#ifndef CONNECTION_H
#define CONNECTION_H

#include <stdio.h>
#include <fileIds.h>
#include <sf_pipes.h>
#include "functions.h"
#include "helpers.h"

#define MAX_CALL_LEN 21
#define MAX_FILE_PATH 4096

#define CMD_ADD_USER "add_user"
#define CMD_REVOKE_ACCESS "revoke_access"
#define CMD_CAN_ACCESS "user_can_access"
#define CMD_REMOVE_FILE "remove_file_security"

#endif
