install:
	apt-get install build-essential gcc-powerpc-linux-gnu g++-powerpc-linux-gnu binutils-powerpc-linux-gnu gcc-arm-linux-gnueabi g++-arm-linux-gnueabi binutils-arm-linux-gnueabi

%:
	$(MAKE) -C ./ctfs/ctf1 $@
	$(MAKE) -C ./ctfs/ctf2 $@
	$(MAKE) -C ./ctfs/ctf3 $@
	$(MAKE) -C ./ctfs/ctf4 $@
	$(MAKE) -C ./ctfs/ctf5 $@
	$(MAKE) -C ./ctfs/ctf6 $@
	$(MAKE) -C ./helpers/obfuscate1 $@
	$(MAKE) -C ./helpers/obfuscate2 $@
	$(MAKE) -C ./helpers/obfuscate3 $@
	$(MAKE) -C ./helpers/obfuscate4 $@
	$(MAKE) -C ./helpers/obfuscate5 $@
	$(MAKE) -C ./helpers/crc16 $@
	$(MAKE) -C ./helpers/md5 $@
	$(MAKE) -C ./helpers/server_client_2 $@
	$(MAKE) -C ./helpers/server_client_1 $@
	$(MAKE) -C ./helpers/server_client_0 $@
