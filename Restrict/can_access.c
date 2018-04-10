#include <FifoWrite.h>
#include <FifoRead.h>
#include <sf_pipes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <fcntl.h>
#include <stdarg.h>
#include <string.h>
#include <limits.h>

int getUserId ();
void expand_path (const char* pathname, char* fullpath);
int startsWith(const char *pre, const char *str);
void read_response (char* resp);
int writeMsg (const char* msg);

int should_ignore (const char* pathname);

int can_open (const char* pathname) {
  char msg [MAX_COMMAND_LEN];
  char path [PATH_MAX];
  expand_path (pathname, path); // get the actual path

  // NOTE: Only running operations on /home & /media, to avoid messing with the system
  //if (!startsWith ("/home", path) && !startsWith ("/media", path) && !startsWith ("/var/shared", path)) return 1;
  if (should_ignore (path)) return 1;

  // check if the user has access
  sprintf (msg, "%s %s %d", CMD_CAN_ACCESS, path, getUserId());
  int status = writeMsg (msg);
  if (status < 0) return 1;

  // return true if the user has access; false if not
  char resp [MAX_COMMAND_LEN];
  read_response (resp);

  // note: server returns true by passing back a '1'
  return resp [0] == '1';
}

int writeMsg (const char* message) {
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

void read_response (char* resp) {
  int len = MAX_COMMAND_LEN;
  int status;
  do {
    status = fifo_read (SERVER_RETURN_PIPE, resp, len);
  } while (status == ERR_FR_OPEN);
}

void expand_path(const char *pathname, char *fullpath)
{
    if (!realpath(pathname, fullpath)) {
        fullpath = "";
    }
}

int startsWith(const char *pre, const char *str)
{
  return (strncmp(pre, str, strlen(pre)) == 0);
}

int getUserId () {
  return getuid();
}


int should_ignore (const char* path) {
  if (startsWith ("/secure_folder/", path)) return 1;

  // Was having an issue with the .swp files - ignore these
  if (strstr (path, ".swp") != NULL) return 1;

  // Finally, if it doesn't exist - ignore it
  return access (path, F_OK) == -1;
}
