# CTF#5 #

## Capture the Flag #5 ##

---

## Table of Contents ##

[MAIN README](../../README.md)

[CTF#5](#ctf5)

- [Capture the Flag #5](#capture-the-flag-5)
- [Table of Contents](#table-of-contents)
- [Goals](#goals)
- [Walkthrough](#walkthrough)

---

## Goals ##

- Familiarization with binary inspection tools
- De-obfuscation practice
- ASCII tables

---

## Walkthrough ##

1. Search strings in binary
    - `ctf5_x86_elf`
        - Find `.ELF` at address `0x0`
        - Strings near `0x`
    - `ctf5_x86_pe`
        - Find `MZ` at address `0x0`
        - Strings near `0x`
    - tools
        - `ghidra`
