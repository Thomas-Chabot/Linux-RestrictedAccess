#include <stdio.h>
#include <string.h>
#include <sf_pipes.h>
#include "../helpers/helpers.h"

#include "functions.h"

// The idea here: Every function will take the arguments & an offset.
// The offset will be how far to the first argument - this SHOULD be 2, but may change?
// The message that must be sent for the call will be returned to *result
int add_file (int argc, char** argv, int offset, char* result);
int add_user (int argc, char** argv, int offset, char* result);
int revoke_access (int argc, char** argv, int offset, char* result);
int remove_file_security (int argc, char** argv, int offset, char* result);

void get_file_path (char** argv, int index, char* result);
int get_uid (int argc, char** argv, int index);

int reqd_opt (int argc, int argNum, char* argName);
void optional_opt (int argc, char** argv, int argNum, char* defaultValue, char** result);

#define ARGS_OFFSET 2 // [0] = Program call; [1] = type of call; [2] ... = arguments

#define MSG_ADD_FILE "add_file"
#define MSG_ADD_USER "add_user"
#define MSG_REVOKE_ACCESS "revoke_access"
#define MSG_REMOVE_FILE_SECURITY "remove_file"
#define MSG_HELP "help"

#define USER_ID_LEN 5 // 4 characters & a NULL

int parse_func (int argc, char* argv [], char* result) {
  char* cmdType;

  // If no command line arguments were passed in, default to 'help'
  if (argc < 2) cmdType = MSG_HELP;
  else{
    cmdType = strlower (argv [1]);
  }

  if (strcmp (cmdType, MSG_ADD_FILE) == 0) {
    return add_file (argc, argv, ARGS_OFFSET, result);
  } else if (strcmp (cmdType, MSG_ADD_USER) == 0) {
    return add_user (argc, argv, ARGS_OFFSET, result);
  } else if (strcmp (cmdType, MSG_REVOKE_ACCESS) == 0) {
    return revoke_access (argc, argv, ARGS_OFFSET, result);
  } else if (strcmp (cmdType, MSG_REMOVE_FILE_SECURITY) == 0) {
    return remove_file_security (argc, argv, ARGS_OFFSET, result);
  } else if (strcmp (cmdType, MSG_HELP) == 0) {
    printf ("The available options are:\n");
    printf ("\t%s FilePath\n", MSG_ADD_FILE);
    printf ("\t%s FilePath Username CanRead CanWrite CanExecute\n", MSG_ADD_USER);
    printf ("\t%s FilePath Username\n", MSG_REVOKE_ACCESS);
    printf ("\t%s FilePath\n", MSG_REMOVE_FILE_SECURITY);

    return DO_NO_SEND;
  } else {
    printf ("Unknown argument: %s\n", cmdType);
    return DO_NO_SEND;
  }
}

int add_file (int argc, char** argv, int offset, char* result) {
  // First argument, second argument required. Third, fourth, fifth optional => default to 0
  if (reqd_opt (argc, offset, "FilePath") < 0) return -1;

  char filePath [MAX_FILE_PATH];
  get_file_path (argv, offset, filePath);
  if (filePath == NULL) return -1;

  int uid = getUserId (NULL);

  sprintf (result, "%s %s %d", CMD_ADD_FILE, filePath, uid);
  return 0;
}

int add_user (int argc, char** argv, int offset, char* result) {
  // First argument, second argument required. Third, fourth, fifth optional => default to 0
  if (reqd_opt (argc, offset, "FilePath") < 0) return -1;

  char filePath [MAX_FILE_PATH];
  get_file_path (argv, offset, filePath);
  if (filePath == NULL) return -1;

  int uid = get_uid (argc, argv, offset + 1);

  char* canRead;
  char* canWrite;
  char* canExec;

  optional_opt (argc, argv, offset + 2, "1", &canRead);
  optional_opt (argc, argv, offset + 3, "1", &canWrite);
  optional_opt (argc, argv, offset + 4, "1", &canExec);

  sprintf (result, "%s %s %d %s %s %s", CMD_ADD_USER, filePath, uid, canRead, canWrite, canExec);
  return 0;
}

int revoke_access (int argc, char** argv, int offset, char* result) {
  if (reqd_opt (argc, offset, "FilePath") < 0) return -1;

  char filePath [MAX_FILE_PATH];
  get_file_path (argv, offset, filePath);
  if (filePath == NULL) return -1;

  int uid = get_uid (argc, argv, offset + 1);

  sprintf (result, "%s %s %d", MSG_REVOKE_ACCESS, filePath, uid);
  return 0;
}

int remove_file_security (int argc, char** argv, int offset, char* result) {
  if (reqd_opt (argc, offset, "FilePath") < 0) return -1;

  char filePath [MAX_FILE_PATH];
  get_file_path (argv, offset, filePath);
  if (filePath == NULL) return -1;

  sprintf (result, "%s %s", CMD_REMOVE_FILE, filePath);
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

void get_file_path (char** argv, int index, char* result) {
  getAbsPath (argv [index], result);
}

int get_uid (int argc, char** argv, int index) {
  char* username = NULL;
  if (argc > index) username = argv[index];

  return getUserId (username);
}
