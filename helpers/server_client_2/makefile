default: build

CUR_DIRNAME := $(lastword $(subst /, ,$(subst \\,/,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))))
NAME=$(CUR_DIRNAME)
OUTDIR=./bin
OUTDIR_WIN=.\\bin
PWD=`pwd`
CL=cl.exe
CL_DBG_ARGS=/DEBUG /ZI /F5
GCC=gcc
GCC_DBG_ARGS=-ggdb
SERVER=server2
CLIENT=client2
INCLUDE_WIN=/I ./ /I ../server_client_0 /I ../server_client_1 /I ../crc16
INCLUDE_NIX=-I ./ -I ../server_client_0 -I ../server_client_1 -I ../crc16

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

build_windows_x86:
	@if not exist $(OUTDIR_WIN) mkdir $(OUTDIR_WIN)
	$(CL) .\\$(SERVER).cpp $(INCLUDE_WIN) /Fe${OUTDIR_WIN}\\$(SERVER)_x86_pe.exe /Fo${OUTDIR_WIN}\\$(SERVER).obj
	$(CL) .\\$(CLIENT).cpp $(INCLUDE_WIN) /Fe${OUTDIR_WIN}\\$(CLIENT)_x86_pe.exe /Fo${OUTDIR_WIN}\\$(CLIENT).obj
	$(CL) $(CL_DBG_ARGS) .\\$(SERVER).cpp $(INCLUDE_WIN) /Fe${OUTDIR_WIN}\\$(SERVER)_x86_pe_debug.exe /Fo${OUTDIR_WIN}\\$(SERVER).obj
	$(CL) $(CL_DBG_ARGS) .\\$(CLIENT).cpp $(INCLUDE_WIN) /Fe${OUTDIR_WIN}\\$(CLIENT)_x86_pe_debug.exe /Fo${OUTDIR_WIN}\\$(CLIENT).obj
	@if exist *.idb move *.idb $(OUTDIR_WIN)
	@if exist *.pdb move *.pdb $(OUTDIR_WIN)
clean_windows_x86:
	if exist ${OUTDIR_WIN}\\$(SERVER)_x86_pe* del ${OUTDIR_WIN}\\$(SERVER)_x86_pe*
	if exist ${OUTDIR_WIN}\\$(CLIENT)_x86_pe* del ${OUTDIR_WIN}\\$(CLIENT)_x86_pe*
rebuild_windows_x86: clean_windows_x86 build_windows_x86

build_windows: build_windows_x86
clean_windows: clean_windows_x86
rebuild_windows: rebuild_windows_x86

build_linux_x86:
	@mkdir -p $(OUTDIR)
	$(GCC) ./$(SERVER).cpp $(INCLUDE_NIX) -o ${OUTDIR}/$(SERVER)_x86_elf
	$(GCC) ./$(CLIENT).cpp $(INCLUDE_NIX) -o ${OUTDIR}/$(CLIENT)_x86_elf
	strip ${OUTDIR}/$(SERVER)_x86_elf
	strip ${OUTDIR}/$(CLIENT)_x86_elf
	$(GCC) $(GCC_DBG_ARGS) ./$(SERVER).cpp $(INCLUDE_NIX) -o ${OUTDIR}/$(SERVER)_x86_elf_debug
	$(GCC) $(GCC_DBG_ARGS) ./${CLIENT}.cpp $(INCLUDE_NIX) -o ${OUTDIR}/${CLIENT}_x86_elf_debug
clean_linux_x86:
	rm -f ${OUTDIR}/$(SERVER)_x86_elf*
	rm -f ${OUTDIR}/$(CLIENT)_x86_elf*
rebuild_linux_x86: clean_linux_x86 build_linux_x86

build_linux_arm:
	@mkdir -p $(OUTDIR)
	arm-linux-gnueabi-g++ -s $(SERVER).cpp $(INCLUDE_NIX) -o $(OUTDIR)/$(SERVER)_arm_elf_debug
	cp $(OUTDIR)/$(SERVER)_arm_elf_debug $(OUTDIR)/$(SERVER)_arm_elf
	arm-linux-gnueabi-strip $(OUTDIR)/$(SERVER)_arm_elf
	arm-linux-gnueabi-g++ -s $(CLIENT).cpp $(INCLUDE_NIX) -o $(OUTDIR)/$(CLIENT)_arm_elf_debug
	cp $(OUTDIR)/$(CLIENT)_arm_elf_debug $(OUTDIR)/$(CLIENT)_arm_elf
	arm-linux-gnueabi-strip $(OUTDIR)/$(CLIENT)_arm_elf
clean_linux_arm:
	rm -f $(OUTDIR)/$(SERVER)_arm_elf*
	rm -f $(OUTDIR)/$(CLIENT)_arm_elf*
rebuild_linux_arm: clean_linux_arm build_linux_arm

build_linux_ppc:
	@mkdir -p $(OUTDIR)
	powerpc-linux-gnu-g++ -s $(SERVER).cpp $(INCLUDE_NIX) -o $(OUTDIR)/$(SERVER)_ppc_elf_debug
	cp $(OUTDIR)/$(SERVER)_ppc_elf_debug $(OUTDIR)/$(SERVER)_ppc_elf
	powerpc-linux-gnu-strip $(OUTDIR)/$(SERVER)_ppc_elf
	powerpc-linux-gnu-g++ -s $(CLIENT).cpp $(INCLUDE_NIX) -o $(OUTDIR)/$(CLIENT)_ppc_elf_debug
	cp $(OUTDIR)/$(CLIENT)_ppc_elf_debug $(OUTDIR)/$(CLIENT)_ppc_elf
	powerpc-linux-gnu-strip $(OUTDIR)/$(CLIENT)_ppc_elf
clean_linux_ppc:
	rm -f $(OUTDIR)/$(SERVER)_ppc_elf*
	rm -f $(OUTDIR)/$(CLIENT)_ppc_elf*
rebuild_linux_ppc: clean_linux_ppc build_linux_ppc

build_in_docker_windows:
	@:

build_docker:
	$(DOCKER_BUILD)
run_docker: build_docker
	$(DOCKER_LAUNCH)

build_linux: build_linux_x86 build_linux_arm build_linux_ppc
clean_linux: clean_linux_x86 clean_linux_arm clean_linux_ppc
rebuild_linux: rebuild_linux_x86 rebuild_linux_arm rebuild_linux_ppc

build: $(BUILD_CMD)
clean: $(CLEAN_CMD)
rebuild: $(REBUILD_CMD)
