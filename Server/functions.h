#ifndef SECURE_FOLDER_FUNCTIONS_H
#define SECURE_FOLDER_FUNCTIONS_H

int f_add_file (char* fileId, char* s);
int f_add_user (char* fileId, char* s);
int f_revoke_access (char* fileId, char* s);
int f_user_can_access (char* fileId, char* s);
int f_remove_file_security (char* fileId, char* s);

#endif
