# Linux Restricted Access

## Purpose
This is a simple system designed to restrict access to various files on Linux. Restricting access allows certain designated users to see a file while others will see it as an empty document. The system currently has support for both files & directories.

## Setup
### Dependencies
Use of this software requires the uuid-dev library. To install, run the following from a terminal:
```sudo apt-get install uuid-dev```

Once completed, the software can be installed to your device.

### Installation
Use ```sudo make``` to make the program. Root access is required by the installation in order to install the necessary programs and libraries.

The computer must be rebooted after installation for everything to work correctly.


## Usage
### Adding & Removing Restricted Access
The client program can be used to add & remove access to files.

The client program can be accessed from the terminal using the command secure_folder. This will print out a list of available uses.

In order to make a change to the system, enter a command such as:

```secure_folder add_user /path/to/file User1```

Which will add access to the file given at /path/to/file for the user User1. All other users will be restricted from using the file. More options are available as well; these can be all be printed out by the client program by calling secure_folder.

### Restricted Access
When a file is in the Secure Folder, access to the file will be restricted to specific users. In the example above, only the user User1 will be able to access the file /path/to/file.

This is separate from any other file system logic implemented in Linux; in order for a user to access a file, they must first have read access by default. The restricted access program will not override this.
