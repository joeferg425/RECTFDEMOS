# CTF#1 #

## Capture the Flag #1 ##

Exploring your first binary.

---

## Table of Contents ##

[MAIN README](../../README.md)

[CTF#1](#ctf\#1)

- [Goals](#goals)
- [Required Tools](#required-tools)
- [Building the Binary](#building-the-binary)
- [Description](#description)
- [Obfuscation](#obfuscation)
- [Walkthrough](#walkthrough)
  - [Manually search strings in binary](#manually-search-strings-in-binary)
  - [Explore in Ghidra](#explore-in-ghidra)

---

## Goals ##

- Capture the flag!
- Introduce to [hexdump](https://linux.die.net/man/1/hexdump) / [HxD](https://mh-nexus.de/en/hxd/)
- Introduce [assembly instructions](https://en.wikipedia.org/wiki/Assembly_language)
- Introduce [Ghidra](https://ghidra-sre.org/)

---

## Required Tools ##

See [Required Tools](../../README.md#Required-Tools) section in the main README.

---

## Building the Binary ##

See [Compiling The CTF Binaries](../../README.md#Compiling-The-CTF-Binaries) section in the main README.

---

## Description ##

This exercise uses a binary built from the CTF1 source found in `./RECTFDEMOS/ctfs/ctf1/src`. Do not look at the source code unless you have completed the exercise, or intend to cheat. If you have already built the binary from source, then it should be located in `./RECTFDEMOS/ctfs/ctf1/bin`. In windows, run `ctf1_x86_pe.exe`, on a Linux system run `ctf1_x86_elf`.

When you run the CTF1 binary, you will see the following prompt:

![ctf1 prompt](readme_files/ctf1_prompt.png)

You can enter any string of text that you would like, followed by the `enter` key. If you get the password wrong, you will get a message like the following:

![ctf1 wrong password](readme_files/ctf1_wrong_password.gif)

If you get the password correct, you will get a message like the following, but with legible text:

![ctf1 correct password](readme_files/ctf1_correct_password.png)

The goal of this exercise is to get the flag without knowing the password beforehand, and without having access to source. In this case you could just go directly to the source code, since it is provided. That would ruin the exercise though. The source code is provided for those who are curious to try re-compilation of the source with various flags, compilers, and architectures and do comparisons of source code against Ghidra output.

Instead of going to the source, the challenge for the beginner binary hacker is to use the walkthrough below to guide you through the process of capturing the flag using some of the most basic binary reverse engineering tools.

---

## Obfuscation ##

Various obfuscation techniques are used for many of the exercises in this repository to make the passwords harder to find. The obfuscation methods used range from trivial ones defeated by searching the binary using a hex editor, to cryptographic methods.

No obfuscation was done for this exercise.

---

## Walkthrough ##

There are two proposed solutions to this exercise. It is good to be familiar with both, but the Ghidra method is the most useful for all but the most basic string searches. I suggest you try both since the manual method is also useful for things besides binary reverse engineering.

---

### Proposed Solutions ###

1. [Manually Search](#Manually-search-strings-in-binary)

    Manually Search the strings compiled into the binary manually using a tool like [strings](https://linux.die.net/man/1/strings), [hexdump](https://linux.die.net/man/1/hexdump), or [HxD](https://mh-nexus.de/en/hxd/) until you find a likely password string and then copy it into the ctf1 password prompt.

2. [Use a reverse engineering tool](#Explore-in-Ghidra)

    Using a reverse engineering tool such as [Ghidra](https://ghidra-sre.org/), search the strings compiled into the binary and determine which text string is the right one by finding where it is compared against the user input.

---

### Manually search strings in binary ###

Instructions for manual password retrieval using common software engineering tools.

---

#### Windows Walkthrough ####

- Open "`ctf1_x86_pe.exe`" in HxD

    ![header](readme_files/x86_pe_hxd_header.png)

- Find `MZ` starting at offset `0x0`. This two-byte sequence implies that the binary is compiled as a [windows executable](https://en.wikipedia.org/wiki/Portable_Executable) and it will have the [DOS header](https://en.wikipedia.org/wiki/DOS_MZ_executable) which can be manually decoded to find out lots of interesting information. Reverse engineering software will typically decode these well-known headers for you.

- Find strings near offset `0x2000` by scrolling until you find text that does not look like library names or other OS keywords.

    ![strings](readme_files/x86_pe_hxd_strings.png)

    Each string of text is separated by a dot. A single possible password can wrap around from the end of one line onto the next as seen with the string `ImAP4$$word` in the image above. Double clicking a string will select it in HxD so that the string can be easily copied and pasted.

- Try each suspicious string in this section until you find the password.

---

#### Linux walkthrough ####

- [hexdump](https://man7.org/linux/man-pages/man1/hexdump.1.html) the binary. Search for "ELF" string using [grep](https://man7.org/linux/man-pages/man1/grep.1.html).

    `$ hexdump ctfs/ctf1/bin/ctf1_x86_elf -C | grep ELF`

    ![hexdump header](readme_files/x86_elf_hexdump.png)

- Find `.ELF` starting at offset `0x0`. This four-byte sequence implies that the binary is compiled as a [Linux executable](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format) and it will have the [ELF header](https://en.wikipedia.org/wiki/Executable_and_Linkable_Format#File_header) which can be manually decoded to find out lots of interesting information. Reverse engineering software will typically decode these well-known headers for you when you open a binary with them.

- Find strings near offset `0x2000` by scrolling with [more](https://man7.org/linux/man-pages/man1/more.1.html) or using [regular expressions](https://en.wikipedia.org/wiki/Regular_expression) with something like [grep](https://man7.org/linux/man-pages/man1/grep.1.html).

    `$ hexdump ctfs/ctf1/bin/ctf1_x86_elf -C -s 0x2000 | more`

    ![strings](readme_files/x86_elf_strings.png)

    Each string of text is separated by a dot. A single possible password can wrap around from the end of one line onto the next as seen with the string `ImAP4$$word` in the image above.

- Try each suspicious string in this section until you find the password.

---

### Explore in Ghidra ###

1. Import the binary "`ctf1_x86_elf`" using Ghidra

2. Find the password and flag strings in Ghidra.

    There are two options here

    1. ***Use the offset*** you already got in the steps above to find the strings in the binary

    2. ***Use Ghidra*** tools to find the strings in the binary

        Either method will work

    ---

    1. ***Use the offset***

        Use the offset we saw in the string search to go directly to the strings. You must combine the string offset from the binary (0x2000) with the offset at which the binary was loaded into memory as seen in the image (0x100000).

        ![ghidra goto](readme_files/x86_elf_ghidra_goto.png)

    2. ***Use Ghidra***

        - Open the strings window in Ghidra

            ![open strings window](readme_files/x86_elf_ghidra_open_strings_window.png)

        - Double click one of the strings to go the address at which it is defined.

            ![open strings window](readme_files/x86_elf_ghidra_strings_window.png)

- Locate the function where the strings are used

    Double click the function name `FUN_001011a9` to navigate to that function.

    ![string references](readme_files/x86_elf_ghidra_string_xrefs.png)

- Look through assembly code and pseudo-c code

    The logic can be followed by observing the code in the screenshot. By following these steps yourself, you will be able to see the flag clearly in the code, or you can run the binary and pass the correct password.

    ![string references](readme_files/x86_elf_ghidra_function.png)
