# CTF#5 #

## Capture the Flag #5 ##

---

## Table of Contents ##

[MAIN README](../../README.md)

[CTF#5](#ctf5)

- [Goals](#goals)
- [Required Tools](#required-tools)
- [Building the Binary](#building-the-binary)
- [Description](#description)
- [Obfuscation](#obfuscation)
- [Walkthrough](#walkthrough)
    - [Open `ctf5_arm_elf` using Ghidra](#open-ctf5_arm_elf-using-ghidra)
    - [Find the password checking function](#find-the-password-checking-function)
    - [Investigate `FUN_000108f0`](#investigate-fun_000108f0)
    - [Reverse Engineer `FUN_00010858`](#reverse-engineer-fun_00010858)
    - [Determine Password and Flag values](#determine-password-and-flag-values)

---

## Goals ##

- Familiarization with binary inspection tools
- Ignore distractions
- De-obfuscation practice
- ASCII tables

---

## Required Tools ##

- [Ghidra Reverse Engineering Software](https://ghidra-sre.org/)

---

## Building the Binary ##

See [Compiling The CTF Binaries](../../README.md#Compiling-The-CTF-Binaries) section in the main README.

---

## Description ##

This exercise uses a binary built from the CTF5 source. When you run the CTF5 binary, you will see the following prompt:

![ctf5 prompt](readme_files/ctf5_prompt.png)

You can enter any string of text that you would like, followed by the `enter` key. If you get the password wrong, you will get a message like the following:

![ctf5 wrong password](readme_files/ctf5_wrong_password.gif)

If you get the password correct, you will get a message like the following, but with legible text:

![ctf5 correct password](readme_files/ctf5_correct_password.png)

It is useful to note that you can also give the password to the binary as an argument for faster testing.

![ctf5 password argument](readme_files/ctf5_password_arg.png)

The goal of this exercise is to get the flag without knowing the password beforehand, and without having access to source. In this case you could just go directly to the source code, since it is provided. That would ruin the exercise though. The source is provided for those who are curious to try re-compilation of the source with various flags, compilers, and architectures and do comparisons of binaries and of Ghidra output.

Instead of going to the source, the challenge for the beginner binary hacker is to use the walkthrough below to guide you through the process of capturing the flag using some of the most basic binary reverse engineering tools.

---

## Obfuscation ##

Obfuscation for this exercise was done by storing [ASCII](https://en.wikipedia.org/wiki/ASCII) data as C's char [data type](https://en.wikipedia.org/wiki/C_data_types), and then a simple and reversible mathematical function was applied to the 8-bit char values.

---

## Walkthrough ##

### Open `ctf5_arm_elf` using Ghidra ###

1. Import the binary
2. Analyze the binary

### Find the password checking function ###

1. Open the "Defined Strings" window
2. Locate a recognizable string in the strings window
3. Select a string in the strings window

    ![ghidra strings window](readme_files/ctf5_ghidra_strings.png)

4. Click decompilation window to bring it into the foreground.

    ![ghidra decompilation window](readme_files/ctf5_ghidra_decompilation.png)

### Investigate `FUN_000108f0` ###

1. Identify variables of interest.

    ![ghidra FUN_000108f0](readme_files/ctf5_ghidra_FUN_000108f0.png)

    | Variable    | Usage               |
    |:------------|:--------------------|
    | `local_178` | Flag                |
    | `local_144` | User Input          |
    | `local_1bc` | Possible Password 1 |
    | `local_dc`  | Possible Password 2 |
    | `local_1b8` | Possible Password 3 |
    | `local_1ac` | Possible Password 4 |
    | `local_1b4` | Possible Password 5 |
    | `local_1b0` | Possible Password 6 |
    | `local_a8`  | Possible Password 7 |

2. Rule out variables of minimal interest.

    - `local_144` - "User Input" is compared against other strings
    - Possible passwords are compared using [strcmp](https://www.cplusplus.com/reference/cstring/strcmp/). According to the documentation, when the compared strings are equal a zero is returned.

        ![strcmp return value](readme_files/ctf5_strcmp.png)

        Looking back at the decompilation, many of the comparisons were not done against the value `0`. If strcmp does not return 0, the strings are not equal. This means the comparisons being done are invalid and should not ever be true.

    - Only the flag and one other variable are put through the function `FUN_00010858` which looks like our previous obfuscation functions.

    - Based on the `strcmp` and `FUN_00010858` findings:

        ![FUN_00010858 calls](readme_files/ctf5_ghidra_FUN_00010858_calls.png)

        ![strcmp == 0](readme_files/ctf5_strcmp_0.png)

        | Variable    | Usage           |
        |:------------|:----------------|
        | `local_178` | Flag            |
        | `local_144` | User Input      |
        | `local_1ac` | Likely Password |

### Reverse Engineer `FUN_00010858` ###

1. Document known argument types for the function

    - Determine type information for `local_178`, the probable flag variable.

        In the call to [printf](https://www.cplusplus.com/reference/cstdio/printf/), `local_178` is printed using the `%s` argument. This means it is a string or `char*` type in c.

        ![local_178 type](readme_files/ctf5_printf_local_178.png)

2. Update the type information for the function

    - Navigate to the `FUN_00010858` decompilation by double clicking the label.

        ![FUN_00010858 initial](readme_files/ctf5_ghidra_FUN_00010858_initial.png)

        Notice that the function currently returns `undefined` type, and `param_3` is set to `int` type despite `param_3` being passed `local_178` which we know to be a `char*`.

        The function always returns `0`, so we can set the return type to `int`.

    - Update type information for `FUN_00010858`

        Right-click on `FUN_00010858` from within the decompilation window and select "Edit-Signature"

        ![edit signature](readme_files/ctf5_ghidra_FUN_00010858_edit_signature.png)

        Set the types in the signature to the ones we have deduced.

        ![edit types](readme_files/ctf5_ghidra_FUN_00010858_types.png)

        The function looks more like a typical loop through a string now.

        ![better FUN_00010858](readme_files/ctf5_ghidra_FUN_00010858_better.png)

        If we remember how the function looked earlier:

        ![char* offsets](readme_files/ctf5_char_star_offsets.png)

        We can tell that `param_1` has the same use and signature as `param_3`. Set it to `char*` as well.

3. Determine function of `FUN_00010858`

    Based on the decompilation, we can tell that `FUN_00010858` adds `param_5` to each byte of `param_1` (up to `param_2` bytes max) and stores the result into `param_3`.

    ![`FUN_00010858` functionality](readme_files/ctf5_ghidra_FUN_00010858_function.png)

### Determine Password and Flag values ###

1. Based on our understanding of `FUN_00010858`, we now know the following:

    - `local_110` is the password string, except each byte needs to have the hex value 0x80 added to it.
    - `local_74` is the flag string, except each byte needs to have the hex value 0x80 added to it.

2. De-obfuscate the flag and/or password data

    - Neither the password or the flag is in plaintext this time, so we will have to work for it a bit.
    - Recalling our reverse engineering work from earlier, we can see that we will have to do some math on the data bytes.

        ![`FUN_00010858` reversed](readme_files/ctf5_ghidra_FUN_00010858_good.png)

        It appears we need the value of `param_5`

        ![param_5 value](readme_files/ctf5_param_5_value.png)

    - Perform the math on either `local_74` or `local_110`

        - For `local_74`

            ![local_74 assignment](readme_files/ctf5_local_74_assignment.png)

            In assembly, we see that the obfuscated data is stored in memory at `DAT_00010fec`.

            ![local_74 assignment assembly](readme_files/ctf5_local_74_assignment_assembly.png)

            If we navigate to that address we can investigate the raw data.

            ![DAT_00010fec](readme_files/ctf5_DAT_00010fec.png)

            Lets clear the data formatting for this obfuscated data for now. select all the data here and press `C`, or select it and right click, then select `Clear Code Bytes`.

            ![DAT_00010fec clear](readme_files/ctf5_DAT_00010fec_clear.png)

            ![DAT_00010fec cleared](readme_files/ctf5_DAT_00010fec_cleared.png)

            In the C language, the storage used for a variable is very important. Each variable type can only hold data up to a certain value, after which if the variable value continues to grow then data is lost. See [Integer Overflow](https://en.wikipedia.org/wiki/Integer_overflow). Integer overflow is why the `9-bit` values in the table below are truncated down to `8-bit` values.

            | Initial Byte    | Math                               | Boolean Result                                                  | [ASCII](https://www.asciitable.com/) Result       |
            |:----------------|:-----------------------------------|:----------------------------------------------------------------|:-------------------|
            | `0xD6` or `214` | `0xD6`+`0x80`=`0x156` or `214`+`128`=`342` | 9-bit `0b101010110` becomes 8-bit `0b01010110` or `0x56` or `86`  | `0x56` or `86` is `V`  |
            | `0xE5` or `229` | `0xE5`+`0x80`=`0x165` or `229`+`128`=`357` | 9-bit `0b101100101` becomes 8-bit `0b01100101` or `0x65` or `101` | `0x65` or `101` is `e` |
            | `0xEC` or `236` | `0xEC`+`0x80`=`0x16C` or `236`+`128`=`364` | 9-bit `0b101101100` becomes 8-bit `0b01101100` or `0x6C` or `108` | `0x6C` or `108` is `l` |
            | `0x__` or `___` | `0x__`+`0x80`=`0x___` or `___`+`128`=`___` | 9-bit `0b_________` becomes 8-bit `0b________` or `0x__` or `___` | `0x__` or `___` is `_` |
            | `0x__` or `___` | `0x__`+`0x80`=`0x___` or `___`+`128`=`___` | 9-bit `0b_________` becomes 8-bit `0b________` or `0x__` or `___` | `0x__` or `___` is `_` |
            | `0x__` or `___` | `0x__`+`0x80`=`0x___` or `___`+`128`=`___` | 9-bit `0b_________` becomes 8-bit `0b________` or `0x__` or `___` | `0x__` or `___` is `_` |
            | `0x__` or `___` | `0x__`+`0x80`=`0x___` or `___`+`128`=`___` | 9-bit `0b_________` becomes 8-bit `0b________` or `0x__` or `___` | `0x__` or `___` is `_` |
            | `0x__` or `___` | `0x__`+`0x80`=`0x___` or `___`+`128`=`___` | 9-bit `0b_________` becomes 8-bit `0b________` or `0x__` or `___` | `0x__` or `___` is `_` |
            | `0x__` or `___` | `0x__`+`0x80`=`0x___` or `___`+`128`=`___` | 9-bit `0b_________` becomes 8-bit `0b________` or `0x__` or `___` | `0x__` or `___` is `_` |
            | `0x__` or `___` | `0x__`+`0x80`=`0x___` or `___`+`128`=`___` | 9-bit `0b_________` becomes 8-bit `0b________` or `0x__` or `___` | `0x__` or `___` is `_` |
            | `0x__` or `___` | `0x__`+`0x80`=`0x___` or `___`+`128`=`___` | 9-bit `0b_________` becomes 8-bit `0b________` or `0x__` or `___` | `0x__` or `___` is `_` |

            Complete the table or write a script to determine the values of the password or flag.
