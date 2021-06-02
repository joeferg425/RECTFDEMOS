default: rebuild

OUTDIR=../bin
OUTDIR_WIN=..\\bin
PWD=`pwd`
CL=cl.exe
CL_DBG_ARGS=/DEBUG /ZI /F5
GCC=gcc
GCC_DBG_ARGS=-ggdb
SERVER=server0
CLIENT=client0
INCLUDE_WIN=/I ./
INCLUDE_NIX=-I ./

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
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	$(CL) ./$(SERVER).cpp $(INCLUDE_WIN) /Fe${OUTDIR}/$(SERVER)_x86_pe.exe /Fo${OUTDIR}/$(SERVER).obj
	$(CL) ./$(CLIENT).cpp $(INCLUDE_WIN) /Fe${OUTDIR}/$(CLIENT)_x86_pe.exe /Fo${OUTDIR}/$(CLIENT).obj
	$(CL) $(CL_DBG_ARGS) ./$(SERVER).cpp $(INCLUDE_WIN) /Fe${OUTDIR}/$(SERVER)_x86_pe_debug.exe /Fo${OUTDIR}/$(SERVER).obj
	$(CL) $(CL_DBG_ARGS) ./$(CLIENT).cpp $(INCLUDE_WIN) /Fe${OUTDIR}/$(CLIENT)_x86_pe_debug.exe /Fo${OUTDIR}/$(CLIENT).obj
	@if exist .\\*.idb move .\\*.idb $(OUTDIR_WIN)\\
	@if exist .\\*.pdb move .\\*.pdb $(OUTDIR_WIN)\\
clean_windows_x86:
	if exist ${OUTDIR}\$(SERVER)_x86_pe* del ${OUTDIR}\$(SERVER)_x86_pe*
	if exist ${OUTDIR}\$(CLIENT)_x86_pe* del ${OUTDIR}\$(CLIENT)_x86_pe*
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

build_linux: build_linux_x86 build_linux_arm build_linux_ppc
clean_linux: clean_linux_x86 clean_linux_arm clean_linux_ppc
rebuild_linux: rebuild_linux_x86 rebuild_linux_arm rebuild_linux_ppc

build: $(detected_OS_build)
clean: $(detected_OS_clean)
rebuild: $(detected_OS_rebuild)
