#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "helpers/helpers.h"

int main () {
  int userId = getUserId (NULL);

  printf ("The user ID for student is %d\n", getUserId ("student"));
  printf ("The current user ID is %d\n", getUserId(NULL));
  printf ("The user ID for root is %d\n", getUserId ("root"));
  printf ("The user ID for non-existant name is %d\n", getUserId("non-existant name"));

  printf ("Sending a message.\n");

  char * myfifo = "/secure_folder/pipe_to_server";
  int fd;

  /* create the FIFO (named pipe) */
  mkfifo(myfifo, 0666);


  /* write "Hi" to the FIFO */
  fd = open(myfifo, O_WRONLY);
  write(fd, "Hi", sizeof("Hi"));
  close(fd);

  printf ("The message has been sent\n");

  /* remove the FIFO */
  unlink(myfifo);
}
