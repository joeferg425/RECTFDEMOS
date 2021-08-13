install:
	apt-get install build-essential gcc-powerpc-linux-gnu g++-powerpc-linux-gnu binutils-powerpc-linux-gnu gcc-arm-linux-gnueabi g++-arm-linux-gnueabi binutils-arm-linux-gnueabi

%:
	$(MAKE) -C ./ctfs/ctf1 $@
	$(MAKE) -C ./ctfs/ctf2 $@
	$(MAKE) -C ./ctfs/ctf3 $@
	$(MAKE) -C ./ctfs/ctf4 $@
	$(MAKE) -C ./ctfs/ctf5 $@
	$(MAKE) -C ./ctfs/ctf6 $@
	$(MAKE) -C ./ctfs/ctf7 $@
	$(MAKE) -C ./helpers/char2int $@
	$(MAKE) -C ./helpers/char2int_scaled $@
	$(MAKE) -C ./helpers/char2byte_offset $@
	$(MAKE) -C ./helpers/char2byte_xor $@
	$(MAKE) -C ./helpers/crclike $@
	$(MAKE) -C ./helpers/crc16 $@
	$(MAKE) -C ./helpers/md5 $@
	$(MAKE) -C ./helpers/server_client_2 $@
	$(MAKE) -C ./helpers/server_client_1 $@
	$(MAKE) -C ./helpers/server_client_0 $@
