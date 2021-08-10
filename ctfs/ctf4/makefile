default: build

MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
RECTF_DIR_ := $(abspath $(MKFILE_PATH)/../../../ )
RECTF_DIR:=$(strip $(subst ^, ,$(lastword $(subst /C:/, C:/,$(subst  ,^,$(RECTF_DIR_))))))
CUR_DIRNAME := $(lastword $(subst /, ,$(subst \\,/,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))))
NAME=$(CUR_DIRNAME)
OUTDIR_NIX=$(RECTF_DIR)/ctfs/$(NAME)/bin
OUTDIR_WIN=$(subst /,\\,$(RECTF_DIR))\\ctfs\\$(NAME)\\bin
SOURCE_NIX=$(RECTF_DIR)/ctfs/$(NAME)/src
SOURCE_WIN=$(subst /,\\,$(RECTF_DIR))\\ctfs\\$(NAME)\\src
INCLUDE_NIX=-I $(RECTF_DIR)/helpers -I $(RECTF_DIR)/helpers/char2byte_xor
INCLUDE_WIN=/I $(subst /,\\,$(RECTF_DIR))\\helpers /I $(subst /,\\,$(RECTF_DIR))\\helpers\\char2byte_xor
DOCKER_INCLUDE_NIX:=-I RECTFDEMOS/helpers -I RECTFDEMOS/helpers/char2byte_xor
DOCKER_INCLUDE_WIN:=/I RECTFDEMOS\\helpers /I RECTFDEMOS\\helpers\\char2byte_xor

ifeq ($(OS),Windows_NT)
	CLEAN_CMD := clean_windows
	BUILD_CMD := build_windows
	REBUILD_CMD := rebuild_windows
	CONTAINER_EXISTS := $(shell docker ps -a | findstr $(NAME) > nul 2>&1 && echo %errorlevel%)
	IMAGE_EXISTS := $(shell docker image ls | findstr $(NAME)_img > nul 2>&1 && echo %errorlevel%)
	ifeq ($(CUR_DIRNAME), "ctfs")
		CHANGE_DIR := cd .
	else
		CHANGE_DIR := cd ..\\..
	endif
	DOCKER_BUILD_CMD := $(CHANGE_DIR) & docker build . -f ctfs\\$(NAME)\\dockerfile -t $(NAME)_img --build-arg NAME=$(NAME)
else
	CLEAN_CMD := clean_linux
	BUILD_CMD := build_linux
	REBUILD_CMD := rebuild_linux
	CONTAINER_EXISTS := $(shell docker ps -a | grep $(NAME) 2>&1 > /dev/null ; echo $$?)
	IMAGE_EXISTS := $(shell docker image ls | grep $(NAME)_img 2>&1 > /dev/null ; echo $$?)
	ifeq ($(CUR_DIRNAME), "ctfs")
		CHANGE_DIR := cd .
	else
		CHANGE_DIR := cd ../..
	endif
	DOCKER_BUILD_CMD := $(CHANGE_DIR) ; docker build . -f ./ctfs/$(NAME)/dockerfile -t $(NAME)_img --build-arg NAME=$(NAME)
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
	cl.exe $(SOURCE_WIN)\\$(NAME).cpp $(INCLUDE_WIN) /Fe$(OUTDIR_WIN)\\$(NAME)_x86_pe_debug.exe /Fo$(OUTDIR_WIN)\\$(NAME)_x86_pe_debug.obj /DEBUG /ZI /F5
	cl.exe $(SOURCE_WIN)\\$(NAME).cpp $(INCLUDE_WIN) /Fe$(OUTDIR_WIN)\\$(NAME)_x86_pe.exe /Fo$(OUTDIR_WIN)\\$(NAME)_x86_pe.obj
	@if exist .\\*.idb move .\\*.idb $(OUTDIR_WIN)\\
	@if exist .\\*.pdb move .\\*.pdb $(OUTDIR_WIN)\\
clean_windows_x86:
	@if exist $(OUTDIR_WIN)\\$(NAME)_x86_pe* del $(OUTDIR_WIN)\\$(NAME)_x86_pe*
rebuild_windows_x86: clean_windows_x86 build_windows_x86

build_linux_x86:
	@mkdir -p $(OUTDIR_NIX)
	g++ -s $(SOURCE_NIX)/$(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_x86_elf_debug -g
	g++ -s $(SOURCE_NIX)/$(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_x86_elf
	strip $(OUTDIR_NIX)/$(NAME)_x86_elf
clean_linux_x86:
	rm -f $(OUTDIR_NIX)/$(NAME)_x86_elf*
rebuild_linux_x86: clean_linux_x86 build_linux_x86

build_linux_arm:
	@mkdir -p $(OUTDIR_NIX)
	arm-linux-gnueabi-g++ -s $(SOURCE_NIX)/$(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_arm_elf_debug
	cp $(OUTDIR_NIX)/$(NAME)_arm_elf_debug $(OUTDIR_NIX)/$(NAME)_arm_elf
	arm-linux-gnueabi-strip $(OUTDIR_NIX)/$(NAME)_arm_elf
clean_linux_arm:
	rm -f $(OUTDIR_NIX)/$(NAME)_arm_elf*
rebuild_linux_arm: clean_linux_arm build_linux_arm

build_linux_ppc:
	@mkdir -p $(OUTDIR_NIX)
	powerpc-linux-gnu-g++ -s $(SOURCE_NIX)/$(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_ppc_elf_debug
	cp $(OUTDIR_NIX)/$(NAME)_ppc_elf_debug $(OUTDIR_NIX)/$(NAME)_ppc_elf
	powerpc-linux-gnu-strip $(OUTDIR_NIX)/$(NAME)_ppc_elf
clean_linux_ppc:
	rm -f $(OUTDIR_NIX)/$(NAME)_ppc_elf*
rebuild_linux_ppc: clean_linux_ppc build_linux_ppc

build_in_docker_windows:
	@if not exist $(OUTDIR_WIN) mkdir $(OUTDIR_WIN)
	@docker start buildtools2019 || docker run --name buildtools2019 -it --mount 'type=bind,source=$(RECTF_DIR),target=C:\RECTFDEMOS' buildtools2019
	docker exec -it buildtools2019 cmd /k "DevPrompt.bat && cl RECTFDEMOS\ctfs\$(NAME)\src\$(NAME).cpp $(DOCKER_INCLUDE_WIN) /FoRECTFDEMOS\ctfs\$(NAME)\bin\$(NAME).obj /FeRECTFDEMOS\ctfs\$(NAME)\bin\$(NAME).exe && exit"

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
