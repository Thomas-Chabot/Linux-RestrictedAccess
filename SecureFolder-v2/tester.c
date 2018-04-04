#include <uuid/uuid.h>
#include <stdio.h>
#include <secureFolder.h>

int main () {
  char* uuid = "the-maniacal-georgie";
  char* uuid1 = "my-name-is-pennywise";
  char* uuid2 = "strangers-smaller";

  int userId = 15;
  int userId2 = 16;

  if (add_to_secure_folder (uuid) < 0) {
    fprintf (stderr, "ERROR ADDING UUID TO SECURE FOLDER");
    return 0;
  };

  fprintf (stdout, "Secure file exists? %d\n", secure_file_exists (uuid));
  fprintf (stdout, "User %d has access? %d\n", userId, user_can_access(uuid, userId));
  fprintf (stdout, "User %d has access? %d\n", userId, user_can_access(uuid, userId2));

  if (add_user_access (uuid, userId, 1, 1, 1) < 0) {
    fprintf (stderr, "ERROR ADDING USER ACCESS");
    return 0;
  };

  fprintf (stdout, "AFTER ADDING USER ACCESS:\n");
  fprintf (stdout, "Secure file exists? %d\n", secure_file_exists (uuid));
  fprintf (stdout, "User %d has access? %d\n", userId, user_can_access(uuid, userId));
  fprintf (stdout, "User %d has access? %d\n", userId, user_can_access(uuid, userId2));

  if (add_user_access (uuid, userId2, 1, 0, 0) < 0) {
    fprintf (stderr, "ERROR ADDING USER ACCESS");
    return 0;
  };

  fprintf (stdout, "AFTER ADDING USER ACCESS:\n");
  fprintf (stdout, "Secure file exists? %d\n", secure_file_exists (uuid));
  fprintf (stdout, "User %d has access? %d\n", userId, user_can_access(uuid, userId));
  fprintf (stdout, "User %d has access? %d\n", userId, user_can_access(uuid, userId2));

  if (revoke_access (uuid, userId) < 0) {
    fprintf (stderr, "ERROR REMOVING NODE\n");
    return 0;
  }

  fprintf (stdout, "Successfully removed\n");
  fprintf (stdout, "Secure file exists? %d\n", secure_file_exists (uuid));
  fprintf (stdout, "User %d has access? %d\n", userId, user_can_access(uuid, userId));
  fprintf (stdout, "User %d has access? %d\n", userId, user_can_access(uuid, userId2));

  if (remove_from_secure_folder (uuid) < 0) {
    fprintf (stderr, "ERROR REMOVING FILE\n");
    return 0;
  }

  fprintf (stdout, "Successfully removed\n");
  fprintf (stdout, "Secure file exists? %d\n", secure_file_exists (uuid));
  fprintf (stdout, "User %d has access? %d\n", userId, user_can_access(uuid, userId));
  fprintf (stdout, "User %d has access? %d\n", userId, user_can_access(uuid, userId2));




  if (add_to_secure_folder (uuid) < 0) {
    fprintf (stderr, "ERROR ADDING UUID TO SECURE FOLDER");
    return 0;
  };
  if (add_to_secure_folder (uuid1) < 0) {
    fprintf (stderr, "ERROR ADDING UUID1 TO SECURE FOLDER");
    return 0;
  };
  if (add_to_secure_folder (uuid2) < 0) {
    fprintf (stderr, "ERROR ADDING UUID2 TO SECURE FOLDER");
    return 0;
  };

  if (add_user_access (uuid, userId2, 1, 0, 0) < 0) {
    fprintf (stderr, "ERROR ADDING USER ACCESS");
    return 0;
  };
  if (add_user_access (uuid, userId, 1, 0, 0) < 0) {
    fprintf (stderr, "ERROR ADDING USER ACCESS");
    return 0;
  };
  if (add_user_access (uuid1, userId, 1, 0, 0) < 0) {
    fprintf (stderr, "ERROR ADDING USER ACCESS");
    return 0;
  };

  fprintf (stdout, "FILE EXISTS: %d\n", secure_file_exists(uuid));
  fprintf (stdout, "RUNNING THE SAVING TESTS\n");

  secure_folder_save();
  secure_folder_clear();

  fprintf (stdout, "EVERYTHING IS SAVED\n");
}
