#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>
#include "stm32f10x.h"

// errno
#undef errno
extern int errno;

/*
 ���������� ����� - ������ ������.
 */
char *__env[1] = { 0 };
char **environ = __env;

int _write(int file, char *ptr, int len);

// exit - ���������� �����. � �������� ������ - �������������.
void _exit(__attribute__((unused)) int status)
{
    while (1);
}

// close - �������� ����� - ���������� ������
int _close(__attribute__((unused)) int file)
{
    return -1;
}
/*
 execve - �������� ���������� ������ �������� - ��������� ��� -> ���������� ������.
 */
int _execve(__attribute__((unused)) char *name, __attribute__((unused)) char **argv, __attribute__((unused)) char **env)
{
    errno = ENOMEM;
    return -1;
}

/*
 fork = �������� ������ ��������
 */
int _fork()
{
    errno = EAGAIN;
    return -1;
}

/*
 fstat - ��������� ��������� �����
 */
int _fstat(__attribute__((unused)) int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 getpid - �������� ID �������� ��������
 */

int _getpid()
{
    return 1;
}

/*
 isatty - �������� �� ���� ����������.
 */
int _isatty(int file)
{
    switch (file)
    {
    case STDOUT_FILENO:
    case STDERR_FILENO:
    case STDIN_FILENO:
        return 1;
    default:
        //errno = ENOTTY;
        errno = EBADF;
        return 0;
    }
}

/*
 kill - ������� ������ ��������
 */
int _kill(__attribute__((unused)) int pid,__attribute__((unused))  int sig)
{
    errno = EINVAL;
    return (-1);
}

/*
 link - ��������� ����� ��� ��� ������������� �����.
 */

int _link(__attribute__((unused)) char *old, __attribute__((unused)) char *new)
{
    errno = EMLINK;
    return -1;
}

/*
 lseek - ���������� ������� � �����
 */
int _lseek(__attribute__((unused)) int file, __attribute__((unused)) int ptr, __attribute__((unused)) int dir)
{
    return 0;
}

/*
 sbrk - ��������� ������ ������� ������, ����������� ��� malloc
 */
caddr_t _sbrk(int incr)
{
    extern char _ebss;
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
    {
        heap_end = &_ebss;
    }
    prev_heap_end = heap_end;

    char * stack = (char*) __get_MSP();
    if (heap_end + incr > stack)
    {
        _write(STDERR_FILENO, "Heap and stack collision\n", 25);
        errno = ENOMEM;
        return (caddr_t) -1;
        //abort ();
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;

}

/*
 read - ������ �� �����, � ��� ���� ��� ������ ���� ������ stdin
 */

int _read(__attribute__((unused)) int file, __attribute__((unused)) char *ptr, __attribute__((unused)) int len)
{
	return -1;
}

/*
 stat - ��������� ��������� �����.
 */

int _stat(__attribute__((unused)) const char *filepath, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 times - ��������� ���������� � �������� (������� �����: ���������, ������������ � �.�.)
 */

clock_t _times(__attribute__((unused)) struct tms *buf)
{
    return -1;
}

/*
 unlink - ������� ��� �����.
 */
int _unlink(__attribute__((unused)) char *name)
{
    errno = ENOENT;
    return -1;
}

/*
 wait - �������� �������� ���������
 */
int _wait(__attribute__((unused)) int *status)
{
    errno = ECHILD;
    return -1;
}


