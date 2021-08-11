default: build

CUR_DIRNAME := $(lastword $(subst /, ,$(subst \\,/,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))))
NAME=$(CUR_DIRNAME)
OUTDIR_NIX=./bin
OUTDIR_WIN_ESCAPED=.\\bin
INCLUDE_NIX=-I ./ -I ../
INCLUDE_WIN_ESCAPED=/I .\\ /I ..\\

ifeq ($(CUR_DIRNAME), "RECTFDEMOS")
	CHANGE_DIR := cd .
else
	CHANGE_DIR := cd ..
endif

ifeq ($(OS),Windows_NT)
	CLEAN_CMD := clean_windows
	BUILD_CMD := build_windows
	REBUILD_CMD := rebuild_windows
	EXISTS_NIX_CONTAINER := $(shell docker ps -a | findstr $(NAME) > nul 2>&1 && echo %errorlevel%)
	EXISTS_NIX_IMAGE := $(shell docker image ls | findstr $(NAME)_img > nul 2>&1 && echo %errorlevel%)
	DOCKER_NIX_BUILD_CMD := $(CHANGE_DIR) & docker build . -f $(NAME)\\dockerfile -t $(NAME)_img --build-arg NAME=$(NAME)
else
	CLEAN_CMD := clean_linux
	BUILD_CMD := build_linux
	REBUILD_CMD := rebuild_linux
	EXISTS_NIX_CONTAINER := $(shell docker ps -a | grep $(NAME) 2>&1 > /dev/null ; echo $$?)
	EXISTS_NIX_IMAGE := $(shell docker image ls | grep $(NAME)_img 2>&1 > /dev/null ; echo $$?)
	DOCKER_NIX_BUILD_CMD := $(CHANGE_DIR) ; docker build . -f ./$(NAME)/dockerfile -t $(NAME)_img --build-arg NAME=$(NAME)
endif

ifeq ($(EXISTS_NIX_CONTAINER), 0)
	NIX_DOCKER_LAUNCH := docker start --attach -i $(NAME)
else
	NIX_DOCKER_LAUNCH := docker run -it --name $(NAME) $(NAME)_img
endif

ifeq ($(EXISTS_NIX_IMAGE), 0)
	NIX_DOCKER_BUILD := @echo "image already built"
else
	NIX_DOCKER_BUILD := $(DOCKER_NIX_BUILD_CMD)
endif

install_linux:
	apt-get install gcc-powerpc-linux-gnu g++-powerpc-linux-gnu binutils-powerpc-linux-gnu
	apt-get install gcc-arm-linux-gnueabi g++-arm-linux-gnueabi binutils-arm-linux-gnueabi

build_windows_x86:
	@if not exist $(OUTDIR_WIN_ESCAPED) mkdir $(OUTDIR_WIN_ESCAPED)
	cl.exe $(NAME).cpp $(INCLUDE_WIN_ESCAPED) /Fe$(OUTDIR_WIN_ESCAPED)\\$(NAME)_x86_pe.exe /Fo$(OUTDIR_WIN_ESCAPED)\\$(NAME)_x86_pe.obj
	cl.exe /DEBUG /ZI /F5 $(NAME).cpp $(INCLUDE_WIN_ESCAPED) /Fe$(OUTDIR_WIN_ESCAPED)\\$(NAME)_x86_pe_debug.exe /Fo$(OUTDIR_WIN_ESCAPED)\\$(NAME)_x86_pe_debug.obj
	@if exist .\\*.idb move .\\*.idb $(OUTDIR_WIN_ESCAPED)\\
	@if exist .\\*.pdb move .\\*.pdb $(OUTDIR_WIN_ESCAPED)\\
clean_windows_x86:
	@if exist $(OUTDIR_WIN_ESCAPED)\\$(NAME)_x86_pe* del $(OUTDIR_WIN_ESCAPED)\\$(NAME)_x86_pe*
rebuild_windows_x86: clean_windows_x86 build_windows_x86

build_linux_x86:
	@mkdir -p $(OUTDIR_NIX)
	g++ -s $(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_x86_elf_debug -g
	g++ -s $(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_x86_elf
	strip $(OUTDIR_NIX)/$(NAME)_x86_elf
clean_linux_x86:
	rm -f $(OUTDIR_NIX)/$(NAME)_x86_elf*
rebuild_linux_x86: clean_linux_x86 build_linux_x86

build_linux_arm:
	@mkdir -p $(OUTDIR_NIX)
	arm-linux-gnueabi-g++ -s $(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_arm_elf_debug
	cp $(OUTDIR_NIX)/$(NAME)_arm_elf_debug $(OUTDIR_NIX)/$(NAME)_arm_elf
	arm-linux-gnueabi-strip $(OUTDIR_NIX)/$(NAME)_arm_elf
clean_linux_arm:
	rm -f $(OUTDIR_NIX)/$(NAME)_arm_elf*
rebuild_linux_arm: clean_linux_arm build_linux_arm

build_linux_ppc:
	@mkdir -p $(OUTDIR_NIX)
	powerpc-linux-gnu-g++ -s $(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_ppc_elf_debug
	cp $(OUTDIR_NIX)/$(NAME)_ppc_elf_debug $(OUTDIR_NIX)/$(NAME)_ppc_elf
	powerpc-linux-gnu-strip $(OUTDIR_NIX)/$(NAME)_ppc_elf
clean_linux_ppc:
	rm -f $(OUTDIR_NIX)/$(NAME)_ppc_elf*
rebuild_linux_ppc: clean_linux_ppc build_linux_ppc

build_in_docker_windows:
	@:

build_linux_docker:
	$(NIX_DOCKER_BUILD)
run_linux_docker: build_linux_docker
	$(NIX_DOCKER_LAUNCH)

build_linux: build_linux_x86 build_linux_arm build_linux_ppc
clean_linux: clean_linux_x86 clean_linux_arm clean_linux_ppc
rebuild_linux: rebuild_linux_x86 rebuild_linux_arm rebuild_linux_ppc

build_windows: build_windows_x86
clean_windows: clean_windows_x86
rebuild_windows: rebuild_windows_x86

build: $(BUILD_CMD)
clean: $(CLEAN_CMD)
rebuild: $(REBUILD_CMD)
