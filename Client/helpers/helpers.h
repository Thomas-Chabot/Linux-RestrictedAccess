#ifndef HELPERS_H
#define HELPERS_H

/* getUserId: returns -1 on failure & userID otherwise */
int getUserId (char* username);
char* strlower (char* string); // Note: returns the same string
int getAbsPath (char* relPath, char* result);

#endif
