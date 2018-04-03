#include "secureFolder.h"

Node* main_list = NULL;

File* get_file (char*);
Permissions* get_user (File* file, int userId);
Permissions* create_user (int userId, int cr, int cw, int ce);
File* create_secure_file (char* fileId);

void delete_permissions (Node* permissions);
void delete_data (Node* list);
void do_delete (void* data);

int secure_file_exists (char* fileId) {
  return get_file (fileId) != NULL;
}

int user_can_access (char* fileId, int userId) {
  File* file = get_file (fileId);
  if (file == NULL) return 0;

  Permissions* user = get_user (file, userId);
  if (user == NULL) return 0;

  return user -> canRead || user -> canWrite;
}

int add_user_access (char* fileId, int userId, int cr, int cw, int ce) {
  File* file = get_file (fileId);
  if (file == NULL) return -1;

  Permissions* perms = create_user (userId, cr, cw, ce);
  list_push (&(file -> users), perms);

  return 0;
}

int add_to_secure_folder (char* fileId) {
  if (secure_file_exists (fileId)) return -1;

  File* file = create_secure_file (fileId);
  list_push (&main_list, file);

  return 0;
}

int remove_from_secure_folder (char* fileId) {
  File* file = get_file (fileId);
  if (file == NULL) return -1;

  delete_permissions (file -> users);
  delete_data (main_list);
  return list_remove (&main_list, file);
}

int revoke_access (char* fileId, int userId) {
  File* file = get_file (fileId);
  if (file == NULL) return -1;

  Permissions* user = get_user (file, userId);
  if (user == NULL) return -1;

  free (user);
  return list_remove (&(file -> users), user);
}

// Helper Functions
int isFile (void* element, void* fileId) {
  return *((char**)fileId) == ((File*)element) -> fileId;
}

int isUser (void* element, void* userId) {
  return ((Permissions*)element)->uid == *((int*)userId);
}

// Get file / user
File* get_file (char* fileId) {
  return list_get (main_list, isFile, &fileId);
}
Permissions* get_user (File* file, int userId) {
  if (file == NULL) return NULL;
  return list_get (file->users, isUser, &userId);
}

// Create user
Permissions* create_user (int userId, int cr, int cw, int ce) {
  Permissions* perms = malloc (sizeof (Permissions));

  perms -> uid = userId;
  perms -> canRead = cr;
  perms -> canWrite = cw;
  perms -> canExecute = ce;

  return perms;
}

File* create_secure_file (char* fileId) {
  File* file = malloc (sizeof (File));

  file -> fileId = fileId;
  file -> users = init_list ();

  return file;
}

// Delete a user
void delete_permissions (Node* permissions) {
  delete_data (permissions);
  delete_list (&permissions);
}

void delete_data (Node* list) {
  list_each (list, do_delete);
}
void do_delete (void* data){
  free (data);
}
