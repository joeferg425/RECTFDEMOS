default: build

NIX_NAME:=build_nix
WIN_NAME:=build_win
NIX_IMG_NAME:=$(NIX_NAME)_img
WIN_IMG_NAME:=$(WIN_NAME)_img
MKFILE_PATH:=$(abspath $(lastword $(MAKEFILE_LIST)))
RECTF_DIR_:=$(abspath $(MKFILE_PATH)/../../../)
RECTF_DIR:=$(strip $(subst ^, ,$(lastword $(subst /C:/, C:/,$(subst  ,^,$(RECTF_DIR_))))))
CUR_DIRNAME:=$(lastword $(subst /, ,$(subst \\,/,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))))
NAME:=$(CUR_DIRNAME)
OUTDIR_NIX:=$(RECTF_DIR)/ctfs/$(NAME)/bin
OUTDIR_NIX_DOCKER:=$(lastword $(subst /RECTFDEMOS/, ./,$(OUTDIR_NIX)))
OUTDIR_WIN_ESCAPED:=$(subst /,\\,$(RECTF_DIR))\\ctfs\\$(NAME)\\bin
OUTDIR_WIN_DOCKER:=$(lastword $(subst \RECTFDEMOS\, .\,$(subst \\,\,$(OUTDIR_WIN_ESCAPED))))
SOURCE_NIX:=$(RECTF_DIR)/ctfs/$(NAME)/src
SOURCE_NIX_DOCKER:=$(lastword $(subst /RECTFDEMOS/, ./,$(SOURCE_NIX)))
SOURCE_WIN_ESCAPED:=$(subst /,\\,$(RECTF_DIR))\\ctfs\\$(NAME)\\src
SOURCE_WIN_DOCKER=$(lastword $(subst \RECTFDEMOS\, .\,$(subst \\,\,$(SOURCE_WIN_ESCAPED))))
INCLUDE_NIX:=-I $(RECTF_DIR)/helpers -I $(RECTF_DIR)/helpers/char2byte_xor
INCLUDE_NIX_DOCKER:=-I $(lastword $(subst /RECTFDEMOS, ./,$(RECTF_DIR)))/helpers -I $(lastword $(subst /RECTFDEMOS, ./,$(RECTF_DIR)))/helpers/char2byte_xor
INCLUDE_WIN_ESCAPED:=/I $(subst /,\\,$(RECTF_DIR))\\helpers /I $(subst /,\\,$(RECTF_DIR))\\helpers\\char2byte_xor
INCLUDE_WIN_DOCKER:=/I $(lastword $(subst \RECTFDEMOS, .\,$(subst \\,\,$(subst /,\\,$(RECTF_DIR)))))\helpers /I $(lastword $(subst \RECTFDEMOS, .\,$(subst \\,\,$(subst /,\\,$(RECTF_DIR)))))\helpers\char2byte_xor
DOCKER_INCLUDE_NIX:=-I RECTFDEMOS/helpers -I RECTFDEMOS/helpers/char2byte_xor
DOCKER_INCLUDE_WIN_ESCAPED:=/I RECTFDEMOS\\helpers /I RECTFDEMOS\\helpers\\char2byte_xor
DOCKER_DEV_PROMPT:=C:\\RECTFDEMOS\\DevPrompt.bat

ifeq ($(OS),Windows_NT)
	CLEAN_CMD:=clean_windows
	BUILD_CMD:=build_windows
	REBUILD_CMD:=rebuild_windows
	EXISTS_NIX_CONTAINER:=$(shell docker ps -a | findstr $(NIX_NAME) > nul 2>&1 && echo %errorlevel%)
	EXISTS_NIX_IMAGE:=$(shell docker image ls | findstr $(NIX_IMG_NAME) > nul 2>&1 && echo %errorlevel%)
	EXISTS_WIN_CONTAINER:=$(shell docker ps -a | findstr $(WIN_NAME) > nul 2>&1 && echo %errorlevel%)
	EXISTS_WIN_IMAGE:=$(shell docker image ls | findstr $(WIN_IMG_NAME) > nul 2>&1 && echo %errorlevel%)
	ifeq ($(CUR_DIRNAME), "RECTFDEMOS")
		CHANGE_DIR:=cd .
	else
		CHANGE_DIR:=cd ..\\..
	endif
	DOCKER_NIX_BUILD_CMD:=docker build $(RECTF_DIR) -f $(RECTF_DIR)\\nix_dockerfile -t $(NIX_IMG_NAME)
	DOCKER_WIN_BUILD_CMD:=docker build $(RECTF_DIR) -f $(RECTF_DIR)\\win_dockerfile -t $(WIN_IMG_NAME)
else
	CLEAN_CMD:=clean_linux
	BUILD_CMD:=build_linux
	REBUILD_CMD:=rebuild_linux
	EXISTS_NIX_CONTAINER:=$(shell docker ps -a | grep $(NIX_NAME) 2>&1 > /dev/null ; echo $$?)
	EXISTS_NIX_IMAGE:=$(shell docker image ls | grep $(NIX_IMG_NAME) 2>&1 > /dev/null ; echo $$?)
	EXISTS_WIN_CONTAINER:=$(shell docker ps -a | grep $(WIN_NAME) 2>&1 > /dev/null ; echo $$?)
	EXISTS_WIN_IMAGE:=$(shell docker image ls | grep $(WIN_IMG_NAME) 2>&1 > /dev/null ; echo $$?)
	ifeq ($(CUR_DIRNAME), "RECTFDEMOS")
		CHANGE_DIR:=cd .
	else
		CHANGE_DIR:=cd ../..
	endif
	DOCKER_NIX_BUILD_CMD:=docker build $(RECTF_DIR) -f $(RECTF_DIR)/nix_dockerfile -t $(NIX_IMG_NAME)
	DOCKER_WIN_BUILD_CMD:=docker build $(RECTF_DIR) -f $(RECTF_DIR)/win_dockerfile -t $(WIN_IMG_NAME)
endif

ifeq ($(EXISTS_NIX_CONTAINER), 0)
	NIX_DOCKER_LAUNCH:=docker start --attach -i $(NIX_NAME)
else
	NIX_DOCKER_LAUNCH:=docker run -it --name $(NIX_NAME) --mount 'type=bind,source=$(RECTF_DIR),target=/home/RECTFDEMOS' $(NIX_IMG_NAME)
endif

ifeq ($(EXISTS_NIX_IMAGE), 0)
	NIX_DOCKER_BUILD:=@echo "linux image already built"
else
	NIX_DOCKER_BUILD:=$(DOCKER_NIX_BUILD_CMD)
endif

ifeq ($(EXISTS_WIN_CONTAINER), 0)
	WIN_DOCKER_LAUNCH:=docker start --attach -i $(WIN_NAME)
else
	WIN_DOCKER_LAUNCH:=docker run -it --name $(WIN_NAME) --mount 'type=bind,source=$(RECTF_DIR),target=C:\RECTFDEMOS' $(WIN_IMG_NAME)
endif

ifeq ($(EXISTS_WIN_IMAGE), 0)
	WIN_DOCKER_BUILD:=@echo "windows image already built"
else
	WIN_DOCKER_BUILD:=$(DOCKER_WIN_BUILD_CMD)
endif

install_linux:
	apt-get install gcc-powerpc-linux-gnu g++-powerpc-linux-gnu binutils-powerpc-linux-gnu gcc-arm-linux-gnueabi g++-arm-linux-gnueabi binutils-arm-linux-gnueabi

build_windows_x86:
	@if not exist $(OUTDIR_WIN_ESCAPED) mkdir $(OUTDIR_WIN_ESCAPED)
	cl.exe $(SOURCE_WIN_ESCAPED)\\$(NAME).cpp $(INCLUDE_WIN_ESCAPED) /Fe$(OUTDIR_WIN_ESCAPED)\\$(NAME)_x86_pe.exe /Fo$(OUTDIR_WIN_ESCAPED)\\$(NAME)_x86_pe.obj
	cl.exe $(SOURCE_WIN_ESCAPED)\\$(NAME).cpp $(INCLUDE_WIN_ESCAPED) /Fe$(OUTDIR_WIN_ESCAPED)\\$(NAME)_x86_pe_debug.exe /Fo$(OUTDIR_WIN_ESCAPED)\\$(NAME)_x86_pe_debug.obj /DEBUG /ZI /F5
	@if exist .\\*.idb move .\\*.idb $(OUTDIR_WIN_ESCAPED)\\
	@if exist .\\*.pdb move .\\*.pdb $(OUTDIR_WIN_ESCAPED)\\
clean_windows_x86:
	if exist $(OUTDIR_WIN_ESCAPED)\\$(NAME)_x86_pe* del $(OUTDIR_WIN_ESCAPED)\\$(NAME)_x86_pe*
rebuild_windows_x86: clean_windows_x86 build_windows_x86
build_in_docker_windows_x86: build_windows_docker
	@if not exist $(subst \\,\,$(OUTDIR_WIN_ESCAPED)) mkdir $(subst \\,\,$(OUTDIR_WIN_ESCAPED))
	@docker start $(WIN_NAME) || docker run --name $(WIN_NAME) -it --mount 'type=bind,source=$(RECTF_DIR),target=C:\RECTFDEMOS' $(WIN_IMG_NAME)
	docker exec -it $(WIN_NAME) cmd /k "$(DOCKER_DEV_PROMPT) && cl.exe $(SOURCE_WIN_DOCKER)\$(NAME).cpp $(INCLUDE_WIN_DOCKER) /Fo$(OUTDIR_WIN_DOCKER)\$(NAME).obj /Fe$(OUTDIR_WIN_DOCKER)\$(NAME)_x86_pe.exe && exit"
clean_in_docker_windows_x86: clean_windows_x86
rebuild_in_docker_windows_x86: clean_in_docker_windows_x86 build_in_docker_windows_x86
run_windows_x86_in_docker: build_windows_docker
	docker exec -it $(WIN_NAME) $(subst .\,,$(OUTDIR_WIN_DOCKER))\$(NAME)_x86_pe.exe

build_linux_x86:
	@mkdir -p $(OUTDIR_NIX)
	g++ -s $(SOURCE_NIX)/$(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_x86_elf_debug -g
	g++ -s $(SOURCE_NIX)/$(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_x86_elf
	strip $(OUTDIR_NIX)/$(NAME)_x86_elf
clean_linux_x86:
	rm -f $(OUTDIR_NIX)/$(NAME)_x86_elf*
rebuild_linux_x86: clean_linux_x86 build_linux_x86
build_in_docker_linux_x86: build_linux_docker
	@mkdir -p $(OUTDIR_NIX)
	@docker start $(NIX_NAME) || docker run --name $(NIX_NAME) -it --mount 'type=bind,source=$(RECTF_DIR),target=/home/RECTFDEMOS' $(NIX_IMG_NAME)
	docker exec -it $(NIX_NAME) g++ -s $(SOURCE_NIX_DOCKER)/$(NAME).cpp $(INCLUDE_NIX_DOCKER) -o $(OUTDIR_NIX_DOCKER)/$(NAME)_x86_elf_debug -g
	docker exec -it $(NIX_NAME) g++ -s $(SOURCE_NIX_DOCKER)/$(NAME).cpp $(INCLUDE_NIX_DOCKER) -o $(OUTDIR_NIX_DOCKER)/$(NAME)_x86_elf
	docker exec -it $(NIX_NAME) strip $(OUTDIR_NIX_DOCKER)/$(NAME)_x86_elf
clean_in_docker_linux_x86: clean_linux_x86
rebuild_in_docker_linux_x86: clean_in_docker_linux_x86 build_in_docker_linux_x86
run_linux_x86_in_docker: build_linux_docker
	docker exec -it $(NIX_NAME) $(OUTDIR_NIX_DOCKER)/$(NAME)_x86_elf

build_linux_arm:
	@mkdir -p $(OUTDIR_NIX)
	arm-linux-gnueabi-g++ -s $(SOURCE_NIX)/$(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_arm_elf_debug
	@cp $(OUTDIR_NIX)/$(NAME)_arm_elf_debug $(OUTDIR_NIX)/$(NAME)_arm_elf
	arm-linux-gnueabi-strip $(OUTDIR_NIX)/$(NAME)_arm_elf
clean_linux_arm:
	rm -f $(OUTDIR_NIX)/$(NAME)_arm_elf*
rebuild_linux_arm: clean_linux_arm build_linux_arm
build_in_docker_linux_arm: build_linux_docker
	@mkdir -p $(OUTDIR_NIX)
	@docker start $(NIX_NAME) || docker run --name $(NIX_NAME) -it --mount 'type=bind,source=$(RECTF_DIR),target=/home/RECTFDEMOS' $(NIX_IMG_NAME)
	docker exec -it $(NIX_NAME) arm-linux-gnueabi-g++ -s $(SOURCE_NIX_DOCKER)/$(NAME).cpp $(INCLUDE_NIX_DOCKER) -o $(OUTDIR_NIX_DOCKER)/$(NAME)_arm_elf_debug
	docker exec -it $(NIX_NAME) cp $(OUTDIR_NIX_DOCKER)/$(NAME)_arm_elf_debug $(OUTDIR_NIX_DOCKER)/$(NAME)_arm_elf
	docker exec -it $(NIX_NAME) arm-linux-gnueabi-strip $(OUTDIR_NIX_DOCKER)/$(NAME)_arm_elf
clean_in_docker_linux_arm: clean_linux_arm
rebuild_in_docker_linux_arm: clean_in_docker_linux_arm build_in_docker_linux_arm

build_linux_ppc:
	@mkdir -p $(OUTDIR_NIX)
	powerpc-linux-gnu-g++ -s $(SOURCE_NIX)/$(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_ppc_elf_debug
	@cp $(OUTDIR_NIX)/$(NAME)_ppc_elf_debug $(OUTDIR_NIX)/$(NAME)_ppc_elf
	powerpc-linux-gnu-strip $(OUTDIR_NIX)/$(NAME)_ppc_elf
clean_linux_ppc:
	rm -f $(OUTDIR_NIX)/$(NAME)_ppc_elf*
rebuild_linux_ppc: clean_linux_ppc build_linux_ppc
build_in_docker_linux_ppc: build_linux_docker
	@mkdir -p $(OUTDIR_NIX)
	@docker start $(NIX_NAME) || docker run --name $(NIX_NAME) -it --mount 'type=bind,source=$(RECTF_DIR),target=/home/RECTFDEMOS' $(NIX_IMG_NAME)
	docker exec -it $(NIX_NAME) powerpc-linux-gnu-g++ -s $(SOURCE_NIX_DOCKER)/$(NAME).cpp $(INCLUDE_NIX_DOCKER) -o $(OUTDIR_NIX_DOCKER)/$(NAME)_ppc_elf_debug
	docker exec -it $(NIX_NAME) cp $(OUTDIR_NIX_DOCKER)/$(NAME)_ppc_elf_debug $(OUTDIR_NIX_DOCKER)/$(NAME)_ppc_elf
	docker exec -it $(NIX_NAME) powerpc-linux-gnu-strip $(OUTDIR_NIX_DOCKER)/$(NAME)_ppc_elf
clean_in_docker_linux_ppc: clean_linux_ppc
rebuild_in_docker_linux_ppc: clean_in_docker_linux_ppc build_in_docker_linux_ppc

build_linux_docker:
	$(NIX_DOCKER_BUILD)
run_linux_docker: build_linux_docker
	$(NIX_DOCKER_LAUNCH)

build_windows_docker:
	$(WIN_DOCKER_BUILD)
run_windows_docker: build_windows_docker
	$(WIN_DOCKER_LAUNCH)

build_linux: build_linux_x86 build_linux_arm build_linux_ppc
clean_linux: clean_linux_x86 clean_linux_arm clean_linux_ppc
rebuild_linux: rebuild_linux_x86 rebuild_linux_arm rebuild_linux_ppc

build_in_docker_linux: build_in_docker_linux_x86 build_in_docker_linux_arm build_in_docker_linux_ppc
clean_in_docker_linux: clean_in_docker_linux_x86 clean_in_docker_linux_arm clean_in_docker_linux_ppc
rebuild_in_docker_linux: rebuild_in_docker_linux_x86 rebuild_in_docker_linux_arm rebuild_in_docker_linux_ppc

build_windows: build_windows_x86
clean_windows: clean_windows_x86
rebuild_windows: rebuild_windows_x86

build_in_docker_windows: build_in_docker_windows_x86
clean_in_docker_windows: clean_in_docker_windows_x86
rebuild_in_docker_windows: rebuild_in_docker_windows_x86

build: $(BUILD_CMD)
clean: $(CLEAN_CMD)
rebuild: $(REBUILD_CMD)
