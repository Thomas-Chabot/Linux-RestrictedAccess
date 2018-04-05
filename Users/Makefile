lib: users.o
	ar rcs libUsers.a users.o
	sudo mv libUsers.a /usr/lib/libUsers.a
	sudo cp users.h /usr/include/users.h

test: tester.o
	gcc -o tester tester.o -lUsers


users.o: users.c
	gcc -c users.c

clean: cleanLib
	rm -f *.o tester *~

cleanLib:
	sudo rm -f /usr/lib/libUsers.a
	sudo rm -f /usr/include/users.h
