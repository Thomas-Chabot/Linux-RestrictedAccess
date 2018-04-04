all: FolderSize.o FolderSave.o FolderLoad.o shared.o
	ar rcs libPersistence.a FolderSize.o FolderSave.o FolderLoad.o shared.o

shared.o: shared.c
	gcc -c shared.c

FolderSize.o: FolderSize.c
	gcc -c FolderSize.c

FolderSave.o: FolderSave.c
	gcc -c FolderSave.c

FolderLoad.o: FolderLoad.c
	gcc -c FolderLoad.c

clean:
	rm -f *.o libPersistence.a
