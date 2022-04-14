#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
int s_fdcp[256];
int s_fdcpi = 0;
int s_argi = 1;
int s_argc = 0;
char **s_argv = NULL;
char s_argbuf[BUFSIZ];
bool verbose = false;
int waitnum = -256;
char* child_args[256]={};
int child_pid[256]={};
int child_num=0;
void set_stdin(int fdcp)
{
    close(STDIN_FILENO);
    dup(fdcp);
    close(fdcp);
}
void set_stdout(int fdcp)
{
    close(STDOUT_FILENO);
    dup(fdcp);
    close(fdcp);
}
void set_stderr(int fdcp)
{
    close(STDERR_FILENO);
    dup(fdcp);
    close(fdcp);
}
void setarg(int argc, char **argv)
{
    s_argi = 1;
    s_argc = argc;
    s_argv = argv;
}
char *_getarg()
{
    if (s_argi < s_argc)
        return s_argv[s_argi++];
    return NULL;
}
char *getarg(bool mode) // 0:get one 1:get all
{
    char *ans;
    if (mode)
    {
        char *p = s_argbuf;
        *(p++) = ' ';
        char *temp = NULL;
        while (temp = _getarg())
        {
            if (strlen(temp) > 2 && temp[0] == '-' && temp[1] == '-')
            {
                --s_argi;
                break;
            }
            p = strcpy(p, temp);
            p += strlen(temp);
            *(p++) = ' ';
        }
        *(p - 1) = '\0';
        ans = s_argbuf + 1;
    }
    else
    {
        ans = _getarg();
    }
    if (verbose && ans)
    {
        write(STDOUT_FILENO, ans, strlen(ans));
        write(STDOUT_FILENO, " ", 1);
    }
    return ans;
}
void sig_catch(int sig)
{
    fprintf(stderr, "caught signal %i\n", sig);
    exit(sig);
}
void sig_wait(int sig)
{
    int stat;
    pid_t pid = wait(&stat);
    --waitnum;
    for (int i = 0; i < child_num; ++i)
        if (child_pid[i] == pid)
        {
            child_pid[i] = 0;
            fprintf(stdout, "exit %i %s\n", stat, child_args[i]);
            free(child_args[i]);
            child_args[i] = NULL;
        }
}
int main(int argc, char **argv)
{
    setarg(argc, argv);
    s_fdcp[200] = STDIN_FILENO;
    s_fdcp[201] = STDOUT_FILENO;
    s_fdcp[202] = STDERR_FILENO;
    char *arg;
    int fflag = 0;
    while (arg = getarg(0))
    {
        if (false)
            ;
        else if (!strcmp(arg, "--append"))
            fflag |= O_APPEND;
        else if (!strcmp(arg, "--cloexec"))
            fflag |= O_CLOEXEC;
        else if (!strcmp(arg, "--creat"))
            fflag |= O_CREAT;
        else if (!strcmp(arg, "--directory"))
            fflag |= O_DIRECTORY;
        else if (!strcmp(arg, "--dsync"))
            fflag |= O_DSYNC;
        else if (!strcmp(arg, "--excl"))
            fflag |= O_EXCL;
        else if (!strcmp(arg, "--nofollow"))
            fflag |= O_NOFOLLOW;
        else if (!strcmp(arg, "--nonblock"))
            fflag |= O_NONBLOCK;
        else if (!strcmp(arg, "--rsync"))
            fflag |= O_RSYNC;
        else if (!strcmp(arg, "--sync"))
            fflag |= O_SYNC;
        else if (!strcmp(arg, "--trunc"))
            fflag |= O_TRUNC;
        else if (!strcmp(arg, "--rdonly"))
        {
            fflag |= O_RDONLY;
            arg = getarg(0);
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            int fdcp = open(arg, fflag);
            if (fdcp < 0)
            {
                fprintf(stderr, "An error occured while opening file: %s, reason as %s.\n", arg, strerror(errno));
                exit(2);
            }
            fflag = 0;
            s_fdcp[s_fdcpi++] = fdcp;
        }
        else if (!strcmp(arg, "--wronly"))
        {
            fflag |= O_WRONLY;
            arg = getarg(0);
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            int fdcp = open(arg, fflag);
            if (fdcp < 0)
            {
                fprintf(stderr, "An error occured while opening file: %s, reason as %s.\n", arg, strerror(errno));
                exit(2);
            }
            fflag = 0;
            s_fdcp[s_fdcpi++] = fdcp;
        }
        else if (!strcmp(arg, "--rdwr"))
        {
            fflag |= O_RDWR;
            arg = getarg(0);
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            int fdcp = open(arg, fflag);
            if (fdcp < 0)
            {
                fprintf(stderr, "An error occured while opening file: %s, reason as %s.\n", arg, strerror(errno));
                exit(2);
            }
            fflag = 0;
            s_fdcp[s_fdcpi++] = fdcp;
        }
        else if (!strcmp(arg, "--pipe"))
        {
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            if (pipe(s_fdcp + s_fdcpi) < 0)
            {
                fprintf(stderr, "An error occured while construction pipi, reason as %s.\n", strerror(errno));
                exit(3);
            }
            s_fdcpi += 2;
        }
        else if (!strcmp(arg, "--command"))
        {
            char *i = getarg(0);
            char *o = getarg(0);
            char *e = getarg(0);
            char *a = getarg(1);
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            int ii = atoi(i);
            int oo = atoi(o);
            int ee = atoi(e);
            ++waitnum;
            pid_t pid = fork();
            if (!pid)
            {
                while (s_fdcpi-- > 0)
                    if (s_fdcpi != ii && s_fdcpi != oo && s_fdcpi != ee)
                        close(s_fdcp[s_fdcpi]);
                set_stdin(s_fdcp[ii]);
                set_stdout(s_fdcp[oo]);
                set_stderr(s_fdcp[ee]);
                system(a);
                close(s_fdcp[ii]);
                close(s_fdcp[oo]);
                close(s_fdcp[ee]);
                exit(0);
            }
            else
            {
                child_args[child_num] = (char *)malloc(strlen(a) + 1);
                strcpy(child_args[child_num], a);
                child_pid[child_num] = pid;
                ++child_num;
            }
        }
        else if (!strcmp(arg, "--wait"))
        {
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            if (waitnum < 0)
                waitnum += 256;
            signal(SIGCHLD, sig_wait);
        }
        else if (!strcmp(arg, "--close"))
        {
            close(s_fdcp[atoi(getarg(0))]);
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
        }
        else if (!strcmp(arg, "--verbose"))
        {
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            verbose = true;
        }
        else if (!strcmp(arg, "--abort"))
        {
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            *(int *)0 = 0;
        }
        else if (!strcmp(arg, "--catch"))
        {
            int sig = atoi(getarg(0));
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            signal(sig, sig_catch);
        }
        else if (!strcmp(arg, "--ignore"))
        {
            int sig = atoi(getarg(0));
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            signal(sig, SIG_IGN);
        }
        else if (!strcmp(arg, "--default"))
        {
            int sig = atoi(getarg(0));
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            signal(sig, SIG_DFL);
        }
        else if (!strcmp(arg, "--pause"))
        {
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            pause();
        }
        else
        {
            fprintf(stderr, "invalid argument found: %s\n", arg);
        }
    }
    while (s_fdcpi-- > 0)
        close(s_fdcp[s_fdcpi]);
    while (waitnum > 0)
        pause();
    for (int i = 0; i < child_num; ++i)
        if (child_pid[i])
        {
            child_pid[i] = 0;
            free(child_args[i]);
            child_args[i] = NULL;
        }
    return 0;
}