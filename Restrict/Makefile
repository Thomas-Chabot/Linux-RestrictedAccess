boot: restrict.so
	if ! grep -q 'export LD_PRELOAD="/secure_folder/app/restrict.so"' ~/.bashrc; then \
		sudo sed -i -e '$$i \export LD_PRELOAD="/secure_folder/app/restrict.so"\n' ~/.bashrc; \
	fi

restrict.so: restrict.o can_access.o
	gcc -shared -o restrict.so restrict_open.o can_access.o -lFifoReadWrite -ldl
	rm -f /secure_folder/app/restrict.so
	mv restrict.so /secure_folder/app/restrict.so

tester: tester.o can_access.o
	gcc -o tester tester.o can_access.o -lFifoReadWrite

restrict.o: restrict_open.c
	gcc -fPIC -Wall -c restrict_open.c -o restrict_open.o

can_access.o: can_access.c
	gcc -c can_access.c

tester.o: tester.c
	gcc -c tester.c

clean: cleanBoot
	rm -f *.o tester
	rm -f /secure_folder/app/restrict.so

cleanBoot:
	sudo sed -i '\/secure_folder/d' ~/.bashrc
