#ifndef SECURE_FOLDER_CONTENTS_H
#define SECURE_FOLDER_CONTENTS_H

// NOTE: This should probably be ported to a library.
#include <linkedList.h>
#include <uuid/uuid.h>

//#include <linkedList.h>

typedef struct {
  int uid;
  int canRead;
  int canWrite;
  int canExecute;
} Permissions;

typedef struct {
  char* fileId;
  Node* users; // NOTE: data for this list MUST be of the Permissions type
} File;

int secure_file_exists (char* fileId);
int user_can_access (char* fileId, int userId);
int add_user_access (char* fileId, int userId, int cr, int cw, int ce);
int add_to_secure_folder (char* fileId);
int remove_from_secure_folder (char* fileId);
int revoke_access (char* fileId, int userId);

#endif
