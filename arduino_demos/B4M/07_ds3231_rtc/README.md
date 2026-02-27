# B4M Arduino Example 07: How to Use DS3231 RTC Clock

## Description
This example demonstrates how to use the DS3231 Real-Time Clock (RTC) module on the B4M board. It shows how to:
- Initialize the DS3231 over I2C.
- Read the current date and time.
- Set the RTC time via serial commands.

## File Structure
- `src/B4M_07_ds3231_rtc.ino` – Arduino source code for customization and compilation.
- `precompiled/B4M_07_ds3231_rtc.bin` – Precompiled firmware binary for ESP32-S3, ready for direct flashing.

## Using the Precompiled Binary (.bin)
1. Download the `.bin` file from the `precompiled/` folder.
2. Use the official **ESP Flash Download Tool** or `esptool.py` to flash it to the B4M controller.
3. **Flash Address**: `0x0` (as indicated in the forum post).

## Compiling from Source
1. **Environment**: Install Arduino IDE and add ESP32-S3 board support (via Boards Manager).
2. **Dependencies**:
   - `Wire.h` (built-in)
   - `DS3231.h` – Install via Library Manager (search for "DS3231" by "Eric Ayars" or similar).
3. **Steps**:
   - Open `src/B4M_07_ds3231_rtc.ino` in Arduino IDE.
   - Select the correct board (`B4M`) and port.
   - Compile and upload.

## Serial Commands
After uploading, open the Serial Monitor at **115200 baud**. You can use the following commands:

- **`current time`** – Prints the current date and time from the RTC.
- **`DYYYY-MM-DDTHH:MM:SS`** – Sets the RTC to the specified date and time.  
  Example: `D2024-09-19T11:50:22` sets the time to September 19, 2024, 11:50:22.

## Expected Output
On startup, the current time is printed:
  Current time is: 2024-01-01 00:00:10
After sending `current time`, the same format is displayed.

## Important Notes
- **I2C Pins**: The code uses SDA = GPIO8, SCL = GPIO18, matching the B4M pin definition.
- **RTC Battery**: Ensure the DS3231 has a backup battery (e.g., CR2032) to retain time when main power is off.
- **Command Format**: The setting command is case-sensitive and must be exactly 20 characters long (e.g., `D2024-09-19T11:50:22`). The code validates this length and the positions of 'D' and 'T'.
- **Relay Constants**: The code defines `OPEN_RLY_DATA`, `OPEN_RLY_MONTH`, etc., but these are **not used** in this example. They can be ignored or removed.
- **24-Hour Mode**: The RTC is set to 24-hour mode (`rtc.setClockMode(false)`). AM/PM indicators are not used.
