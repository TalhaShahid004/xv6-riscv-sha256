# xv6-riscv-sha256

<p align="center">
This repository contains a modified version of the xv6 operating system, targeting the RISC-V architecture and integrating SHA-256 cryptographic hashing capabilities. It provides a learning platform for understanding operating system principles and practical cryptography application.
</p>

## Project Description

This project is a modified implementation of the xv6 operating system, which is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix Version 6 (v6), originally written for a PDP-11. This version targets a RISC-V 64-bit architecture and includes a custom SHA-256 cryptographic hash implementation. This system is intended to serve as a practical example for OS development, system calls, memory management, concurrency, and application of cryptography in an embedded environment.

## Key Features

* **RISC-V Architecture Support:** This xv6 port targets a modern RISC-V architecture, enabling better understanding and experimentation on contemporary hardware.
* **SHA-256 Implementation:** A functional SHA-256 cryptographic hash is integrated into the xv6 kernel and user space.
* **Operating System Fundamentals:** Provides comprehensive practical examples for process management, memory allocation, file systems, device drivers, etc.
* **User-Space Utilities:** Includes basic tools like cat, echo, ls, mkdir, etc., all built for the custom xv6 environment.

## Installation and Setup

1. **RISC-V Toolchain:** You will need a RISC-V GNU toolchain. Follow the instructions at [https://github.com/riscv/riscv-gnu-toolchain](https://github.com/riscv/riscv-gnu-toolchain) to install it. This is essential for compiling the kernel and user programs.
2. **QEMU:** Install QEMU with riscv64-softmmu support. This emulator is used for running the compiled xv6 system.
3. **Clone the repository:**
    ```bash
    git clone https://github.com/TalhaShahid004/xv6-riscv-sha256.git
    cd xv6-riscv-sha256
    ```

## Running the Project

1. **Compile the operating system and tools:**
    ```bash
    make clean
    make
    ```

2. **Run the operating system in QEMU:**
    ```bash
    make qemu
    ```
    This command compiles the xv6 kernel and user programs, creates a disk image containing them, and runs QEMU with the xv6 operating system. Once the system is booted, you will see the xv6 shell, where commands can be executed. For example, type `ls` to list the files or `usha256 <string>` to compute SHA256 hash.

## Dependencies and Tools

* **RISC-V GNU Toolchain:** Compiler and associated tools for RISC-V architecture
* **QEMU:** Emulator for running the RISC-V architecture
* **make:** Build tool for compiling the OS
* **Perl:** Required for generating syscall stubs
* **gcc:** C compiler

## License

This project is licensed under the MIT License. See the `LICENSE` file for more information.
