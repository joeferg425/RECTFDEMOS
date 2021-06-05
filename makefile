default: build
%:
	$(MAKE) -C ./ctf1 $1
	$(MAKE) -C ./ctf2 $1
	$(MAKE) -C ./ctf3 $1
	$(MAKE) -C ./ctf4 $1
	$(MAKE) -C ./ctf5 $1
	$(MAKE) -C ./ctf6 $1
	$(MAKE) -C ./server_client_0 $1
	$(MAKE) -C ./server_client_1 $1
	$(MAKE) -C ./server_client_2 $1
