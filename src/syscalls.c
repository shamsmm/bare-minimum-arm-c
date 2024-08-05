#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include "os/os.h"
#include "uart/uart.h"
#include "bluepill/bluepill.h"

int _getpid(void)
{
    return 1;
}

int _kill(int pid, int sig)
{
    errno = EINVAL;
    return -1;
}

void _exit (int status)
{
    _kill(status, -1);
    while (1) {}		/* Make sure we hang here */
}

int _read_r (struct _reent *r, int file, char * ptr, int len)
{
    r = r;
    file = file;
    ptr = ptr;
    len = len;

    errno = EINVAL;
    return -1;
}

int _lseek_r (struct _reent *r, int file, int ptr, int dir)
{
    r = r;
    file = file;
    ptr = ptr;
    dir = dir;

    return 0;
}

int _write(int file, char *data, int len)
{
    OS_TASK_LOCK();
    for(int index=0; index<len; index++)
    {
        if (data[index] == '\n')
        {
            UART_Transmit(USART1, '\r');
        }

        UART_Transmit(USART1, data[index]);
    }
    OS_TASK_UNLOCK();

    return len;
}

int _close_r (struct _reent *r, int file)
{
    return 0;
}

/* Register name faking - works in collusion with the linker.  */
register char * stack_ptr asm ("sp");

caddr_t _sbrk_r (struct _reent *r, int incr)
{
    extern char   end asm ("end"); /* Defined by the linker.  */
    static char * heap_end;
    char *        prev_heap_end;

    if (heap_end == NULL)
        heap_end = & end;

    prev_heap_end = heap_end;

    if (heap_end + incr > stack_ptr)
    {
        /* Some of the libstdc++-v3 tests rely upon detecting
          out of memory errors, so do not abort here.  */
#if 0
        extern void abort (void);

      _write (1, "_sbrk: Heap and stack collision\n", 32);

      abort ();
#else
        errno = ENOMEM;
        return (caddr_t) -1;
#endif
    }

    heap_end += incr;

    return (caddr_t) prev_heap_end;
}

int _fstat_r (struct _reent *r, int file, struct stat * st)
{
    r = r;
    file = file;

    memset (st, 0, sizeof (* st));
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty_r(struct _reent *r, int fd)
{
    r = r;
    fd = fd;

    return 1;
}