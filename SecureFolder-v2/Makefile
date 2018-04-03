SUBDIRS := $(wildcard */.)

lib: secureFolder.o linkedList.o
		ar rcs libsecurefolder.a secureFolder.o linked-list/linkedList.o
		sudo mv libsecurefolder.a /usr/lib/libsecurefolder.a
		sudo cp secureFolder.h /usr/include/secureFolder.h

tester: tester.o
	gcc -o tester tester.o -luuid -lsecurefolder

secureFolder.o: secureFolder.c
	gcc -c secureFolder.c

linkedList.o: linked-list/linkedList.c
	make lib -C linked-list/

tester.o: tester.c
	gcc -c tester.c

clean:
	rm -f *.o tester *.a *~ linked-list/*.o linked-list/tester linked-list/*~

cleanLib:
	rm /usr/lib/libsecurefolder.a
	rm /usr/include/secureFolder.h
