#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include "ext2_fs.h"
unsigned int blocksize = EXT2_MIN_BLOCK_SIZE;
int img = 0;
bool bm_get(u_char *bitmap, size_t i)
{
    u_char mbyte = bitmap[i / 8];
    for (int j = i % 8; j > 0; --j)
        mbyte >>= 1;
    return mbyte & 1;
}
void print_indirectory(int depth, int inode_rank, int parent_index, int block_rank, size_t offset)
{
    u_int32_t buffer[0x100];
    pread(img, &buffer, sizeof(buffer), offset);
    for (int i = 0; i < 0x100; ++i)
        if (buffer[i])
            fprintf(stdout, "INDIRECT,%i,%i,%i,%i,%i\n",
                    inode_rank + 1,
                    depth,
                    block_rank + i,
                    parent_index,
                    buffer[i]);
    if (depth > 1)
        for (int i = 0; i < 0x100; ++i)
            if (buffer[i])
                print_indirectory(depth - 1, inode_rank, buffer[i], block_rank + (i << (16 * depth)), buffer[i] * blocksize);
}
void print_directorylist(int inode_rank, size_t offset)
{
    size_t offset_origin = offset;
    struct ext2_dir_entry buffer;
    pread(img, &buffer, sizeof(buffer), offset);
    while (buffer.rec_len)
    {
        fprintf(stdout, "DIRENT,%i,%i,%i,%i,%i,\'%s\'\n",
                inode_rank + 1,
                offset - offset_origin,
                buffer.inode,
                buffer.rec_len,
                buffer.name_len,
                buffer.name);
        if (buffer.rec_len - buffer.name_len - 8 >= 4)
            break;
        offset += buffer.rec_len;
        pread(img, &buffer, sizeof(buffer), offset);
    }
}
void print_inode(int rank, size_t offset)
{
    struct ext2_inode buffer;
    pread(img, &buffer, sizeof(buffer), offset);
    if (buffer.i_mode == 0 && buffer.i_uid == 0)
        return;
    time_t _time[3] = {buffer.i_ctime, buffer.i_mtime, buffer.i_atime};
    struct tm time[3];
    time[0].tm_sec = 0;
    time[1].tm_sec = 0;
    time[2].tm_sec = 0;
    gmtime_r(_time, time);
    gmtime_r(_time + 1, time + 1);
    gmtime_r(_time + 2, time + 2);
    char ffmts[8] = {'?', 'c', 'd', 'b', 'f', 's', 'S', '?'};
    char ffmt = ffmts[buffer.i_mode >> 13];
    fprintf(stdout, "INODE,%i,%c,%o,%u,%u,%u,%02i/%02i/%02i %02i:%02i:%02i,%02i/%02i/%02i %02i:%02i:%02i,%02i/%02i/%02i %02i:%02i:%02i,%u,%u",
            rank + 1,
            ffmt,
            buffer.i_mode & 0xfff,
            buffer.i_uid,
            buffer.i_gid,
            buffer.i_links_count,
            time[0].tm_mon, time[0].tm_mday, time[0].tm_year % 100, time[0].tm_hour, time[0].tm_min, time[0].tm_sec,
            time[1].tm_mon, time[1].tm_mday, time[1].tm_year % 100, time[1].tm_hour, time[1].tm_min, time[1].tm_sec,
            time[2].tm_mon, time[2].tm_mday, time[2].tm_year % 100, time[2].tm_hour, time[2].tm_min, time[2].tm_sec,
            buffer.i_size,
            buffer.i_blocks);
    if (ffmt == 'f' || ffmt == 'd' || (ffmt == 's' && buffer.i_size <= 60))
    {
        fprintf(stdout, ",%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i\n",
                buffer.i_block[0],
                buffer.i_block[1],
                buffer.i_block[2],
                buffer.i_block[3],
                buffer.i_block[4],
                buffer.i_block[5],
                buffer.i_block[6],
                buffer.i_block[7],
                buffer.i_block[8],
                buffer.i_block[9],
                buffer.i_block[10],
                buffer.i_block[11],
                buffer.i_block[12],
                buffer.i_block[13],
                buffer.i_block[14]);
    }
    else if (ffmt == 's' && buffer.i_size > 60)
    {
        fprintf(stdout, "\n");
    }
    if (ffmt == 'd')
        print_directorylist(rank, blocksize * buffer.i_block[0]);
    if (buffer.i_block[12])
        print_indirectory(1, rank, buffer.i_block[12], 12, buffer.i_block[12] * blocksize);
    if (buffer.i_block[13])
        print_indirectory(2, rank, buffer.i_block[13], 268, buffer.i_block[13] * blocksize);
    if (buffer.i_block[14])
        print_indirectory(3, rank, buffer.i_block[14], 65804, buffer.i_block[14] * blocksize);
}
void print_bminode_detail(size_t inode_offset, int num, size_t offset)
{
    u_char buffer[blocksize];
    pread(img, &buffer, blocksize, offset);
    for (int i = 0; i < num; ++i)
        if (bm_get(buffer, i))
            print_inode(i, inode_offset + i * sizeof(struct ext2_inode));
}
void print_bmblock_free(int rank, int num, size_t offset)
{
    u_char buffer[blocksize];
    pread(img, &buffer, blocksize, offset);
    for (int i = 0; i < num; ++i)
        if (!bm_get(buffer, i))
            fprintf(stdout, "BFREE,%i\n", rank + i + 1);
}
void print_bminode_free(int rank, int num, size_t offset)
{
    u_char buffer[blocksize];
    pread(img, &buffer, blocksize, offset);
    for (int i = 0; i < num; ++i)
        if (!bm_get(buffer, i))
            fprintf(stdout, "IFREE,%i\n", rank + i + 1);
}
void print_group(int index, int blocknum, int inodenum, size_t offset)
{
    struct ext2_group_desc buffer;
    pread(img, &buffer, sizeof(buffer), offset);
    fprintf(stdout, "GROUP,%i,%i,%i,%u,%u,%u,%u,%u\n",
            index,
            blocknum,
            inodenum,
            buffer.bg_free_blocks_count,
            buffer.bg_free_inodes_count,
            buffer.bg_block_bitmap,
            buffer.bg_inode_bitmap,
            buffer.bg_inode_table);
    u_char block[0x400];
    int bmnum = 1 + (blocknum - 1) / (8 * blocksize);
    for (int i_bm = 0; i_bm < bmnum; ++i_bm)
        print_bmblock_free(i_bm * 8 * blocksize, blocknum, blocksize * (buffer.bg_block_bitmap + i_bm));
    bmnum = 1 + (inodenum - 1) / (8 * blocksize);
    for (int i_bm = 0; i_bm < bmnum; ++i_bm)
        print_bminode_free(i_bm * 8 * blocksize, inodenum, blocksize * (buffer.bg_inode_bitmap + i_bm));
    for (int i_bm = 0; i_bm < bmnum; ++i_bm)
        print_bminode_detail(buffer.bg_inode_table * blocksize, inodenum, blocksize * (buffer.bg_inode_bitmap + i_bm));
}
void print_superblock(size_t offset)
{
    struct ext2_super_block buffer;
    pread(img, &buffer, sizeof(buffer), offset);
    offset += 0x400;
    for (int i = 0; i < buffer.s_log_block_size; ++i)
        blocksize <<= 1;
    fprintf(stdout, "SUPERBLOCK,%u,%u,%u,%u,%u,%u,%u\n",
            buffer.s_blocks_count,
            buffer.s_inodes_count,
            blocksize,
            buffer.s_inode_size,
            buffer.s_blocks_per_group,
            buffer.s_inodes_per_group,
            buffer.s_first_ino);
    print_group(0, buffer.s_blocks_count, buffer.s_inodes_count, offset);
}
int main()
{
    img = open("./EXT2_test.img", O_RDONLY);
    if (img < 0)
        exit(1);
    int out = open("lab3a.csv", O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (out < 0)
        exit(1);
    close(STDOUT_FILENO);
    dup(out);
    close(out);
    print_superblock(0x400);
    return 0;
}