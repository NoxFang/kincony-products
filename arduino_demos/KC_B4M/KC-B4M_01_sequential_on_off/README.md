# Kincony B4M Arduino Example 01: Sequential Relay On/Off

## Description
This example demonstrates how to control the 4 relays on the B4M board (via PCF8574) in a sequential on/off cycle using Arduino.

## File Structure
- **`src/KC-B4M_01_sequential_on_off.ino`**: Arduino source code. Intended for developers who want to compile or modify the code themselves.
- **`precompiled/KC-B4M_01_sequential_on_off.bin`**: Precompiled firmware binary for ESP32-S3. Suitable for users who want to quickly test the functionality without setting up a development environment.

## Using the Precompiled Binary (.bin)
1.  Download the `.bin` file from the `precompiled/` folder.
2.  Use the official **ESP Flash Download Tool** or `esptool.py` to flash it to the B4M controller.
3.  **Flash Address**: `0x0` (as indicated in the forum post).

## Compiling from Source
1.  **Environment**: Install Arduino IDE and add ESP32-S3 board support (via Boards Manager).
2.  **Dependencies**: Install the `PCF8574.h` library (search for "PCF8574" in the Library Manager).
3.  **Steps**: Open the `.ino` file inside the `src/` folder with Arduino IDE, select the correct board (`B4M`) and port, then compile and upload.