# RECTFDEMOS #

## (R)everse (E)ngineering (C)apture (T)he (F)lag (DEMOS) ##

---

## Table of Contents ##

- [Preface](#preface)
- [Introduction](#introduction)
- [Exercises](#exercises)
- [Building The CTF Binaries](#building-the-ctf-binaries)
  - [Compiling in Docker](#compiling-in-docker)
    - [Docker-Compile Linux Binaries](#docker-compile-linux-binaries)
    - [Docker-Compile Windows Binaries](#docker-compile-windows-binaries)
  - [Compiling in windows](#compiling-in-windows)
  - [Compiling in Linux](#compiling-in-linux)

---

## Preface ##

My goal when creating this originally was to make some simplistic Binary Reverse Engineering demos to teach in a class at the University I was attending. At the time, I was using [hex-rays IDA](https://hex-rays.com/ida-pro/) products exclusively. The class session went well and was well-received.

A few years later I put the code on github, but not the tutorial writeups since they were done for a specific set of students and were not adequate for a wider audience. Since then I have tried to create new tutorial documentation with better screenshots and walk-through steps. Additionally, I have switched to the [NSA's Ghidra](https://ghidra-sre.org/) because of its significantly better price, the much better support, and the impressive development cycle.

My goal with the specific content that I have created is to fill a gap I ran into when I was getting started. Many guides are available for 'advanced malware analysis' or 'writing scripts to auto-detect library/function X' or many more advanced topics, but what I have not seen done well is the simple introduction to binary reverse engineering with real code, real binaries, and a complete walkthrough. I hope you find this set of exercises useful.

## Introduction ##

These exercises are meant to be representative of many of the most basic exercises that are performed when doing reverse engineering work. Each exercise is built from one of just a few simple templates so that the beginner hacker is not overwhelmed by multiple, large, complex codebases to sift through. Learned skills will be reinforced through pattern recognition along with instruction.

To add realistic complication without requiring a lot of coding on my part, multiple compilers and compiler options are used in the makefiles. This allows a user to "cheat" a bit by viewing the same code compiled for different architectures and operating systems. Comparing the output of various compilers is also a very useful exercise for hackers.

## Exercises ##

The following links will take you to the capture the flag exercises.

1. [CTF1](ctfs/ctf1/CTF1_README.md)
2. [CTF2](ctfs/ctf2/CTF2_README.md)
3. [CTF3](ctfs/ctf3/CTF3_README.md)
4. [CTF4](ctfs/ctf4/CTF4_README.md)
5. [CTF5](ctfs/ctf5/CTF5_README.md)
6. [CTF6](ctfs/ctf6/CTF6_README.md)
7. [CTF7](ctfs/ctf7/CTF7_README.md)

## Compiling The CTF Binaries ##

If you want to run the capture the flag exercises, you will need to build them since I decided against checking the binaries into source control. Multiple methods have been prepared for you to make this process as easy as possible.

The easiest and safest method is to use docker to build and run the linux binaries. Installation is usually straightforward, and the dockerfiles, makefiles, and source code have been provided for you in this repository.

If you already have a c/c++ build environment set up, then feel free to compile everything yourself using whatever compiler you want and just follow along with the tutorials as well as possible. The instructions should still be valid, just the memory addresses and offsets will all change.

### Compiling in Docker ###

I recommend building the binaries in a linux-based docker container, or building natively in linux or the Windows Subsystem for Linux (WSL). The docker image provides some protection of your system from exercises like this, and is a good tool to become comfortable with.

If you aren't determined to use the windows binaries, I recommend skipping the windows docker image altogether. It is a large docker image and since you have to use the Microsoft Visual Studio installers to prep it, it takes at least fifteen minutes just to build it typically.

#### Docker-Compile Linux Binaries ####

- Use make
  If make is installed and configured, run the following

  `$ make build_linux_docker`
  `$ make run_linux_docker`

  You should now be attached to the docker container; use make to build the binaries. Run the following to build the binaries in docker.

  `$ make build`

- Install [Docker](https://docs.docker.com/)

  `$ apt-get install docker`

- Build Linux Docker Image

  `$ docker build . -f ./nix_dockerfile -t build_nix_img`

- Run Linux Docker Image

  You will need the absolute path to the `RECTFDEMOS` directory. Something like:

  - `C:\workspace\RECTFDEMOS`
  - `/home/hacker/RECTFDEMOS`

  The full path below is represented by `RECTFDEMOS_PATH`

  `$ docker run --name build_nix --mount 'type=bind,source=RECTFDEMOS_PATH,target=/home/RECTFDEMOS' build_nix_img`

- Use Make to build the binaries

  Within the docker container, run the following command.

  `$ make build`

#### Docker-Compile Windows Binaries ####

---

- **Requires Windows 10 Pro**

---

- Install [Docker](https://docs.docker.com/)

- Switch to Windows containers

  Run the following in powershell

  `$ & $Env:ProgramFiles\Docker\Docker\DockerCli.exe -SwitchDaemon .`

- Build the docker image

  `$ docker build . -f win_dockerfile -t build_win_img`

  It takes about 15 minutes to build image.

- Run the docker image

  You will need the absolute path to the `RECTFDEMOS` directory. Something like:

  - `C:\workspace\RECTFDEMOS`

  The full path below is represented by `RECTFDEMOS_PATH`

  `docker run --name build_win -it --mount 'type=bind,source=RECTFDEMOS_PATH,target=C:\RECTFDEMOS' build_win_img`

### Compiling in Windows ###

1. Install [Visual Studio Code](https://code.visualstudio.com/download)
1. Open this repository / folder / workspace in VS Code
1. Install `CygWin` / [Mingw](http://mingw-w64.org/) / [Mingw make](http://gnuwin32.sourceforge.net/packages/make.htm)
1. Install [Microsoft Visual Studio Developer tools](https://visualstudio.microsoft.com/vs/community/) (installs individually or as part of Microsoft Visual Studio)
1. Launch [Developer Command Prompt for VS 20XX](https://docs.microsoft.com/en-us/visualstudio/ide/reference/command-prompt-powershell)
1. Type `code` on the command line and press `Enter`
1. You should now be able to build the Microsoft Windows binaries by running `make build`

### Compiling in Linux ###

1. Install [Visual Studio Code](https://code.visualstudio.com/download)
1. Open this repository / folder in a terminal
1. Run `make install_linux`
1. You should now be able to build the *nix binaries by running `make build`

### Required Tools ###

- [Ghidra Reverse Engineering Software](https://ghidra-sre.org/)
- Windows
  - [Mingw](http://mingw-w64.org/)
  - [Mingw make](http://gnuwin32.sourceforge.net/packages/make.htm)
  - [Microsoft Visual Studio Developer tools](https://visualstudio.microsoft.com/vs/community/)
  - [HxD hex editor](https://mh-nexus.de/en/hxd/)
- Linux
  - build-essential gcc-powerpc-linux-gnu g++-powerpc-linux-gnu binutils-powerpc-linux-gnu gcc-arm-linux-gnueabi g++-arm-linux-gnueabi binutils-arm-linux-gnueabi
  - [strings](https://linux.die.net/man/1/strings)
  - [hexdump](https://linux.die.net/man/1/hexdump)
