# RECTFDEMOS #

Reverse Engineering Capture The Flag DEMOS

## Exercises ##

1. [CTF1](ctfs/ctf1/CTF1_README.md)
1. [CTF2](ctfs/ctf2/CTF2_README.md)
1. [CTF3](ctfs/ctf3/CTF3_README.md)
1. [CTF4](ctfs/ctf4/CTF4_README.md)
1. [CTF5](ctfs/ctf5/CTF5_README.md)
1. [CTF6](ctfs/ctf6/CTF6_README.md)

## Building in Docker ##

- Build Windows Binaries
  - **Requires Windows 10 Pro**
  - Install [Docker](https://docs.docker.com/)
  - Follow Windows [Docker Build Tools](https://docs.microsoft.com/en-us/visualstudio/install/build-tools-container?view=vs-2019) instructions
  - Switch to Windows containers

    `$ & $Env:ProgramFiles\Docker\Docker\DockerCli.exe -SwitchDaemon .`
  - `docker run --name buildtools2019 -it --mount 'type=bind,source=C:\workspace\RECTFDEMOS,target=C:\RECTFDEMOS' buildtools2019`

- Build Linux Binaries
  - Install Docker
    `$ apt-get install docker`

## Building in windows ##

1. Install [Visual Studio Code](https://code.visualstudio.com/download)
1. Open this repository / folder / workspace in VS Code
1. Install `CygWin` / [Mingw](http://mingw-w64.org/) / [Mingw make](http://gnuwin32.sourceforge.net/packages/make.htm)
1. Install [Microsoft Visual Studio Developer tools](https://visualstudio.microsoft.com/vs/community/) (installs individually or as part of Microsoft Visual Studio)
1. Launch [Developer Command Prompt for VS 20XX](https://docs.microsoft.com/en-us/visualstudio/ide/reference/command-prompt-powershell)
1. Type `code` on the command line and press `Enter`
1. You should now be able to build the Microsoft Windows binaries by running `make build`

## Building in Linux ##

1. Install [Visual Studio Code](https://code.visualstudio.com/download)
1. Open this repository / folder in VS Code
1. Install build essential
1. Install make
1. You should now be able to build the *nix binaries by running `make build`
