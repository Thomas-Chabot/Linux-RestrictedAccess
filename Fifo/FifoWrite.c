// Credit to StackOverflow for this function
// https://stackoverflow.com/questions/2784500/how-to-send-a-simple-string-between-two-programs-using-pipes

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "FifoWrite.h"

int fifo_write (char* message, char* fifoPath) {
  int fd;

  /* create the FIFO (named pipe) */
  if (mkfifo(fifoPath, 0666) == -1 && errno != EEXIST)
    return ERR_FW_MK_FIFO;

  /* write the message to the FIFO */
  fd = open(fifoPath, O_WRONLY);
  if (fd == -1) return ERR_FW_OPEN;

  if (write(fd, message, strlen (message)) == 0) {
    printf ("Error code? %d\n", errno);
    return ERR_FW_WRITE;
  };

  close(fd);

  /* remove the FIFO */
  unlink(fifoPath);

  return 0;
}
