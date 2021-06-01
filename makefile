default:

OUTDIR=bin

CL_LONG=C:/Program Files (x86)/Microsoft Visual Studio/2019/BuildTools/VC/Tools/MSVC/14.29.30037/bin/Hostx64/x64/cl.exe
PWD=`pwd`
CL_SHORT=cl.exe
# ifneq ("$(wildcard $(CL))","")
#     echo exists
# else
#     echo nope
# endif
# CL := $(or $(and $(wildcard $(CL_SHORT)),$(CL_SHORT)),$(CL_LONG))
# ifeq ($(FILE_EXISTS), 1)
# 	echo exists
# else
# 	echo doesnt
# endif

# cl.exe > nul 2>&1

# # EXIT_CODE := cl.exe > nul 2>&1 & echo %ERRORLEVEL%
# @EXIT_CODE := $(shell cl.exe > nul 2>&1 & echo %ERRORLEVEL%)
# echo EXIT_CODE: $(EXIT_CODE)

# ifneq ($(EXIT_CODE), 0)
# 	cmd /k "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\Common7\Tools\VsDevCmd.bat"
# 	cd ${PWD}
# endif

windows_server0:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	cl.exe ./server_client_0/server0.cpp /I ./server_client_0 /Fe${OUTDIR}/server0.exe /Fo${OUTDIR}/server0.obj
windows_server0_debug:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	cl.exe /DEBUG /ZI /F5 ./server_client_0/server0.cpp /I ./server_client_0 /Fe${OUTDIR}/server0.exe /Fo${OUTDIR}/server0.obj
windows_server0_clean:
	if exist ${OUTDIR}\server0.* del ${OUTDIR}\server0.*
windows_client0:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	cl.exe ./server_client_0/client0.cpp /I ./server_client_0 /Fe${OUTDIR}/client0.exe /Fo${OUTDIR}/client0.obj
windows_client0_debug:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	cl.exe /DEBUG /ZI /F5 ./server_client_0/client0.cpp /I ./server_client_0 /Fe${OUTDIR}/client0.exe /Fo${OUTDIR}/client0.obj
windows_client0_clean:
	if exist ${OUTDIR}\client0.* del ${OUTDIR}\client0.*
windows_clean0: windows_server0_clean windows_client0_clean
windows_build0: windows_server0 windows_client0
windows_rebuild0: windows_clean0 windows_build0
windows_build0_debug: windows_server0_debug windows_client0_debug
windows_rebuild0_debug: windows_clean0 windows_build0_debug

linux_server0:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	gcc ./server_client_0/server0.cpp -I ./server_client_0 -o ${OUTDIR}/server0
linux_server0_debug:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	gcc -ggdb ./server_client_0/server0.cpp -I ./server_client_0 -o ${OUTDIR}/server0
linux_server0_clean:
	rm -f ${OUTDIR}/server0
	rm -f server_client_0/server0.obj
linux_client0:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	gcc ./server_client_0/client0.cpp -I ./server_client_0 -o ${OUTDIR}/client0
linux_client0_debug:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	gcc -ggdb ./server_client_0/client0.cpp -I ./server_client_0 -o ${OUTDIR}/client0
linux_client0_clean:
	rm -f ${OUTDIR}/client0
	rm -f server_client_0/client0.obj
linux_clean0: linux_server0_clean linux_client0_clean
linux_build0: linux_server0 linux_client0
linux_rebuild0: linux_clean0 linux_build0
linux_build0_debug: linux_server0_debug linux_client0_debug
linux_rebuild0_debug: linux_clean0 linux_build0_debug

windows_server1:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	cl.exe ./server_client_1/server1.cpp /I ./server_client_0 /I ./server_client_1 /Fe${OUTDIR}/server1.exe /Fo${OUTDIR}/server1.obj
windows_server1_debug:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	cl.exe /DEBUG /ZI /F5 ./server_client_1/server1.cpp /I ./server_client_0 /I ./server_client_1 /Fe${OUTDIR}/server1.exe /Fo${OUTDIR}/server1.obj
windows_server1_clean:
	if exist ${OUTDIR}\server1.* del ${OUTDIR}\server1.*
windows_client1:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	cl.exe ./server_client_1/client1.cpp /I ./server_client_0 /I ./server_client_1 /Fe${OUTDIR}/client1.exe /Fo${OUTDIR}/client1.obj
windows_client1_debug:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	cl.exe /DEBUG /ZI /F5 ./server_client_1/client1.cpp /I ./server_client_0 /I ./server_client_1 /Fe${OUTDIR}/client1.exe /Fo${OUTDIR}/client1.obj
windows_client1_clean:
	if exist ${OUTDIR}\client1.* del ${OUTDIR}\client1.*
windows_clean1: windows_server1_clean windows_client1_clean
windows_build1: windows_server1 windows_client1
windows_rebuild1: windows_clean1 windows_build1
windows_build1_debug: windows_server1_debug windows_client1_debug
windows_rebuild1_debug: windows_clean1 windows_build1_debug

linux_server1:
	gcc ./server_client_1/server1.cpp -I ./server_client_0 -I ./server_client_1 -o ${OUTDIR}/server1
linux_server1_debug:
	gcc -ggdb ./server_client_1/server1.cpp -I ./server_client_0 -I ./server_client_1 -o ${OUTDIR}/server1
linux_server1_clean:
	rm -f ${OUTDIR}/server1
	rm -f server_client_1/server1.obj
linux_client1:
	gcc ./server_client_1/client1.cpp -I ./server_client_0 -I ./server_client_1 -o ${OUTDIR}/client1
linux_client1_debug:
	gcc -ggdb ./server_client_1/client1.cpp -I ./server_client_0 -I ./server_client_1 -o ${OUTDIR}/client1
linux_client1_clean:
	rm -f ${OUTDIR}/client1
	rm -f server_client_1/client1.obj
linux_clean1: linux_server1_clean linux_client1_clean
linux_build1: linux_server1 linux_client1
linux_rebuild1: linux_clean1 linux_build1
linux_build1_debug: linux_server1_debug linux_client1_debug
linux_rebuild1_debug: linux_clean1 linux_build1_debug

windows_server2:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	cl.exe ./server_client_2/server2.cpp /I ./server_client_0 /I ./server_client_1 /I ./server_client_2 /Fe${OUTDIR}/server2.exe /Fo${OUTDIR}/server2.obj
windows_server2_debug:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	cl.exe /DEBUG /ZI /F5 ./server_client_2/server2.cpp /I ./server_client_0 /I ./server_client_1 /I ./server_client_2 /Fe${OUTDIR}/server2.exe /Fo${OUTDIR}/server2.obj
windows_server2_clean:
	if exist ${OUTDIR}\server2.* del ${OUTDIR}\server2.*
windows_client2:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	cl.exe ./server_client_2/client2.cpp /I ./server_client_0 /I ./server_client_1 /I ./server_client_2 /Fe${OUTDIR}/client2.exe /Fo${OUTDIR}/client2.obj
windows_client2_debug:
	@if not exist $(OUTDIR) mkdir $(OUTDIR)
	cl.exe /DEBUG /ZI /F5 ./server_client_2/client2.cpp /I ./server_client_0 /I ./server_client_1 /I ./server_client_2 /Fe${OUTDIR}/client2.exe /Fo${OUTDIR}/client2.obj
windows_client2_clean:
	if exist ${OUTDIR}\client2.* del ${OUTDIR}\client2.*
windows_clean2: windows_server2_clean windows_client2_clean
windows_build2: windows_server2 windows_client2
windows_rebuild2: windows_clean2 windows_build2
windows_build2_debug: windows_server2_debug windows_client2_debug
windows_rebuild2_debug: windows_clean2 windows_build2_debug

linux_clean: linux_clean0 linux_clean1
windows_clean: windows_clean0 windows_clean1 windows_clean2

linux_build: linux_build0 linux_build1
windows_build: windows_build0 windows_build1 windows_build2

linux_rebuild: linux_rebuild0 linux_rebuild1
windows_rebuild: windows_rebuild0 windows_rebuild1 windows_rebuild2

linux_build_debug: linux_build0_debug linux_build1_debug
windows_build_debug: windows_build0_debug windows_build1_debug windows_build2_debug

linux_rebuild_debug: linux_rebuild0_debug linux_rebuild1_debug
windows_rebuild_debug: windows_rebuild0_debug windows_rebuild1_debug windows_rebuild2_debug

windows: windows_rebuild
linux: linux_rebuild