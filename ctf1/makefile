.PHONY: compile
.DEFAULT: compile

#sudo mkdir /mnt/v
#sudo mount -t drvfs V: /mnt/v

install:
	apt-get install gcc-powerpc-linux-gnu g++-powerpc-linux-gnu binutils-powerpc-linux-gnu
	apt-get install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi binutils-arm-linux-gnueabi 
	
compile:
	g++ -s CTF1.c -o CTF1_x86_elf -g 
	g++ -s CTF1.c -o CTF1_x86_elf_stripped 
	cp CTF1_x86_elf CTF1_x86_elf_stripped
	strip CTF1_x86_elf_stripped
	arm-linux-gnueabi-g++ -s CTF1.c -o CTF1_arm_elf
	cp CTF1_arm_elf CTF1_arm_elf_stripped
	arm-none-eabi-strip CTF1_arm_elf_stripped
	powerpc-linux-gnu-g++ -s CTF1.c -o CTF1_ppc_elf
	cp CTF1_ppc_elf CTF1_ppc_elf_stripped
	powerpc-linux-gnu-strip CTF1_ppc_elf_stripped
	
	
