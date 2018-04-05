#ifndef FILE_IDS_H
#define FILE_IDS_H

#include <sys/xattr.h>
#include <uuid/uuid.h>
#include <string.h>

#define UUID_LEN 36

void get_file_id (const char *pathname, char* result);

#endif
