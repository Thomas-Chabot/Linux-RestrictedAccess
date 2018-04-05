#include <stdio.h>
#include <string.h>
#include "../helpers/helpers.h"

#include "functions.h"

// The idea here: Every function will take the arguments & an offset.
// The offset will be how far to the first argument - this SHOULD be 2, but may change?
// The message that must be sent for the call will be returned to *result
int add_user (int argc, char** argv, int offset, char* result);
int revoke_access (int argc, char** argv, int offset, char* result);
int remove_file_security (int argc, char** argv, int offset, char* result);

int reqd_opt (int argc, int argNum, char* argName);
void optional_opt (int argc, char** argv, int argNum, char* defaultValue, char** result);

#define ARGS_OFFSET 2 // [0] = Program call; [1] = type of call; [2] ... = arguments

#define CMD_ADD_USER "add_user"
#define CMD_REVOKE_ACCESS "revoke_access"
#define CMD_REMOVE_FILE_SECURITY "remove_file"
#define CMD_HELP "help"

#define MSG_ADD_USER "add_user"
#define MSG_REVOKE_ACCESS "revoke_access"
#define MSG_REMOVE_FILE "remove_file_security"

int parse_func (int argc, char* argv [], char* result) {
  char* cmdType = argv [1];
  strlower (cmdType);

  if (strcmp (cmdType, CMD_ADD_USER) == 0) {
    return add_user (argc, argv, ARGS_OFFSET, result);
  } else if (strcmp (cmdType, CMD_REVOKE_ACCESS) == 0) {
    return revoke_access (argc, argv, ARGS_OFFSET, result);
  } else if (strcmp (cmdType, CMD_REMOVE_FILE_SECURITY) == 0) {
    return remove_file_security (argc, argv, ARGS_OFFSET, result);
  } else if (strcmp (cmdType, CMD_HELP) == 0) {
    printf ("The available options are:\n");
    printf ("\t%s FilePath UserId CanRead CanWrite CanExecute\n", CMD_ADD_USER);
    printf ("\t%s FilePath UserId\n", CMD_REVOKE_ACCESS);
    printf ("\t%s FilePath\n", CMD_REMOVE_FILE_SECURITY);

    return DO_NO_SEND;
  }
}

int add_user (int argc, char** argv, int offset, char* result) {
  // First argument, second argument required. Third, fourth, fifth optional => default to 0
  if (reqd_opt (argc, offset, "FilePath") < 0) return -1;
  if (reqd_opt (argc, offset + 1, "UserId") < 0) return -1;

  char* canRead;
  char* canWrite;
  char* canExec;

  optional_opt (argc, argv, offset + 2, "1", &canRead);
  optional_opt (argc, argv, offset + 3, "1", &canWrite);
  optional_opt (argc, argv, offset + 4, "1", &canExec);

  sprintf (result, "%s %s %s %s %s %s", MSG_ADD_USER, argv[offset], argv[offset + 1], canRead, canWrite, canExec);
  return 0;
}

int revoke_access (int argc, char** argv, int offset, char* result) {
  if (reqd_opt (argc, offset, "FilePath") < 0) return -1;
  if (reqd_opt (argc, offset + 1, "UserId") < 0) return -1;

  sprintf (result, "%s %s %s", MSG_REVOKE_ACCESS, argv[offset], argv[offset + 1]);
  return 0;
}

int remove_file_security (int argc, char** argv, int offset, char* result) {
  if (reqd_opt (argc, offset, "FilePath") < 0) return -1;

  sprintf (result, "%s %s", MSG_REMOVE_FILE, argv[offset]);
  return 0;
}

int reqd_opt (int argc, int argNum, char* argName) {
  if (argc <= argNum) {
    printf ("REQD: %s is a required argument\n", argName);
    return -1;
  }

  return 0;
}

void optional_opt (int argc, char** argv, int argNum, char* defaultValue, char** result) {
  if (argc <= argNum)
    *result = defaultValue;
  else
    *result = argv [argNum];
}
