#include <stdio.h>
#include <FifoWrite.h>
#include <FifoRead.h>
#include <sf_pipes.h>
#include "helpers/helpers.h"
#include "functions/functions.h"

void readNextMessage (char* resp, int len) {
  int status;
  do {
    status = fifo_read (SERVER_RETURN_PIPE, resp, len);
  } while (status == ERR_FR_OPEN);

  resp [len - 1] = '\0';
}

int writeMessage (char* message) {
  int status = fifo_write (message, SERVER_FIFO);
  switch (status) {
    case ERR_FW_WRITE:
      printf ("Write failed\n");
      break;
    case ERR_FW_OPEN:
      printf ("Open failed\n");
      break;
    default:
      break;
  }
  return status;
}

int main (int argc, char* argv []) {
  char resp [2];
  char message [MAX_COMMAND_LEN];

  int result = parse_func (argc, argv, message);
  if (result == DO_NO_SEND) return 0;

  if (result < 0)
    return 0;

  if (writeMessage (message) == 0) {
    readNextMessage (resp, 2);

    if (resp[0] == '1')
      printf ("Operation completed successfully\n");
    else
      printf("Operation failed.\n");
  }
}
