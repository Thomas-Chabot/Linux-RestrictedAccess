SUBDIRS := $(wildcard */.)

lib: secureFolder.o linkedList.o Persistence.o
		ar rcs libSecureFolder.a Persistence/FolderSize.o Persistence/FolderSave.o Persistence/FolderLoad.o Persistence/shared.o secureFolder.o linked-list/linkedList.o
		sudo mv libSecureFolder.a /usr/lib/libSecureFolder.a
		sudo cp secureFolder.h /usr/include/secureFolder.h

tester: tester.o
	gcc -o tester tester.o -luuid -lSecureFolder

tester2: tester.o secureFolder.o linkedList.o Persistence.o
	gcc -o tester tester.o secureFolder.o Persistence/libPersistence.a linked-list/linkedList.o

tester3: tester2.o secureFolder.o linkedList.o Persistence.o
	gcc -o tester tester2.o secureFolder.o linked-list/linkedList.o Persistence/libPersistence.a

Persistence.o:
	make -C Persistence/

secureFolder.o: secureFolder.c
	gcc -c secureFolder.c

linkedList.o: linked-list/linkedList.c
	make lib -C linked-list/

tester.o: tester.c
	gcc -c tester.c

tester2.o: tester2.c
	gcc -c tester2.c

clean:
	rm -f *.o tester *.a *~
	make clean -C linked-list/
	make clean -C Persistence/

cleanLib:
	rm /usr/lib/libSecureFolder.a
	rm /usr/include/secureFolder.h
