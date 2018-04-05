#ifndef SECURE_FOLDER_CONTENTS_H
#define SECURE_FOLDER_CONTENTS_H

#include <linkedList.h>
#include <fileIds.h>
#include <uuid/uuid.h>

//#include <linkedList.h>

#define FILE_ID_LEN UUID_LEN + 1

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

// Returns true if the file exists inside the secure folder, false otherwise.
int secure_file_exists (char* fileId);

// Returns true if the user has access to the given file.
int user_can_access (char* fileId, int userId);

// Gives the user access to the secure file
int add_user_access (char* fileId, int userId, int cr, int cw, int ce);

// Adds a secure file to the secure folder if it does not already exist
int add_to_secure_folder (char* fileId);

// Removes a secure file from the secure folder. This will also delete all user permissions
int remove_from_secure_folder (char* fileId);

// Revokes access to a secure file for a given user. This will completely remove their permissions (read, write, execute)
int revoke_access (char* fileId, int userId);

void secure_folder_save ();
void secure_folder_load ();

#endif
