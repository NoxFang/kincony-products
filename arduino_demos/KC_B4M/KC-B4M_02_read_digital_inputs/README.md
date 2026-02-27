# Kincony B4M Arduino Example 02 Read Digital Input Ports State

## Description
This example demonstrates how to read the state of the 4 digital input ports on the B4M board (connected via a PCF8574 IO expander). The program reads the status of pins P0 to P3 and prints the combined state as a binary number to the Serial Monitor.

## File Structure
- `srcKC-B4M_02_read_digital_inputs.ino` Arduino source code. Intended for developers who want to compile or modify the code themselves.
- `precompiledKC-B4M_02_read_digital_inputs.bin` Precompiled firmware binary for ESP32-S3. Suitable for users who want to quickly test the functionality without setting up a development environment.

## Using the Precompiled Binary (.bin)
1.  Download the `.bin` file from the `precompiled` folder.
2.  Use the official ESP Flash Download Tool or `esptool.py` to flash it to the B4M controller.
3.  Flash Address `0x0` (as indicated in the forum post).

## Compiling from Source
1.  Environment Install Arduino IDE and add ESP32-S3 board support (via Boards Manager).
2.  Dependencies Install the `PCF8574.h` library (search for PCF8574 in the Library Manager).
3.  Steps Open the `.ino` file inside the `src` folder with Arduino IDE, select the correct board (`B4M`) and port, then compile and upload.

## Expected Output
After flashing and opening the Serial Monitor (set to 115200 baud), you will see messages like