#ifndef ACCOUNTS_H
#define ACCOUNTS_H

#include "users.h"

int secure_folder_account_create (int); // userid
int secure_folder_account_exists (int); // userid
int* secure_folder_accounts_get (); // returns array[] of userids

#endif
