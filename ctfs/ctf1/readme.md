# Capture the Flag #1

## Goals
- Familiarization with binary inspection tools
- Introduction to assembly instructions

## Solution:
1. Search strings in binary
    - `ctf1_x86_elf`
        - Find `.ELF` at address `0x0`
        - Strings near `0xB85`
    - `ctf1_x86_pe`
        - Find `MZ` at address `0x0`
        - Strings near `0x13965`
    - tools
        - `strings`
        - `ghex / hexdump`
        - `ghidra`
        - `ida`
            - Find suspicious strings