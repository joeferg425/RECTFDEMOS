default: build

NAME=ctf7
OUTDIR_NIX=./bin
OUTDIR_WIN=.\\bin
INCLUDE_NIX=-I ../md5
INCLUDE_WIN=/I ../md5

ifeq ($(OS),Windows_NT)
    detected_OS_clean := clean_windows
    detected_OS_build := build_windows
    detected_OS_rebuild := rebuild_windows
else
    detected_OS_clean := clean_linux
    detected_OS_build := build_linux
    detected_OS_rebuild := rebuild_linux
endif

install_linux:
	apt-get install gcc-powerpc-linux-gnu g++-powerpc-linux-gnu binutils-powerpc-linux-gnu
	apt-get install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi binutils-arm-linux-gnueabi

build_windows_x86:
	@if not exist $(OUTDIR_WIN) mkdir $(OUTDIR_WIN)
	cl.exe $(NAME).cpp $(INCLUDE_WIN) /Fe$(OUTDIR_WIN)\\$(NAME)_x86_pe.exe /Fo$(OUTDIR_WIN)\\$(NAME)_x86_pe.obj
	cl.exe $(NAME).cpp $(INCLUDE_WIN) /Fe$(OUTDIR_WIN)\\$(NAME)_x86_pe_debug.exe /Fo$(OUTDIR_WIN)\\$(NAME)_x86_pe_debug.obj  /DEBUG /ZI /F5
	@if exist .\\*.idb move .\\*.idb $(OUTDIR_WIN)\\
	@if exist .\\*.pdb move .\\*.pdb $(OUTDIR_WIN)\\
clean_windows_x86:
	@if exist $(OUTDIR_WIN)\\$(NAME)_x86_pe* del $(OUTDIR_WIN)\\$(NAME)_x86_pe*
rebuild_windows_x86: clean_windows_x86 build_windows_x86

build_linux_x86:
	@mkdir -p $(OUTDIR_NIX)
	g++ -s $(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_x86_elf_debug -g -fno-stack-protector
	g++ -s $(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_x86_elf -fno-stack-protector
	strip $(OUTDIR_NIX)/$(NAME)_x86_elf
clean_linux_x86:
	rm -f $(OUTDIR_NIX)/$(NAME)_x86_elf*
rebuild_linux_x86: clean_linux_x86 build_linux_x86

build_linux_arm:
	@mkdir -p $(OUTDIR_NIX)
	arm-linux-gnueabi-g++ -s $(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_arm_elf_debug -fno-stack-protector
	cp $(OUTDIR_NIX)/$(NAME)_arm_elf_debug $(OUTDIR_NIX)/$(NAME)_arm_elf
	arm-linux-gnueabi-strip $(OUTDIR_NIX)/$(NAME)_arm_elf
clean_linux_arm:
	rm -f $(OUTDIR_NIX)/$(NAME)_arm_elf*
rebuild_linux_arm: clean_linux_arm build_linux_arm

build_linux_ppc:
	@mkdir -p $(OUTDIR_NIX)
	powerpc-linux-gnu-g++ -s $(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_ppc_elf_debug -fno-stack-protector
	cp $(OUTDIR_NIX)/$(NAME)_ppc_elf_debug $(OUTDIR_NIX)/$(NAME)_ppc_elf
	powerpc-linux-gnu-strip $(OUTDIR_NIX)/$(NAME)_ppc_elf
clean_linux_ppc:
	rm -f $(OUTDIR_NIX)/$(NAME)_ppc_elf*
rebuild_linux_ppc: clean_linux_ppc build_linux_ppc

build_linux: build_linux_x86 build_linux_arm build_linux_ppc
clean_linux: clean_linux_x86 clean_linux_arm clean_linux_ppc
rebuild_linux: rebuild_linux_x86 rebuild_linux_arm rebuild_linux_ppc

build_windows: build_windows_x86
clean_windows: clean_windows_x86
rebuild_windows: rebuild_windows_x86

build: $(detected_OS_build)
clean: $(detected_OS_clean)
rebuild: $(detected_OS_rebuild)
