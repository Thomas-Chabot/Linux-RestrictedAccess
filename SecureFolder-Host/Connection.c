// This file controls everything for interfacing between other programs,
// Such as the piping mechanism.
#include "Connection.h"
#include <errno.h>
#include <FifoRead.h>
#include <FifoWrite.h>

int do_read (char* details) {
  char call_type [MAX_CALL_LEN];
  char file_path [MAX_FILE_PATH];
  char file_id   [UUID_LEN];

  read_str (&details, call_type);
  read_str (&details, file_path);

  get_file_id (file_path, file_id);

  if (strcmp (call_type, CMD_ADD_USER) == 0) {
    return f_add_user (file_id, details);
  } else if (strcmp (call_type, CMD_REVOKE_ACCESS) == 0) {
    return f_revoke_access (file_id, details);
  } else if (strcmp (call_type, CMD_REMOVE_FILE) == 0) {
    return f_remove_file_security (file_id, details);
  } else if (strcmp (call_type, CMD_CAN_ACCESS) == 0) {
    return f_user_can_access (file_id, details);
  } else {
    printf ("Could not find command type: %s\n", call_type);
    return 0;
  }
}

void respond (int value) {
  char resp[2];
  sprintf (resp, "%d", value);
  fifo_write (resp, SERVER_RETURN_PIPE);
}

int main () {
  int fd;
  char * myfifo = SERVER_FIFO;
  char buf[4096];

  /* open, read, and display the message from the FIFO */
  while (1) {
    int ret = fifo_read (myfifo, buf, 4096);
    if (ret == ERR_FR_OPEN) continue;
    if (ret == ERR_FR_READ) {
      printf ("Error on reading\n");
      continue;
    }

    int resp = do_read (buf);

    printf ("Command is %s\n", buf);
    printf ("Return value is %d\n", resp);
    respond (resp);
  }

  return 0;
}
