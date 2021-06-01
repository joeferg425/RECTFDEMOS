.PHONY: compile
.DEFAULT: compile

#sudo mkdir /mnt/v
#sudo mount -t drvfs V: /mnt/v

install:
	apt-get install gcc-powerpc-linux-gnu g++-powerpc-linux-gnu binutils-powerpc-linux-gnu
	apt-get install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi binutils-arm-linux-gnueabi 
	
compile:
	g++ -s CTF2.cpp -o CTF2_x86_elf
	cp CTF2_x86_elf CTF2_x86_elf_stripped
	strip CTF2_x86_elf_stripped	
	arm-linux-gnueabi-g++ -s CTF2.cpp -o CTF2_arm_elf
	cp CTF2_arm_elf CTF2_arm_elf_stripped
	arm-none-eabi-strip CTF2_arm_elf_stripped
	powerpc-linux-gnu-g++ -s CTF2.cpp -o CTF2_ppc_elf
	cp CTF2_ppc_elf CTF2_ppc_elf_stripped
	powerpc-linux-gnu-strip CTF2_ppc_elf_stripped

	
