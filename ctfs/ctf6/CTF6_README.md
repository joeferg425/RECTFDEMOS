# Capture the Flag #6

## Goals
- Familiarization with binary inspection tools
- Introduction to storage types (`c-structs`)
- Introduction to buffer overflow attacks

## Solution:
1. Search strings in binary
    - `ctf6_x86_elf`
        - Find `.ELF` at address `0x0`
        - Strings near `0x`
    - `ctf6_x86_pe`
        - Find `MZ` at address `0x0`
        - Strings near `0x`
    - tools
        - `ghidra`
