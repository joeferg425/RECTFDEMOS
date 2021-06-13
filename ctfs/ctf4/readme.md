# Capture the Flag #4

## Goals
- Familiarization with binary inspection tools
- Easy win, clear-text password can be pulled from binary despite obfuscation

## Solution:
1. Search strings in binary
    - `ctf4_x86_elf`
        - Find `.ELF` at address `0x0`
        - Strings near `0x`
    - `ctf4_x86_pe`
        - Find `MZ` at address `0x0`
        - Strings near `0x`
    - tools
        - `strings`
        - `ghex / hexdump`
        - `ghidra`
        - `ida`
            - Find suspicious strings