# libasm - Assembly Language Library

## Overview

`libasm` is a library implemented in assembly language, focusing on providing a set of low-level programming functionalities closely aligned with the machine's architecture. Assembly language offers a unique approach where the code directly corresponds to the machine's instructions, enabling precise control and optimization not typically available in high-level languages. This project is aimed at those interested in understanding the intricacies of system-level programming and the inner workings of computers.

## Features

The library offers a reimplementation of several standard C library functions, showcasing how to work with system calls, error handling, and basic memory operations in assembly. These functions include:

- `ft_strlen`: Calculate the length of a string.
- `ft_strcpy`: Copy a string to another.
- `ft_strcmp`: Compare two strings.
- `ft_write`: Write to a file descriptor.
- `ft_read`: Read from a file descriptor.
- `ft_strdup`: Duplicate a string, with memory allocation.

Error handling is a critical aspect of `libasm`. The library meticulously checks for errors during syscalls and sets the `errno` variable appropriately, ensuring robustness and reliability.

## Getting Started

To use `libasm`, clone this repository to your local machine and build the library using the provided Makefile:

```sh
git clone https://github.com/yass-mhl/libasm.git
cd libasm
make
make test
./test
```

The Makefile supports the following rules: `all`, `clean`, `fclean`, `re`,`test` and the mandatory `$(NAME)` target to build the `libasm.a` library.

### Requirements

- An environment capable of assembling 64-bit assembly code.
- `nasm` for assembling the `.s` files.
- GNU `make` for automating the build process.
- A C compiler (GCC) for compiling the test main.

### Testing

Although the submission does not include test programs, users are encouraged to write their own tests to verify the functionality of the library. A simple main file is provided to demonstrate how to link against `libasm.a` and test its functions.

## Restrictions

- The project mandates the use of 64-bit assembly, adhering to the "calling convention".
- Inline assembly is prohibited; all assembly code must reside in `.s` files.
- The Intel syntax is required for all assembly code.
- The compilation flag `-no-pie` is not allowed.

## Contributions

Contributions to `libasm` are welcome. Whether it's adding new features, improving existing functions, or fixing bugs, your help is appreciated. Please submit a pull request or open an issue if you have suggestions or identify a problem.

## License

`libasm` is open-source. Feel free to use, modify, and distribute the library as per the license agreement.

## Acknowledgments

This project is a testament to the power and precision of assembly language. It's designed for educational purposes, helping others grasp the fundamentals of low-level programming and encouraging a deeper understanding of computer architecture.
