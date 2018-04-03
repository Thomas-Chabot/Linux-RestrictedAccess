all: tester.o
	gcc -o tester tester.o -lUsers

lib: users.o
	ar rcs libUsers.a users.o
	sudo mv libUsers.a /usr/lib/libUsers.a
	sudo cp users.h /usr/include/users.h

users.o: users.c
	gcc -c users.c

clean:
	rm -f *.o tester *~

cleanLib:
	sudo rm /usr/lib/libUsers.a
	sudo rm /usr/include/users.h
