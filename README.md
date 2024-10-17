# ESP32 Custom Bootloader Project

<!-- ## Table of Contents
1. [Introduction](#introduction)
2. [Project Overview](#project-overview)
3. [Prerequisites](#prerequisites)
4. [Project Structure](#project-structure)
5. [How It Works](#how-it-works)
6. [Building and Flashing](#building-and-flashing)
7. [Customization and Further Development](#customization-and-further-development)
8. [Advanced Topics](#advanced-topics)
9. [Troubleshooting](#troubleshooting)
10. [Resources](#resources) -->

## Introduction

This project implements a basic custom bootloader for the ESP32 microcontroller. It serves as a learning tool to understand the boot process of ESP32 and how to implement custom bootloader functionality. 

## Project Overview

The bootloader is responsible for initializing the system, verifying the presence of a valid application, and jumping to the main application if one is found. This project demonstrates these fundamental bootloader operations in a simplified manner.

Key features:
- System initialization
- Basic application verification
- Jumping to the main application

## Prerequisites

To use this project, you need:
- ESP-IDF (v4.4 or later)
- Python 3.6 or newer
- A compatible ESP32 development board
- USB cable for connecting the ESP32 to your computer

<!-- ## Project Structure

```
esp32_bootloader/
├── CMakeLists.txt
├── main/
│   ├── CMakeLists.txt
│   ├── bootloader_main.c
│   ├── bootloader_utility.c
│   └── bootloader_utility.h
├── partitions.csv
├── sdkconfig
└── README.md
``` -->

- `bootloader_main.c`: The main entry point for the bootloader
- `bootloader_utility.c`: Contains utility functions for bootloader operations
- `bootloader_utility.h`: Header file for bootloader utilities
- `partitions.csv`: Defines the partition table

## How It Works

1. **Initialization** (`bootloader_init`):
   - Initializes the SPI flash
   - Prints chip information

2. **Application Verification** (`bootloader_verify_app`):
   - Checks if a valid application is present at the expected address
   - In this simplified version, it just checks if the first byte is not 0xFF

3. **Jumping to Application** (`bootloader_jump_to_app`):
   - Disables interrupts
   - Sets up the initial stack pointer for the app
   - Jumps to the app's entry point

## Building and Flashing

1. Set up the ESP-IDF environment:
   ```
   . $HOME/esp/v5.3.1/esp-idf/export.sh
   ```
   (Adjust the path if you installed ESP-IDF in a different location)

2. Navigate to the project directory:
   ```
   cd path/to/esp32_bootloader
   ```

3. Build the project:
   ```
   idf.py build
   ```

4. Flash the project to your ESP32:
   ```
   idf.py -p (PORT) flash
   ```
   Replace (PORT) with your ESP32's port (e.g., /dev/ttyUSB0 on Linux)

5. Monitor the output:
   ```
   idf.py -p (PORT) monitor
   ```

## Customization and Further Development

1. **Enhance Application Verification:**
   - Implement checksums or digital signatures
   - Verify the application size and version

2. **Implement Secure Boot:**
   - Add encryption and signature verification
   - Implement anti-rollback protection

3. **Support Multiple Boot Partitions:**
   - Implement logic to choose between multiple application partitions
   - Add support for fallback to a previous version if boot fails

4. **Over-The-Air (OTA) Updates:**
   - Implement functionality to update the main application via OTA
   - Add support for updating the bootloader itself

5. **Error Handling and Recovery:**
   - Implement robust error handling mechanisms
   - Add support for entering a recovery mode if no valid application is found

6. **Logging and Debugging:**
   - Enhance logging capabilities for easier debugging
   - Implement a debug console accessible during the boot process

<!-- ## Advanced Topics

1. **Memory Layout:**
   Understanding the ESP32's memory layout is crucial for bootloader development. The bootloader typically resides at the beginning of the flash (0x1000), followed by the partition table and application(s).

2. **Secure Boot:**
   Implementing secure boot involves verifying the integrity and authenticity of the firmware before executing it. This requires careful management of encryption keys and certificates.

3. **Flash Encryption:**
   ESP32 supports flash encryption to protect sensitive data. Integrating this with your bootloader requires careful consideration of the encryption process and key management.

4. **Customizing Partition Tables:**
   The `partitions.csv` file defines how the flash memory is partitioned. Customizing this can allow for multiple application partitions, data storage, etc. -->

## Troubleshooting

- **Build Errors:** Ensure you're using a compatible ESP-IDF version and that all required components are installed.
- **Flash Errors:** Check your connections and ensure you're using the correct port.
- **Boot Loops:** If the ESP32 is stuck in a boot loop, there might be an issue with the application verification or jump logic.

## Resources

- [ESP-IDF Programming Guide](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [ESP32 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [ESP32 Boot Process](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/startup.html)

