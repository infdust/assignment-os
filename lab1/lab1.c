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
int s_fdcp[256];
int s_fdcpi = 0;
int s_argi = 1;
int s_argc = 0;
char **s_argv = NULL;
char s_argbuf[BUFSIZ];
bool verbose = false;
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
        else if (!strcmp(arg, "--rdonly"))
        {
            fflag |= O_RDONLY;
        }
        else if (!strcmp(arg, "--wronly"))
        {
            fflag |= O_WRONLY;
        }
        else if (!strcmp(arg, "--rdwr"))
        {
            fflag |= O_RDWR;
        }
        else if (!strcmp(arg, "--pipe"))
        {
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
            pid_t pid = fork();
            if (!pid)
            {
                set_stdin(s_fdcp[atoi(i)]);
                set_stdout(s_fdcp[atoi(o)]);
                set_stderr(s_fdcp[atoi(e)]);
                system(a);
                exit(0);
            }
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
        }
        else if (!strcmp(arg, "--verbose"))
        {
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
            verbose = true;
        } /*

 --append
     O_APPEND
 --cloexec
     O_CLOEXEC
 --creat
     O_CREAT
 --directory
     O_DIRECTORY
 --dsync
     O_DSYNC
 --excl
     O_EXCL
 --nofollow
     O_NOFOLLOW
 --nonblock
     O_NONBLOCK
 --rsync
     O_RSYNC
 --sync
     O_SYNC
 --trunc
     O_TRUNC

--command i o e cmd args
    Execute a command with standard input i, standard output o and standard error e;
    these values should correspond to earlier file or pipe options.
    The executable for the command is cmd and it has zero or more arguments args.
    None of the cmd and args operands begin with the two characters "--".
--wait
    Wait for all commands to finish. As each finishes, output its exit status or signal number
    as described above, and a copy of the command (with spaces separating arguments) to standard output.

--close N
    Close the Nth file that was opened by a file-opening option.
    For a pipe, this closes just one end of the pipe.
    Once file N is closed, it is an error to access it, just as it is an error
    to access any file number that has never been opened.
    File numbers are not reused by later file-opening options.
--verbose
    Just before executing an option, output a line to standard output containing the option.
    If the option has operands, list them separated by spaces.
    Ensure that the line is actually output, and is not merely sitting in a buffer somewhere.
--profile
    Just after executing an option, output a line to standard output containing the resources used.
    Use getrusage and output a line containing as much useful information as you can glean from it.
--abort
    Crash the shell. The shell itself should immediately dump core, via a segmentation violation.
--catch N
    Catch signal N, where N is a decimal integer, with a handler that outputs the diagnostic N caught to stderr,
    and exits with status N. This exits the entire shell.
    N uses the same numbering as your system; for example, on GNU/Linux, a segmentation violation is signal 11.
--ignore N
    Ignore signal N.
--default N
    Use the default behavior for signal N.
--pause
    Pause, waiting for a signal to arrive.


     */
        else if (!strcmp(arg, "--"))
        {
        }
        else
        {
            int fdcp = open(arg, fflag);
            if (fdcp < 0)
            {
                fprintf(stderr, "An error occured while opening file: %s, reason as %s.\n", arg, strerror(errno));
                exit(2);
            }
            fflag = 0;
            s_fdcp[s_fdcpi++] = fdcp;
            if (verbose)
                write(STDOUT_FILENO, "\n", 1);
        }
    }
    return 0;
}