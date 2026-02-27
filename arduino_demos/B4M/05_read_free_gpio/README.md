# B4M Arduino Example 05: Read Free GPIO State

## Description
This example demonstrates how to read the digital state (HIGH/LOW) of several free GPIO pins on the B4M board. The program reads the status of pins GPIO0, GPIO13, GPIO14, GPIO17, GPIO21, GPIO40, GPIO47, and GPIO48, then prints all states to the Serial Monitor every second.

## File Structure
- `src/B4M_05_read_free_gpio.ino` – Arduino source code for customization and compilation.
- `precompiled/B4M_05_read_free_gpio.bin` – Precompiled firmware binary for ESP32-S3, ready for direct flashing.

## Using the Precompiled Binary (.bin)
1. Download the `.bin` file from the `precompiled/` folder.
2. Use the official **ESP Flash Download Tool** or `esptool.py` to flash it to the B4M controller.
3. **Flash Address**: `0x0` (as indicated in the forum post).

## Compiling from Source
1. **Environment**: Install Arduino IDE and add ESP32-S3 board support (via Boards Manager).
2. **Dependencies**: None (uses standard Arduino functions).
3. **Steps**:
   - Open `src/B4M_05_read_free_gpio.ino` in Arduino IDE.
   - Select the correct board (`B4M`) and port.
   - Compile and upload.

## Expected Output
After flashing and opening the Serial Monitor (set to **115200 baud**), you will see output like:
  GPIO13: 1, GPIO40: 0, GPIO14: 1, GPIO48: 0, GPIO0: 1, GPIO47: 0, GPIO17: 1, GPIO21: 0
(Values depend on external connections: `1` = HIGH, `0` = LOW.)

## Important Notes
- **Pin List**: The code reads the following free GPIOs: 13, 40, 14, 48, 0, 47, 17, 21. Refer to the [B4M pin definition](../../../pin_definitions/B4M_pin_definition.md) for details on pull-up resistors and default states.
- **No External Connection**: If a pin is left floating (not connected), its state may be random or unstable. For meaningful readings, connect the pin to GND (LOW) or 3.3V (HIGH), or enable internal pull-up/pull-down resistors in the code.
- **GPIO0 Note**: GPIO0 is often used for boot mode selection. Avoid pulling it LOW during power-up or reset, as it may put the chip into flashing mode.
- **Serial Monitor**: Ensure the baud rate matches `115200` in the Serial Monitor.