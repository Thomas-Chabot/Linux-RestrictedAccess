#ifndef SECURE_FOLDER_PERSISTENCE_H
#define SECURE_FOLDER_PERSISTENCE_H

#define DEF_SAVE_LOC "/home/student/Documents/Testing/secure_folder_contents.txt"

void do_sf_save (Node* list, char* saveFile, int fileSize);
void do_sf_load (char* saveFile);
int get_sf_size (Node* folderList);

#endif
