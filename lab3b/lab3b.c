#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
int reserved = 0;
typedef struct SUPERBLOCK
{
    int blocknum;
    int inodenum;
    int blocksize;
    int inodesize;
    int blocknum_pergroup;
    int inodenum_pergroup;
    int inode_head;
} SUPERBLOCK;
typedef struct GROUP
{
    int groupindex;
    int blocknum;
    int inodenum;
    int freeblocknum;
    int freeinodenum;
    int bmlock;
    int bminode;
    int inode_head;
} GROUP;
typedef struct INODE
{
    int index;
    char type;
    int mode;
    int owner;
    int group;
    int linknum;
    int size;
    int lblocknum;
    int directory[12];
    int indirectory1;
    int indirectory2;
    int indirectory3;
} INODE;
typedef struct DIRENT
{
    int inodeindex;
    int offset;
    int fileindex;
    int len;
    int namelen;
    char name[255];
} DIRENT;
typedef struct INDIRECT
{
    int inodeindex;
    int depth;
    int fileoffset;
    int parentblock;
    int block;
} INDIRECT;
void scan_superblock(SUPERBLOCK *p)
{
    if (!p)
        scanf("%*u,%*u,%*u,%*u,%*u,%*u,%*u\n");
    else
        scanf("%i,%i,%i,%i,%i,%i,%i\n",
              &p->blocknum,
              &p->inodenum,
              &p->blocksize,
              &p->inodesize,
              &p->blocknum_pergroup,
              &p->inodenum_pergroup,
              &p->inode_head);
};
void scan_group(GROUP *p)
{
    if (!p)
        scanf("%*u,%*u,%*u,%*u,%*u,%*u,%*u,%*u\n");
    else
        scanf("%i,%i,%i,%i,%i,%i,%i,%i\n",
              &p->groupindex,
              &p->blocknum,
              &p->inodenum,
              &p->freeblocknum,
              &p->freeinodenum,
              &p->bmlock,
              &p->bminode,
              &p->inode_head);
};
void scan_bfree(int *p)
{
    if (!p)
        scanf("%*u\n");
    else
        scanf("%i\n", p);
};
void scan_ifree(int *p)
{
    if (!p)
        scanf("%*u\n");
    else
        scanf("%i\n", p);
};
void scan_inode(INODE *p)
{
    if (!p)
        scanf("%*u,%*c,%*u,%*u,%*u,%*u,%*u/%*u/%*u %*u:%*u:%*u,%*u/%*u/%*u %*u:%*u:%*u,%*u/%*u/%*u %*u:%*u:%*u,%*u,%*u,%*u,%*u,%*u,%*u,%*u,%*u,%*u,%*u,%*u,%*u,%*u,%*u,%*u,%*u,%*u\n");
    else
        scanf("%i,%c,%i,%i,%i,%i,%*u/%*u/%*u %*u:%*u:%*u,%*u/%*u/%*u %*u:%*u:%*u,%*u/%*u/%*u %*u:%*u:%*u,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,%i\n",
              &p->index,
              &p->type,
              &p->mode,
              &p->owner,
              &p->group,
              &p->linknum,
              &p->size,
              &p->lblocknum,
              &p->directory[0],
              &p->directory[1],
              &p->directory[2],
              &p->directory[3],
              &p->directory[4],
              &p->directory[5],
              &p->directory[6],
              &p->directory[7],
              &p->directory[8],
              &p->directory[9],
              &p->directory[10],
              &p->directory[11],
              &p->indirectory1,
              &p->indirectory2,
              &p->indirectory3);
};
void scan_dirent(DIRENT *p)
{
    if (!p)
        scanf("%*u,%*u,%*u,%*u,%*u,'%*[^']'\n");
    else
        scanf("%i,%i,%i,%i,%i,'%[^']'\n",
              &p->inodeindex,
              &p->offset,
              &p->fileindex,
              &p->len,
              &p->namelen,
              p->name);
};
void scan_indirect(INDIRECT *p)
{
    if (!p)
        scanf("%*u,%*u,%*u,%*u,%*u\n");
    else
        scanf("%i,%i,%i,%i,%i\n",
              &p->inodeindex,
              &p->depth,
              &p->fileoffset,
              &p->parentblock,
              &p->block);
};
int main(int argc, char **argv)
{
    if (argc < 2)
        exit(1);
    int summary = open(argv[1], O_RDONLY);
    if (summary < 0)
        exit(1);
    close(STDIN_FILENO);
    dup(summary);
    close(summary);
    char tag[16];
    int superblocknum = 0;
    int groupnum = 0;
    int bfreenum = 0;
    int ifreenum = 0;
    int inodenum = 0;
    int direntnum = 0;
    int indirectnum = 0;
    while (scanf("%[^,],", tag) != EOF)
    {
        if (!strcmp(tag, "SUPERBLOCK"))
            ++superblocknum, scan_superblock(NULL);
        else if (!strcmp(tag, "GROUP"))
            ++groupnum, scan_group(NULL);
        else if (!strcmp(tag, "BFREE"))
            ++bfreenum, scan_bfree(NULL);
        else if (!strcmp(tag, "IFREE"))
            ++ifreenum, scan_ifree(NULL);
        else if (!strcmp(tag, "INODE"))
            ++inodenum, scan_inode(NULL);
        else if (!strcmp(tag, "DIRENT"))
            ++direntnum, scan_dirent(NULL);
        else if (!strcmp(tag, "INDIRECT"))
            ++indirectnum, scan_indirect(NULL);
        else
            exit(1);
    }
    SUPERBLOCK *superblocks = (SUPERBLOCK *)malloc(sizeof(SUPERBLOCK) * superblocknum);
    GROUP *groups = (GROUP *)malloc(sizeof(GROUP) * groupnum);
    int *bfrees = (int *)malloc(sizeof(int) * bfreenum);
    int *ifrees = (int *)malloc(sizeof(int) * ifreenum);
    INODE *inodes = (INODE *)malloc(sizeof(INODE) * inodenum);
    DIRENT *dirents = (DIRENT *)malloc(sizeof(DIRENT) * direntnum);
    INDIRECT *indirects = (INDIRECT *)malloc(sizeof(INDIRECT) * indirectnum);
    superblocknum = 0;
    groupnum = 0;
    bfreenum = 0;
    ifreenum = 0;
    inodenum = 0;
    direntnum = 0;
    indirectnum = 0;
    fseek(stdin, 0, 0);
    while (scanf("%[^,],", tag) != EOF)
    {
        if (!strcmp(tag, "SUPERBLOCK"))
            scan_superblock(superblocks + (superblocknum++));
        else if (!strcmp(tag, "GROUP"))
            scan_group(groups + (groupnum++));
        else if (!strcmp(tag, "BFREE"))
            scan_bfree(bfrees + (bfreenum++));
        else if (!strcmp(tag, "IFREE"))
            scan_ifree(ifrees + (ifreenum++));
        else if (!strcmp(tag, "INODE"))
            scan_inode(inodes + (inodenum++));
        else if (!strcmp(tag, "DIRENT"))
            scan_dirent(dirents + (direntnum++));
        else if (!strcmp(tag, "INDIRECT"))
            scan_indirect(indirects + (indirectnum++));
        else
            exit(1);
    }

    reserved = groups[0].inode_head + (groups[0].inodenum + 7) / 8;

    int *blocks_ownerindex = (int *)malloc(sizeof(int) * groups[0].blocknum); //-1=nil -2=disposed -3=free
    int *blocks_owneroffset = (int *)malloc(sizeof(int) * groups[0].blocknum);
    bool *inodes_allocated = (bool *)malloc(sizeof(bool) * groups[0].inodenum);
    int *inodes_linknum1 = (int *)malloc(sizeof(int) * groups[0].inodenum);
    int *inodes_linknum2 = (int *)malloc(sizeof(int) * groups[0].inodenum);
    int *dir_parent = (int *)malloc(sizeof(int) * direntnum);
    for (int i = 0; i < groups[0].blocknum; ++i)
        blocks_ownerindex[i] = -1;
    for (int i = 0; i < bfreenum; ++i)
        blocks_ownerindex[bfrees[i]] = -3;
    for (int i = 0; i < groups[0].inodenum; ++i)
        inodes_allocated[i] = false;
    for (int i = 0; i < ifreenum; ++i)
        inodes_allocated[ifrees[i]] = true;
    for (int i = 0; i < groups[0].inodenum; ++i)
        inodes_linknum1[i] = -1;
    for (int i = 0; i < groups[0].inodenum; ++i)
        inodes_linknum2[i] = 0;
    for (int i = 0; i < direntnum; ++i)
        dir_parent[i] = -1;
    for (int i = 0; i < inodenum; ++i)
    {
        inodes_linknum1[inodes[i].index] = inodes[i].linknum;
        if(inodes_allocated[inodes[i].index])
            printf("ALLOCATED INODE %i ON FREELIST\n", inodes[i].index);
        inodes_allocated[inodes[i].index] = true;
        if (inodes[i].type == 'd' || inodes[i].type == 'f' || (inodes[i].type == 's' && inodes[i].size <= 60))
        {
            int block;
            for (int j = 0; j < 12; ++j)
            {
                block = inodes[i].directory[j];
                if (block == 0)
                    ;
                else if (block < 0 || block >= groups[0].blocknum)
                    printf("INVALID BLOCK %i IN INODE %i AT OFFSET %i\n", block, inodes[i].index, j);
                else if (block > 0 && block < reserved)
                    printf("RESERVED BLOCK %i IN INODE %i AT OFFSET %i\n", block, inodes[i].index, j);
                else if (blocks_ownerindex[block] == -1)
                    blocks_ownerindex[block] = inodes[i].index, blocks_owneroffset[block] = j;
                else if (blocks_ownerindex[block] == -2)
                    printf("DUPLICATE BLOCK %i IN INODE %i AT OFFSET %i\n", block, inodes[i].index, j);
                else if (blocks_ownerindex[block] == -3)
                    printf("ALLOCATED BLOCK %i ON FREELIST\n", block);
                else
                {
                    if (blocks_owneroffset[i] < 12)
                        printf("DUPLICATE BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                    else if (blocks_owneroffset[i] < 268)
                        printf("DUPLICATE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                    else if (blocks_owneroffset[i] < 65804)
                        printf("DUPLICATE DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                    else
                        printf("DUPLICATE TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                    printf("DUPLICATE BLOCK %i IN INODE %i AT OFFSET %i\n", block, inodes[i].index, j);
                    blocks_ownerindex[block] = -2;
                }
            }
            block = inodes[i].indirectory1;
            if (block == 0)
                ;
            else if (block < 0 || block >= groups[0].blocknum)
                printf("INVALID INDIRECT BLOCK %i IN INODE %i AT OFFSET 12\n", block, inodes[i].index);
            else if (block > 0 && block < reserved)
                printf("RESERVED INDIRECT BLOCK %i IN INODE %i AT OFFSET 12\n", block, inodes[i].index);
            else if (blocks_ownerindex[block] == -1)
                blocks_ownerindex[block] = inodes[i].index, blocks_owneroffset[block] = 12;
            else if (blocks_ownerindex[block] == -2)
                printf("DUPLICATE INDIRECT BLOCK %i IN INODE %i AT OFFSET 12\n", block, inodes[i].index);
            else if (blocks_ownerindex[block] == -3)
                printf("ALLOCATED BLOCK %i ON FREELIST\n", block);
            else
            {
                if (blocks_owneroffset[i] < 12)
                    printf("DUPLICATE BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else if (blocks_owneroffset[i] < 268)
                    printf("DUPLICATE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else if (blocks_owneroffset[i] < 65804)
                    printf("DUPLICATE DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else
                    printf("DUPLICATE TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                printf("DUPLICATE INDIRECT BLOCK %i IN INODE %i AT OFFSET 12\n", block, inodes[i].index);
                blocks_ownerindex[block] = -2;
            }
            block = inodes[i].indirectory2;
            if (block == 0)
                ;
            else if (block < 0 || block >= groups[0].blocknum)
                printf("INVALID DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET 268\n", block, inodes[i].index);
            else if (block > 0 && block < reserved)
                printf("RESERVED DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET 268\n", block, inodes[i].index);
            else if (blocks_ownerindex[block] == -1)
                blocks_ownerindex[block] = inodes[i].index, blocks_owneroffset[block] = 268;
            else if (blocks_ownerindex[block] == -2)
                printf("DUPLICATE DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET 268\n", block, inodes[i].index);
            else if (blocks_ownerindex[block] == -3)
                printf("ALLOCATED BLOCK %i ON FREELIST\n", block);
            else
            {
                if (blocks_owneroffset[i] < 12)
                    printf("DUPLICATE BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else if (blocks_owneroffset[i] < 268)
                    printf("DUPLICATE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else if (blocks_owneroffset[i] < 65804)
                    printf("DUPLICATE DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else
                    printf("DUPLICATE TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                printf("DUPLICATE DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET 268\n", block, inodes[i].index);
                blocks_ownerindex[block] = -2;
            }
            block = inodes[i].indirectory3;
            if (block == 0)
                ;
            else if (block < 0 || block >= groups[0].blocknum)
                printf("INVALID TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET 65804\n", block, inodes[i].index);
            else if (block > 0 && block < reserved)
                printf("RESERVED TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET 65804\n", block, inodes[i].index);
            else if (blocks_ownerindex[block] == -1)
                blocks_ownerindex[block] = inodes[i].index, blocks_owneroffset[block] = 65804;
            else if (blocks_ownerindex[block] == -2)
                printf("DUPLICATE TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET 65804\n", block, inodes[i].index);
            else if (blocks_ownerindex[block] == -3)
                printf("ALLOCATED BLOCK %i ON FREELIST\n", block);
            else
            {
                if (blocks_owneroffset[i] < 12)
                    printf("DUPLICATE BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else if (blocks_owneroffset[i] < 268)
                    printf("DUPLICATE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else if (blocks_owneroffset[i] < 65804)
                    printf("DUPLICATE DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else
                    printf("DUPLICATE TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                printf("DUPLICATE TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET 65804\n", block, inodes[i].index);
                blocks_ownerindex[block] = -2;
            }
        }
    }
    for (int i = 0; i < direntnum; ++i)
    {
        if (dirents[i].fileindex < 1 || dirents[i].fileindex > groups[0].inodenum)
            printf("DIRECTORY INODE %i NAME '%s' INVALID INODE %i\n", dirents[i].inodeindex, dirents[i].name, dirents[i].fileindex);
        else
        {
            if (inodes_linknum1[dirents[i].fileindex] <= 0)
                printf("DIRECTORY INODE %i NAME '%s' UNALLOCATED INODE %i\n", dirents[i].inodeindex, dirents[i].name, dirents[i].fileindex);
            else
                ++inodes_linknum2[dirents[i].fileindex];
            if (!strcmp(".", dirents[i].name))
            {
                if (dirents[i].inodeindex != dirents[i].fileindex)
                    printf("DIRECTORY INODE %i NAME '.' LINK TO INODE %i SHOULD BE %i\n", dirents[i].inodeindex, dirents[i].fileindex, dirents[i].inodeindex);
            }
            else if (!strcmp("..", dirents[i].name))
            {
                if (dirents[i].inodeindex < dirents[i].fileindex)
                printf("DIRECTORY INODE %i NAME '..' LINK TO INODE %i SHOULD BE %i\n", dirents[i].inodeindex, dirents[i].fileindex, dirents[i].inodeindex);
            }
        }
    }
    for (int i = 0; i < indirectnum; ++i)
    {
        int block = indirects[i].block;
        switch (indirects[i].depth)
        {
        case 1:
            if (block == 0)
                ;
            else if (block < 0 || block >= groups[0].blocknum)
                printf("INVALID INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, indirects[i].inodeindex, indirects[i].fileoffset);
            else if (block > 0 && block < reserved)
                printf("RESERVED INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, indirects[i].inodeindex, indirects[i].fileoffset);
            else if (blocks_ownerindex[block] == -1)
                blocks_ownerindex[block] = indirects[i].inodeindex, blocks_owneroffset[block] = indirects[i].fileoffset;
            else if (blocks_ownerindex[block] == -2)
                printf("DUPLICATE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, indirects[i].inodeindex, indirects[i].fileoffset);
            else if (blocks_ownerindex[block] == -3)
                printf("ALLOCATED BLOCK %i ON FREELIST\n", block);
            else
            {
                if (blocks_owneroffset[i] < 12)
                    printf("DUPLICATE BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else if (blocks_owneroffset[i] < 268)
                    printf("DUPLICATE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else if (blocks_owneroffset[i] < 65804)
                    printf("DUPLICATE DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else
                    printf("DUPLICATE TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                printf("DUPLICATE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, indirects[i].inodeindex, indirects[i].fileoffset);
                blocks_ownerindex[block] = -2;
            }
            break;
        case 2:
            if (block == 0)
                ;
            else if (block < 0 || block >= groups[0].blocknum)
                printf("INVALID DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, indirects[i].inodeindex, indirects[i].fileoffset);
            else if (block > 0 && block < reserved)
                printf("RESERVED DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, indirects[i].inodeindex, indirects[i].fileoffset);
            else if (blocks_ownerindex[block] == -1)
                blocks_ownerindex[block] = indirects[i].inodeindex, blocks_owneroffset[block] = indirects[i].fileoffset;
            else if (blocks_ownerindex[block] == -2)
                printf("DUPLICATE DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, indirects[i].inodeindex, indirects[i].fileoffset);
            else if (blocks_ownerindex[block] == -3)
                printf("ALLOCATED BLOCK %i ON FREELIST\n", block);
            else
            {
                if (blocks_owneroffset[i] < 12)
                    printf("DUPLICATE BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else if (blocks_owneroffset[i] < 268)
                    printf("DUPLICATE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else if (blocks_owneroffset[i] < 65804)
                    printf("DUPLICATE DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else
                    printf("DUPLICATE TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                printf("DUPLICATE DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, indirects[i].inodeindex, indirects[i].fileoffset);
                blocks_ownerindex[block] = -2;
            }
            break;
        case 3:
            if (block == 0)
                ;
            else if (block < 0 || block >= groups[0].blocknum)
                printf("INVALID TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, indirects[i].inodeindex, indirects[i].fileoffset);
            else if (block > 0 && block < reserved)
                printf("RESERVED TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, indirects[i].inodeindex, indirects[i].fileoffset);
            else if (blocks_ownerindex[block] == -1)
                blocks_ownerindex[block] = indirects[i].inodeindex, blocks_owneroffset[block] = indirects[i].fileoffset;
            else if (blocks_ownerindex[block] == -2)
                printf("DUPLICATE TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, indirects[i].inodeindex, indirects[i].fileoffset);
            else if (blocks_ownerindex[block] == -3)
                printf("ALLOCATED BLOCK %i ON FREELIST\n", block);
            else
            {
                if (blocks_owneroffset[i] < 12)
                    printf("DUPLICATE BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else if (blocks_owneroffset[i] < 268)
                    printf("DUPLICATE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else if (blocks_owneroffset[i] < 65804)
                    printf("DUPLICATE DOUBLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                else
                    printf("DUPLICATE TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, blocks_ownerindex[block], blocks_owneroffset[block]);
                printf("DUPLICATE TRIPLE INDIRECT BLOCK %i IN INODE %i AT OFFSET %i\n", block, indirects[i].inodeindex, indirects[i].fileoffset);
                blocks_ownerindex[block] = -2;
            }
            break;
        }
    }
    for (int i = reserved; i < groups[0].blocknum; ++i)
        if (blocks_ownerindex[i] == -1)
            printf("UNREFERENCED BLOCK %i\n", i);
    for (int i = superblocks[0].inode_head; i < groups[0].inodenum; ++i)
        if (!inodes_allocated[i])
            printf("UNALLOCATED INODE %i NOT ON FREELIST\n", i);
    for (int i = 0; i < groups[0].inodenum; ++i)
        if (inodes_linknum1[i] > 0 && inodes_linknum1[i] != inodes_linknum2[i])
            printf("INODE %i HAS %i LINKS BUT LINKCOUNT IS %i\n", i, inodes_linknum2[i], inodes_linknum1[i]);

    free(dir_parent);
    free(inodes_allocated);
    free(blocks_owneroffset);
    free(blocks_ownerindex);

    free(superblocks);
    free(groups);
    free(bfrees);
    free(ifrees);
    free(inodes);
    free(dirents);
    free(indirects);
    return 0;
}