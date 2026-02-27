# B4M Arduino Example 06: How to Use SD Card

## Description
This example demonstrates basic file operations on an SD card using the B4M board. It shows how to initialize the SD card, perform read/write/append/delete operations, and test file I/O performance. All results are printed to the Serial Monitor.

## File Structure
- `src/B4M_06_sd_card_operations.ino` – Arduino source code for customization and compilation.
- `precompiled/B4M_06_sd_card_operations.bin` – Precompiled firmware binary for ESP32-S3, ready for direct flashing.

## Using the Precompiled Binary (.bin)
1. Download the `.bin` file from the `precompiled/` folder.
2. Use the official **ESP Flash Download Tool** or `esptool.py` to flash it to the B4M controller.
3. **Flash Address**: `0x0` (as indicated in the forum post).

## Compiling from Source
1. **Environment**: Install Arduino IDE and add ESP32-S3 board support (via Boards Manager).
2. **Dependencies**:
   - `FS.h`, `SD.h`, `SPI.h` (all built-in with ESP32 core)
3. **Steps**:
   - Open `src/B4M_06_sd_card_operations.ino` in Arduino IDE.
   - Select the correct board (`B4M`) and port.
   - Compile and upload.

## Expected Output (Serial Monitor at 115200 baud)
After inserting a formatted SD card and resetting the board, you should see output similar to:
   - SD Card Type: SDHC
   - SD Card Size: 3817MB
   - Reading file: /hello.txt
   - Read from file: Hello World!
   - Total space: 3817MB
   - Used space: 16MB
Additional performance test results will also be printed.

## Important Notes
- **Pin Configuration**: The code uses the following B4M SD Card pins:
  - SCK  = GPIO11
  - MISO = GPIO12
  - MOSI = GPIO10
  - CS   = GPIO9
- **SPI Initialization**: The code explicitly uses `HSPI` for the SD card. If you have other SPI devices, ensure they are on different buses or properly managed.
- **SD Card Format**: The card should be formatted as FAT16 or FAT32. Cards larger than 32GB may not work reliably.
- **Power Supply**: SD cards can draw significant current during writes. Ensure your B4M is powered adequately (not just via USB from a weak source) to avoid corruption.
- **File Operations**: The `setup()` function performs a sequence of file tests. The `loop()` is empty, so the test runs only once at startup. Reset the board to repeat.
- **Refer to Pin Definitions**: For detailed pinout information, see the [B4M pin definition](../../../pin_definitions/B4M_pin_definition.md).