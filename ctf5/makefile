default: build

CUR_DIRNAME=$(shell basename "$(CURDIR)")
NAME=$(CUR_DIRNAME)
OUTDIR=./bin
OUTDIR_WIN=.\\bin

ifeq ($(OS),Windows_NT)
	CLEAN_CMD := clean_windows
	BUILD_CMD := build_windows
	REBUILD_CMD := rebuild_windows
	CONTAINER_EXISTS := $(shell docker ps -a | findstr $(NAME) > nul 2>&1 && echo %errorlevel%)
	IMAGE_EXISTS := $(shell docker image ls | findstr $(NAME)_img > nul 2>&1 && echo %errorlevel%)
	DOCKER_BUILD_CMD := cd .. & docker build . -f $(NAME)\\dockerfile -t $(NAME)_img --build-arg NAME=$(NAME)
else
	CLEAN_CMD := clean_linux
	BUILD_CMD := build_linux
	REBUILD_CMD := rebuild_linux
	CONTAINER_EXISTS := $(shell docker ps -a | grep $(NAME) 2>&1 > /dev/null ; echo $$?)
	IMAGE_EXISTS := $(shell docker image ls | grep $(NAME)_img 2>&1 > /dev/null ; echo $$?)
	DOCKER_BUILD_CMD := cd .. ; docker build . -f ./$(NAME)/dockerfile -t $(NAME)_img --build-arg NAME=$(NAME)
endif

ifeq ($(CONTAINER_EXISTS), 0)
	DOCKER_LAUNCH := docker start --attach -i $(NAME)
else
	DOCKER_LAUNCH := docker run -it --name $(NAME) $(NAME)_img
endif

ifeq ($(IMAGE_EXISTS), 0)
	DOCKER_BUILD := @echo "image already built"
else
	DOCKER_BUILD := $(DOCKER_BUILD_CMD)
endif

install_linux:
	apt-get install gcc-powerpc-linux-gnu g++-powerpc-linux-gnu binutils-powerpc-linux-gnu
	apt-get install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi binutils-arm-linux-gnueabi

build_windows_helper:
	@if not exist $(OUTDIR_WIN) mkdir $(OUTDIR_WIN)
	cl.exe obfuscate5.cpp /Fe$(OUTDIR_WIN)\\obfuscate5.exe /Fo$(OUTDIR_WIN)\\obfuscate5.obj

build_linux_helper:
	@mkdir -p $(OUTDIR)
	gcc obfuscate5.cpp -o $(OUTDIR)/obfuscate5

build_windows_x86:
	@if not exist $(OUTDIR_WIN) mkdir $(OUTDIR_WIN)
	cl.exe $(NAME).cpp /Fe$(OUTDIR_WIN)\\$(NAME)_x86_pe.exe /Fo$(OUTDIR_WIN)\\$(NAME)_x86_pe.obj
	cl.exe /DEBUG /ZI /F5 $(NAME).cpp /Fe$(OUTDIR_WIN)\\$(NAME)_x86_pe_debug.exe /Fo$(OUTDIR_WIN)\\$(NAME)_x86_pe_debug.obj
	@if exist .\\*.idb move .\\*.idb $(OUTDIR_WIN)\\
	@if exist .\\*.pdb move .\\*.pdb $(OUTDIR_WIN)\\
clean_windows_x86:
	@if exist $(OUTDIR_WIN)\\$(NAME)_x86_pe* del $(OUTDIR_WIN)\\$(NAME)_x86_pe*
rebuild_windows_x86: clean_windows_x86 build_windows_x86

build_linux_x86:
	@mkdir -p $(OUTDIR)
	g++ -s $(NAME).cpp -o $(OUTDIR)/$(NAME)_x86_elf_debug -g
	g++ -s $(NAME).cpp -o $(OUTDIR)/$(NAME)_x86_elf
	strip $(OUTDIR)/$(NAME)_x86_elf
clean_linux_x86:
	rm -f $(OUTDIR)/$(NAME)_x86_elf*
rebuild_linux_x86: clean_linux_x86 build_linux_x86

build_linux_arm:
	@mkdir -p $(OUTDIR)
	arm-linux-gnueabi-g++ -s $(NAME).cpp -o $(OUTDIR)/$(NAME)_arm_elf_debug
	cp $(OUTDIR)/$(NAME)_arm_elf_debug $(OUTDIR)/$(NAME)_arm_elf
	arm-linux-gnueabi-strip $(OUTDIR)/$(NAME)_arm_elf
clean_linux_arm:
	rm -f $(OUTDIR)/$(NAME)_arm_elf*
rebuild_linux_arm: clean_linux_arm build_linux_arm

build_linux_ppc:
	@mkdir -p $(OUTDIR)
	powerpc-linux-gnu-g++ -s $(NAME).cpp -o $(OUTDIR)/$(NAME)_ppc_elf_debug
	cp $(OUTDIR)/$(NAME)_ppc_elf_debug $(OUTDIR)/$(NAME)_ppc_elf
	powerpc-linux-gnu-strip $(OUTDIR)/$(NAME)_ppc_elf
clean_linux_ppc:
	rm -f $(OUTDIR)/$(NAME)_ppc_elf*
rebuild_linux_ppc: clean_linux_ppc build_linux_ppc

build_docker:
	$(DOCKER_BUILD)
run_docker: build_docker
	$(DOCKER_LAUNCH)

build_linux: build_linux_x86 build_linux_arm build_linux_ppc
clean_linux: clean_linux_x86 clean_linux_arm clean_linux_ppc
rebuild_linux: rebuild_linux_x86 rebuild_linux_arm rebuild_linux_ppc

build_windows: build_windows_x86
clean_windows: clean_windows_x86
rebuild_windows: rebuild_windows_x86

build: $(BUILD_CMD)
clean: $(CLEAN_CMD)
rebuild: $(REBUILD_CMD)
