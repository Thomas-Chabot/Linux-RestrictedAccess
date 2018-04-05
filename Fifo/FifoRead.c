#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include "FifoRead.h"

int fifo_read (char* fifoPath, char* message, int size)
{
    int fd;

    /* open, read, and display the message from the FIFO */
    fd = open(fifoPath, O_RDONLY);
    if (fd < 0) return ERR_FR_OPEN;

    if (read(fd, message, size) < 0)
      return ERR_FR_READ;

    close(fd);

    return 0;
}
