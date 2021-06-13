# Capture the Flag #2

## Goals
- Familiarization with binary inspection tools
- Introduction to assembly instructions
- Introduce obfuscation concepts
- Introduce stripped binary vs binary with debug symbols

## Solution:
1. Search strings in binary
    - `ctf2_x86_elf`
        - Find `.ELF` at address `0x0`
        - Strings near `0x`
    - `ctf2_x86_pe`
        - Find `MZ` at address `0x0`
        - Strings near `0x`
    - tools
        - `strings`
        - `ghex / hexdump`
        - `ghidra`
        - `ida`
            - Find suspicious strings