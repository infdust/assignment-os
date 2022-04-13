#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
bool fault = false;
bool dump=false;
void cmd_input(const char *path)
{
    if (!path)
        return;
    int ifd = open(path, O_RDONLY);
    if (ifd < 0)
    {
        fprintf(stderr,
                "An error occured while disposing argument:--input, with filename as %s, errorstr as %s.\n",
                path, strerror(errno));
        exit(2);
    }
    close(STDIN_FILENO);
    dup(ifd);
    close(ifd);
}
void cmd_output(const char *path)
{
    if (!path)
        return;
    int ofd = open(path, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (ofd < 0)
    {
        fprintf(stderr,
                "An error occured while disposing argument:--output, with filename as %s, errorstr as %s.\n",
                path, strerror(errno));
        exit(3);
    }
    close(STDOUT_FILENO);
    dup(ofd);
    close(ofd);
}
void cmd_segfault()
{
    fault = true;
    pid_t pid = fork();
    if (!pid)
        *(int *)0 = 0;
}
void __sigsegv(int sig)
{
    fprintf(stderr, "caught segmentfault\n");
    exit(4);
}
void cmd_catch()
{
    signal(SIGSEGV, __sigsegv);
}
void cmd_coredump()
{
    kill(0, SIGSEGV);
    exit(139);
}
void run()
{
    if (fault)
        return;
    char buffer[256];
    char *begin;
    char *end;
    int temp = 0;
    while (temp = read(STDIN_FILENO, buffer, 256))
    {
        begin = buffer;
        end = begin + temp;
        while (begin != end)
            begin += write(STDOUT_FILENO, begin, end - begin);
    }
}
int main(int argc, char **argv)
{
    int chr = 1;
    struct option options[] = {
        {"input", optional_argument, NULL, 'i'},
        {"output", optional_argument, NULL, 'o'},
        {"segfault", no_argument, NULL, 'f'},
        {"catch", no_argument, NULL, 'c'},
        {"dump-core", no_argument, NULL, 'd'},
        {NULL, 0, NULL, 0},
    };
    while ((chr = getopt_long(argc, argv, "", options, NULL)) != -1)
        switch (chr)
        {
        case 'i':
            cmd_input(optarg);
            break;
        case 'o':
            cmd_output(optarg);
            break;
        case 'f':
            cmd_segfault();
            break;
        case 'c':
            cmd_catch();
            break;
        case 'd':
            cmd_coredump();
            break;
        case '?':
            fprintf(stderr,
                    "expected arguments:\n--input(=path)\n--output(=path)\n--segfault\n--catch\n--dump-core\n");
            exit(1);
            break;
        }
    run();
    return 0;
}