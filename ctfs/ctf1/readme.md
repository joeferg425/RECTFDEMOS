# Capture the Flag #1

The goal of this challenge is familiarization with tools.

## Solution:
1. Search strings in binary
    - hex editor
        - ctf1_x86_elf
            - Find `.ELF` at address `0x0`
            - Strings at `0xB85`
        - ctf1_x86_pe
            - Find `MZ` at address `0x0`
            - Strings at `0x13965`
    - hexdump
        - ctf1_x86_elf
            - Find `.ELF` at address `0x0`
            - Strings at `0xB85`
        - ctf1_x86_pe
            - Find `MZ` at address `0x0`
            - Strings at `0x13965`
    - strings
        - Find suspicious strings