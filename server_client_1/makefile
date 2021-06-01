default: build

OUTDIR=bin
PWD=`pwd`
CL=cl.exe
CL_DBG_ARGS=/DEBUG /ZI /F5
GCC=gcc
GCC_DBG_ARGS=-ggdb
SERVER=server1
CLIENT=client1
INCLUDE_WIN=/I ./ /I ../server_client_0
INCLUDE_NIX=-I ./ -I ../server_client_0

ifeq ($(OS),Windows_NT)
    detected_OS := rebuild_windows
else
    detected_OS := rebuild_linux
endif

build_windows:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	$(CL) ./$(SERVER).cpp $(INCLUDE_WIN) /Fe${OUTDIR}/$(SERVER).exe /Fo${OUTDIR}/$(SERVER).obj
	$(CL) ./$(CLIENT).cpp $(INCLUDE_WIN) /Fe${OUTDIR}/$(CLIENT).exe /Fo${OUTDIR}/$(CLIENT).obj
debug_windows:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	$(CL) $(CL_DBG_ARGS) ./$(SERVER).cpp $(INCLUDE_WIN) /Fe${OUTDIR}/$(SERVER).exe /Fo${OUTDIR}/$(SERVER).obj
	$(CL) $(CL_DBG_ARGS) ./$(CLIENT).cpp $(INCLUDE_WIN) /Fe${OUTDIR}/$(CLIENT).exe /Fo${OUTDIR}/$(CLIENT).obj
clean_windows:
	if exist ${OUTDIR}\$(SERVER).* del ${OUTDIR}\$(SERVER).*
	if exist ${OUTDIR}\$(CLIENT).* del ${OUTDIR}\$(CLIENT).*
rebuild_windows: clean_windows build_windows
rebuild_windows_debug: clean_windows debug_windows

build_linux:
	@mkdir -p $(OUTDIR)
	$(GCC) ./$(SERVER).cpp $(INCLUDE_NIX) -o ${OUTDIR}/$(SERVER)
	$(GCC) ./$(CLIENT).cpp $(INCLUDE_NIX) -o ${OUTDIR}/$(CLIENT)
debug_linux:
	mkdir -p $(OUTDIR)
	$(GCC) $(GCC_DBG_ARGS) ./$(SERVER).cpp $(INCLUDE_NIX) -o ${OUTDIR}/$(SERVER)
	$(GCC) $(GCC_DBG_ARGS) ./${CLIENT}.cpp $(INCLUDE_NIX) -o ${OUTDIR}/${CLIENT}
clean_linux:
	rm -f ${OUTDIR}/$(SERVER)
	rm -f ${OUTDIR}/$(CLIENT)
	rm -f ${OUTDIR}/$(SERVER).obj
	rm -f ${OUTDIR}/$(CLIENT).obj
rebuild_linux: clean_linux build_linux
rebuild_linux_debug: clean_linux debug_linux

build: $(detected_OS)
