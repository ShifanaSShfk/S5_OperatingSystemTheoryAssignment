# S5_OperatingSystemTheoryAssignment

# Character Device Driver Project

#Project Overview

This project involves creating a Linux Character Device Driver that verifies the kernel version before loading. The driver accepts a kernel_version parameter and performs a check to ensure it matches the current running kernel. The driver allows reading and writing operations, with the log messages generated for each operation stored in the kernel log. A user-space program is provided to interact with the driver through read and write commands.

#Problem Statement

The objective of this project is to develop a character device driver for Linux that enforces a kernel version check at the time of insertion. The driver accepts a kernel_version parameter to ensure compatibility with the currently running kernel version. After successful insertion, it should log its assigned major and minor numbers, support basic read/write operations, and log all interactions.

#Methodology

    Kernel Version Check: The driver checks if the specified kernel_version parameter matches the current kernel version.
    Device Operations: The driver supports reading and writing, allowing interaction through user-space applications.
    Logging: Each read/write interaction is logged in the kernel log for tracking and debugging.
    
#Project Structure

    Character_Device_Driver.c: Source code for the character device driver.
    test.c: User-space program to test reading and writing to the driver.
    Makefile: Automates the process of building the driver.
    README.md: Instructions and steps for executing the project.
    
#Requirements

    Linux Kernel Headers: Ensure the correct kernel headers are installed for your kernel version.
    Compiler: GCC or any compatible compiler.
    Root Privileges: Root access is required to insert, remove, and interact with the driver.
