.PHONY: compile
.DEFAULT: compile

#sudo mkdir /mnt/v
#sudo mount -t drvfs V: /mnt/v

install:
	apt-get install gcc-powerpc-linux-gnu g++-powerpc-linux-gnu binutils-powerpc-linux-gnu
	apt-get install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi binutils-arm-linux-gnueabi 
	
compile:
	g++ -s CTF6.c -o CTF6_x86_elf -fno-stack-protector
	cp CTF6_x86_elf CTF6_x86_elf_stripped
	strip CTF6_x86_elf_stripped
	arm-linux-gnueabi-g++ -s CTF6.c -o CTF6_arm_elf -fno-stack-protector
	cp CTF6_arm_elf CTF6_arm_elf_stripped
	arm-none-eabi-strip CTF6_arm_elf_stripped
	powerpc-linux-gnu-g++ -s CTF6.c -o CTF6_ppc_elf -fno-stack-protector
	cp CTF6_ppc_elf CTF6_ppc_elf_stripped
	powerpc-linux-gnu-strip CTF6_ppc_elf_stripped
