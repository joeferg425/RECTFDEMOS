default: build

CTFS=ctfs
HELPERS=helpers
NIX_NAME:=build_nix
WIN_NAME:=build_win
NIX_IMG_NAME:=$(NIX_NAME)_img
WIN_IMG_NAME:=$(WIN_NAME)_img

MKFILE_PATH:=$(abspath $(lastword $(MAKEFILE_LIST)))
RECTF_DIR_:=$(abspath $(MKFILE_PATH)/../../../)
RECTF_DIR_NIX:=$(strip $(subst ^, ,$(lastword $(subst /C:/, C:/,$(subst  ,^,$(RECTF_DIR_))))))
RECTF_DIR_WIN:=$(subst /,\,$(RECTF_DIR_NIX))
CUR_DIRNAME:=$(lastword $(subst /, ,$(subst \\,/,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))))
NAME:=$(CUR_DIRNAME)

DIR_NIX:=$(RECTF_DIR_NIX)/$(CTFS)/$(NAME)
SOURCE_NIX:=$(DIR_NIX)/src
OUTDIR_NIX:=$(DIR_NIX)/bin
INCLUDE_NIX:=-I $(RECTF_DIR_NIX)/$(HELPERS) -I $(RECTF_DIR_NIX)/$(HELPERS)/md5/src

DIR_NIX_REL:=$(lastword $(subst /$(NAME)/, ./,$(DIR_NIX)))
SOURCE_NIX_REL:=$(lastword $(subst /$(NAME)/, ./,$(SOURCE_NIX)))
OUTDIR_NIX_REL:=$(lastword $(subst /$(NAME)/, ./,$(OUTDIR_NIX)))
INCLUDE_NIX_REL:=-I ../../$(HELPERS) -I ../../$(HELPERS)/md5/src

DIR_WIN:=$(RECTF_DIR_WIN)\$(CTFS)\$(NAME)
SOURCE_WIN:=$(DIR_WIN)\src
OUTDIR_WIN:=$(DIR_WIN)\bin
INCLUDE_WIN:=/I $(RECTF_DIR_WIN)\$(HELPERS) /I $(RECTF_DIR_WIN)\$(HELPERS)\md5\src

DIR_WIN_REL:=
SOURCE_WIN_REL:=$(lastword $(subst \$(NAME)\, ,$(SOURCE_WIN)))
OUTDIR_WIN_REL:=$(lastword $(subst \$(NAME)\, ,$(OUTDIR_WIN)))
INCLUDE_WIN_REL:=/I ..\..\$(HELPERS) /I ..\..\$(HELPERS)\md5\src

DIR_WIN_ESCAPED:=$(subst \,\\,$(DIR_WIN))
SOURCE_WIN_ESCAPED:=$(subst \,\\,$(SOURCE_WIN))
OUTDIR_WIN_ESCAPED:=$(subst \,\\,$(OUTDIR_WIN))
INCLUDE_WIN_ESCAPED:=$(subst \,\\,$(INCLUDE_WIN))

DIR_WIN_REL_ESCAPED:=$(subst \,\\,$(DIR_WIN_REL))
SOURCE_WIN_REL_ESCAPED:=$(subst \,\\,$(SOURCE_WIN_REL))
OUTDIR_WIN_REL_ESCAPED:=$(subst \,\\,$(OUTDIR_WIN_REL))
INCLUDE_WIN_REL_ESCAPED:=$(subst \,\\,$(INCLUDE_WIN_REL))

DOCKER_DEV_PROMPT:=C:\RECTFDEMOS\DevPrompt.bat

ifeq ($(OS),Windows_NT)
	CLEAN_CMD:=clean_windows
	BUILD_CMD:=build_windows
	RUN_CMD:=run_windows
	RUN_DOCKER_CMD:=run_in_docker_windows
	BUILD_IN_DOCKER_CMD:=build_in_docker_windows
	CLEAN_IN_DOCKER_CMD:=clean_in_docker_windows
	REBUILD_IN_DOCKER_CMD:=rebuild_in_docker_windows
	REBUILD_CMD:=rebuild_windows
	EXISTS_NIX_CONTAINER:=$(shell docker ps -a | findstr $(NIX_NAME) 2>&1 >nul && echo %errorlevel%)
	EXISTS_NIX_IMAGE:=$(shell docker image ls | findstr $(NIX_IMG_NAME) 2>&1 >nul && echo %errorlevel%)
	EXISTS_WIN_CONTAINER:=$(shell docker ps -a | findstr $(WIN_NAME) 2>&1 >nul && echo %errorlevel%)
	EXISTS_WIN_IMAGE:=$(shell docker image ls | findstr $(WIN_IMG_NAME) 2>&1 >nul && echo %errorlevel%)
	ifeq ($(CUR_DIRNAME), "RECTFDEMOS")
		CHANGE_DIR:=cd .
	else
		CHANGE_DIR:=cd ..\\..
	endif
	DOCKER_NIX_BUILD_CMD:=docker build $(RECTF_DIR_WIN) -f $(RECTF_DIR_WIN)\nix_dockerfile -t $(NIX_IMG_NAME)
	DOCKER_WIN_BUILD_CMD:=docker build $(RECTF_DIR_WIN) -f $(RECTF_DIR_WIN)\win_dockerfile -t $(WIN_IMG_NAME)
else
	CLEAN_CMD:=clean_linux
	BUILD_CMD:=build_linux
	RUN_CMD:=run_linux
	RUN_DOCKER_CMD:=run_in_docker_linux
	BUILD_IN_DOCKER_CMD:=build_in_docker_linux
	CLEAN_IN_DOCKER_CMD:=clean_in_docker_linux
	REBUILD_IN_DOCKER_CMD:=rebuild_in_docker_linux
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
	DOCKER_NIX_BUILD_CMD:=docker build $(RECTF_DIR_NIX) -f $(RECTF_DIR_NIX)/nix_dockerfile -t $(NIX_IMG_NAME)
	DOCKER_WIN_BUILD_CMD:=docker build $(RECTF_DIR_WIN) -f $(RECTF_DIR_WIN)\win_dockerfile -t $(WIN_IMG_NAME)
endif

ifeq ($(EXISTS_NIX_CONTAINER), 0)
	NIX_DOCKER_LAUNCH:=docker start $(NIX_NAME)
else
	NIX_DOCKER_LAUNCH:=docker run --name $(NIX_NAME) --mount 'type=bind,source=$(RECTF_DIR_NIX),target=/home/RECTFDEMOS' $(NIX_IMG_NAME)
endif

ifeq ($(EXISTS_NIX_IMAGE), 0)
	NIX_DOCKER_BUILD:=@echo "linux image already built"
else
	NIX_DOCKER_BUILD:=$(DOCKER_NIX_BUILD_CMD)
endif

ifeq ($(EXISTS_WIN_CONTAINER), 0)
	WIN_DOCKER_LAUNCH:=docker start $(WIN_NAME)
else
	WIN_DOCKER_LAUNCH:=docker run --name $(WIN_NAME) --mount 'type=bind,source=$(RECTF_DIR_WIN),target=C:\RECTFDEMOS' $(WIN_IMG_NAME)
endif

ifeq ($(EXISTS_WIN_IMAGE), 0)
	WIN_DOCKER_BUILD:=@echo "windows image already built"
else
	WIN_DOCKER_BUILD:=$(DOCKER_WIN_BUILD_CMD)
endif

install_linux:
	apt-get install gcc-powerpc-linux-gnu g++-powerpc-linux-gnu binutils-powerpc-linux-gnu gcc-arm-linux-gnueabi g++-arm-linux-gnueabi binutils-arm-linux-gnueabi

build_windows_x86:
	@if not exist $(OUTDIR_WIN_REL) mkdir $(OUTDIR_WIN_REL)
	cl.exe $(SOURCE_WIN_REL)\$(NAME).cpp $(INCLUDE_WIN_REL) /Fe$(OUTDIR_WIN_REL)\$(NAME)_x86_pe.exe /Fo$(OUTDIR_WIN_REL)\$(NAME)_x86_pe.obj
	cl.exe $(SOURCE_WIN_REL)\$(NAME).cpp $(INCLUDE_WIN_REL) /Fe$(OUTDIR_WIN_REL)\$(NAME)_x86_pe_debug.exe /Fo$(OUTDIR_WIN_REL)\$(NAME)_x86_pe_debug.obj /DEBUG /ZI /F5
	@if exist .\\*.idb move .\\*.idb $(OUTDIR_WIN_REL)\\
	@if exist .\\*.pdb move .\\*.pdb $(OUTDIR_WIN_REL)\\
clean_windows_x86:
	if exist $(OUTDIR_WIN_REL)\$(NAME)_x86_pe* del $(OUTDIR_WIN_REL)\$(NAME)_x86_pe*
rebuild_windows_x86: clean_windows_x86 build_windows_x86
run_windows_x86: rebuild_windows_x86
	$(subst .\,,$(OUTDIR_WIN_REL))\$(NAME)_x86_pe.exe
build_in_docker_windows_x86: build_windows_docker run_windows_docker
	@if not exist $(OUTDIR_WIN_REL) mkdir $(OUTDIR_WIN_REL)
	docker exec -it $(WIN_NAME) cmd /k "$(DOCKER_DEV_PROMPT) && cd $(CTFS)\$(NAME) && cl.exe $(SOURCE_WIN_REL)\$(NAME).cpp $(INCLUDE_WIN_REL) /Fo$(OUTDIR_WIN_REL)\$(NAME)_x86_pe.obj /Fe$(OUTDIR_WIN_REL)\$(NAME)_x86_pe.exe && exit"
clean_in_docker_windows_x86: clean_windows_x86
rebuild_in_docker_windows_x86: clean_in_docker_windows_x86 build_in_docker_windows_x86
run_in_docker_windows_x86: rebuild_in_docker_windows_x86
	docker exec -it $(WIN_NAME) $(subst .\,,$(OUTDIR_WIN_REL))\$(NAME)_x86_pe.exe

build_linux_x86:
	@echo changed
	@mkdir -p $(OUTDIR_NIX)
	g++ $(SOURCE_NIX)/$(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_x86_elf_debug -g -fno-stack-protector -O0
	g++ $(SOURCE_NIX)/$(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_x86_elf -fno-stack-protector -O0
	strip $(OUTDIR_NIX)/$(NAME)_x86_elf
	chmod +x $(OUTDIR_NIX)/$(NAME)_x86_elf_debug
	chmod +x $(OUTDIR_NIX)/$(NAME)_x86_elf
clean_linux_x86:
	rm -f $(OUTDIR_NIX)/$(NAME)_x86_elf*
rebuild_linux_x86: clean_linux_x86 build_linux_x86
run_linux_x86: rebuild_linux_x86
	$(OUTDIR_NIX_REL)/$(NAME)_x86_elf
build_in_docker_linux_x86: build_linux_docker run_linux_docker
	@mkdir -p $(OUTDIR_NIX)
	docker exec -it $(NIX_NAME) bash -c cd $(CTFS)/$(NAME); g++ $(SOURCE_NIX_REL)/$(NAME).cpp $(INCLUDE_NIX_REL) -o $(OUTDIR_NIX_REL)/$(NAME)_x86_elf_debug -g -fno-stack-protector
	docker exec -it $(NIX_NAME) bash -c cd $(CTFS)/$(NAME); g++ $(SOURCE_NIX_REL)/$(NAME).cpp $(INCLUDE_NIX_REL) -o $(OUTDIR_NIX_REL)/$(NAME)_x86_elf -fno-stack-protector
	docker exec -it $(NIX_NAME) bash -c cd $(CTFS)/$(NAME); strip $(OUTDIR_NIX_REL)/$(NAME)_x86_elf
clean_in_docker_linux_x86: clean_linux_x86
rebuild_in_docker_linux_x86: clean_in_docker_linux_x86 build_in_docker_linux_x86
run_in_docker_linux_x86: rebuild_in_docker_linux_x86
	docker exec -it $(NIX_NAME) bash -c cd $(CTFS)/$(NAME); $(OUTDIR_NIX_REL)/$(NAME)_x86_elf

build_linux_arm:
	@mkdir -p $(OUTDIR_NIX)
	arm-linux-gnueabi-g++ $(SOURCE_NIX)/$(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_arm_elf_debug -fno-stack-protector
	@cp $(OUTDIR_NIX)/$(NAME)_arm_elf_debug $(OUTDIR_NIX)/$(NAME)_arm_elf
	arm-linux-gnueabi-strip $(OUTDIR_NIX)/$(NAME)_arm_elf
clean_linux_arm:
	rm -f $(OUTDIR_NIX)/$(NAME)_arm_elf*
rebuild_linux_arm: clean_linux_arm build_linux_arm
build_in_docker_linux_arm: build_linux_docker run_linux_docker
	@mkdir -p $(OUTDIR_NIX)
	docker exec -it $(NIX_NAME) bash -c cd $(CTFS)/$(NAME); arm-linux-gnueabi-g++ $(SOURCE_NIX_REL)/$(NAME).cpp $(INCLUDE_NIX_REL) -o $(OUTDIR_NIX_REL)/$(NAME)_arm_elf_debug -fno-stack-protector
	docker exec -it $(NIX_NAME) bash -c cd $(CTFS)/$(NAME); cp $(OUTDIR_NIX_REL)/$(NAME)_arm_elf_debug $(OUTDIR_NIX_REL)/$(NAME)_arm_elf -fno-stack-protector
	docker exec -it $(NIX_NAME) bash -c cd $(CTFS)/$(NAME); arm-linux-gnueabi-strip $(OUTDIR_NIX_REL)/$(NAME)_arm_elf
clean_in_docker_linux_arm: clean_linux_arm
rebuild_in_docker_linux_arm: clean_in_docker_linux_arm build_in_docker_linux_arm

build_linux_ppc:
	@mkdir -p $(OUTDIR_NIX)
	powerpc-linux-gnu-g++ $(SOURCE_NIX)/$(NAME).cpp $(INCLUDE_NIX) -o $(OUTDIR_NIX)/$(NAME)_ppc_elf_debug -fno-stack-protector
	@cp $(OUTDIR_NIX)/$(NAME)_ppc_elf_debug $(OUTDIR_NIX)/$(NAME)_ppc_elf
	powerpc-linux-gnu-strip $(OUTDIR_NIX)/$(NAME)_ppc_elf
clean_linux_ppc:
	rm -f $(OUTDIR_NIX)/$(NAME)_ppc_elf*
rebuild_linux_ppc: clean_linux_ppc build_linux_ppc
build_in_docker_linux_ppc: build_linux_docker run_linux_docker
	@mkdir -p $(OUTDIR_NIX)
	docker exec -it $(NIX_NAME) bash -c cd $(CTFS)/$(NAME); powerpc-linux-gnu-g++ $(SOURCE_NIX_REL)/$(NAME).cpp $(INCLUDE_NIX_REL) -o $(OUTDIR_NIX_REL)/$(NAME)_ppc_elf_debug -fno-stack-protector
	docker exec -it $(NIX_NAME) bash -c cd $(CTFS)/$(NAME); cp $(OUTDIR_NIX_REL)/$(NAME)_ppc_elf_debug $(OUTDIR_NIX_REL)/$(NAME)_ppc_elf -fno-stack-protector
	docker exec -it $(NIX_NAME) bash -c cd $(CTFS)/$(NAME); powerpc-linux-gnu-strip $(OUTDIR_NIX_REL)/$(NAME)_ppc_elf
clean_in_docker_linux_ppc: clean_linux_ppc
rebuild_in_docker_linux_ppc: clean_in_docker_linux_ppc build_in_docker_linux_ppc

build_linux_docker:
	$(NIX_DOCKER_BUILD)
run_linux_docker: build_linux_docker
	$(NIX_DOCKER_LAUNCH)
attach_linux_docker: run_linux_docker
	docker exec $(NIX_NAME) bash

build_windows_docker:
	$(WIN_DOCKER_BUILD)
run_windows_docker: build_windows_docker
	$(WIN_DOCKER_LAUNCH)
attach_windows_docker: run_windows_docker
	docker exec -it $(WIN_NAME) cmd "/k $(DOCKER_DEV_PROMPT) && powershell -NoExit"

build_linux: build_linux_x86 build_linux_arm build_linux_ppc
clean_linux: clean_linux_x86 clean_linux_arm clean_linux_ppc
rebuild_linux: rebuild_linux_x86 rebuild_linux_arm rebuild_linux_ppc
run_linux: run_linux_x86

build_in_docker_linux: build_in_docker_linux_x86 build_in_docker_linux_arm build_in_docker_linux_ppc
clean_in_docker_linux: clean_in_docker_linux_x86 clean_in_docker_linux_arm clean_in_docker_linux_ppc
rebuild_in_docker_linux: rebuild_in_docker_linux_x86 rebuild_in_docker_linux_arm rebuild_in_docker_linux_ppc
run_in_docker_linux: run_in_docker_linux_x86

build_windows: build_windows_x86
clean_windows: clean_windows_x86
rebuild_windows: rebuild_windows_x86
run_windows: run_windows_x86

build_in_docker_windows: build_in_docker_windows_x86
clean_in_docker_windows: clean_in_docker_windows_x86
rebuild_in_docker_windows: rebuild_in_docker_windows_x86
run_in_docker_windows: run_in_docker_windows_x86

build: $(BUILD_CMD)
clean: $(CLEAN_CMD)
rebuild: $(REBUILD_CMD)
run: $(RUN_CMD)

build_in_docker: $(BUILD_IN_DOCKER_CMD)
clean_in_docker: $(CLEAN_IN_DOCKER_CMD)
rebuild_in_docker: $(REBUILD_IN_DOCKER_CMD)
run_in_docker: $(RUN_DOCKER_CMD)