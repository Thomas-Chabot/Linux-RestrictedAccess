all:
	sudo mkdir -p /secure_folder
	sudo mkdir -p /secure_folder/data
	sudo mkdir -p /secure_folder/app
	sudo mkdir -p /secure_folder/pipes
	sudo chmod -R 777 /secure_folder

	sudo make -C data-structures/linked-list
	sudo make -C Fifo/
	sudo make -C FileIds/
	sudo make -C Users/
	sudo make -C SecureFolder-Main/
	sudo make -C SecureFolder-Host/
	sudo make -C Client/
	sudo make -C Restrict/

	echo "Please reboot to complete installation."

clean:
	sudo rm -r -f /secure_folder
	sudo make clean -C data-structures/linked-list
	sudo make clean -C Fifo/
	sudo make clean -C FileIds/
	sudo make clean -C Users/
	sudo make clean -C SecureFolder-Main/
	sudo make clean -C SecureFolder-Host/
	sudo make clean -C Client/
	sudo make clean -C Restrict/
