boot: Triage
	if ! grep -q '/secure_folder/app/Triage &' '/etc/rc.local'; then \
		sudo sed -i -e '$$i \/secure_folder/app/Triage &\n' /etc/rc.local; \
	fi

run: Triage
	/secure_folder/app/Triage &

Triage: sf_pipes Connection.o helpers.o functions.o
		gcc -o Triage Connection.o functions.o helpers.o -lFifoReadWrite -lSecureFolder -lFileIds -luuid
		rm -f /secure_folder/app/Triage
		cp Triage /secure_folder/app/Triage

sf_pipes: sf_pipes.h
	sudo rm -f /usr/include/sf_pipes.h
	sudo cp sf_pipes.h /usr/include/sf_pipes.h

Connection.o: Connection.c
	gcc -c Connection.c

functions.o: functions.c
	gcc -c functions.c

helpers.o: helpers.c
	gcc -c helpers.c

clean: cleanBoot
	rm -f *.o Triage

cleanBoot:
	sudo sed -i '\/secure_folder/d' /etc/rc.local
