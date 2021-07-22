# Capture the Flag #5

## Goals
- Familiarization with binary inspection tools
- De-obfuscation practice
- ASCII tables

## Solution:
1. Search strings in binary
    - `ctf5_x86_elf`
        - Find `.ELF` at address `0x0`
        - Strings near `0x`
    - `ctf5_x86_pe`
        - Find `MZ` at address `0x0`
        - Strings near `0x`
    - tools
        - `ghidra`
