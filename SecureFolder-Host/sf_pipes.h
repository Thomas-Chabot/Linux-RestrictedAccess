#ifndef SF_PIPES_H
#define SF_PIPES_H

#define SERVER_FIFO "/secure_folder/pipes/toServer"
#define SERVER_RETURN_PIPE "/secure_folder/pipes/fromServer"

#define MAX_COMMAND_LEN 4096
#define MAX_FILE_PATH 4096

#define CMD_ADD_FILE "add_file"
#define CMD_ADD_USER "add_user"
#define CMD_REVOKE_ACCESS "revoke_access"
#define CMD_CAN_ACCESS "user_can_access"
#define CMD_REMOVE_FILE "remove_file_security"


#endif
