# Capture the Flag #3

## Goals
- Familiarization with binary inspection tools
- Introduce slightly more complex obfuscation reversal

## Solution:
1. Search strings in binary
    - `ctf3_x86_elf`
        - Find `.ELF` at address `0x0`
        - Strings near `0x`
    - `ctf3_x86_pe`
        - Find `MZ` at address `0x0`
        - Strings near `0x`
    - tools
        - `strings`
        - `ghex / hexdump`
        - `ghidra`
        - `ida`
            - Find suspicious strings