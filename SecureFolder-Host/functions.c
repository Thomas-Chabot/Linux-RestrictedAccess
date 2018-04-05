#include <secureFolder.h>
#include "helpers.h"

#define MAX_PATH_LEN 40

int f_add_user (char* fileId, char* s) {
  int uid      = read_int (&s);
  int canRead  = read_int (&s);
  int canWrite = read_int (&s);
  int canExec  = read_int (&s);

  // in case not already in the secure folder
  add_to_secure_folder (fileId);

  // add the user Permissions
  int status = add_user_access (fileId, uid, canRead, canWrite, canExec);

  return status == 0;
}

int f_revoke_access (char* fileId, char* s) {
  int uid = read_int (&s);

  int canAccess = user_can_access (fileId, uid);
  if (!canAccess) return 0;

  int status = revoke_access (fileId, uid);
  return status == 0;
}

int f_user_can_access (char* fileId, char* s) {
  int uid = read_int (&s);
  return user_can_access (fileId, uid);
}

int f_remove_file_security (char* fileId, char* s) {
  int result = remove_from_secure_folder (fileId);
  return result == 0;
}
