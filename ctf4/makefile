.PHONY: compile
.DEFAULT: compile

#sudo mkdir /mnt/v
#sudo mount -t drvfs V: /mnt/v

install:
	apt-get install gcc-powerpc-linux-gnu g++-powerpc-linux-gnu binutils-powerpc-linux-gnu
	apt-get install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi binutils-arm-linux-gnueabi 
	
compile:
	g++ -s CTF4.c -o CTF4_x86_elf
	cp CTF4_x86_elf CTF4_x86_elf_stripped
	strip CTF4_x86_elf_stripped
	arm-linux-gnueabi-g++ -s CTF4.c -o CTF4_arm_elf
	cp CTF4_arm_elf CTF4_arm_elf_stripped
	arm-none-eabi-strip CTF4_arm_elf_stripped
	powerpc-linux-gnu-g++ -s CTF4.c -o CTF4_ppc_elf
	cp CTF4_ppc_elf CTF4_ppc_elf_stripped
	powerpc-linux-gnu-strip CTF4_ppc_elf_stripped

	
