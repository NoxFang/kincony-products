# B4M Arduino Example 04: RS485 Communication Test

## Description
This example demonstrates basic RS485 communication on the B4M board using the ESP32-S3's hardware serial interface. It periodically sends a test message over RS485 and listens for any incoming messages, printing received data to the Serial Monitor.

## File Structure
- `src/B4M_04_rs485_test.ino` – Arduino source code for customization and compilation.
- `precompiled/B4M_04_rs485_test.bin` – Precompiled firmware binary for ESP32-S3, ready for direct flashing.

## Using the Precompiled Binary (.bin)
1. Download the `.bin` file from the `precompiled/` folder.
2. Use the official **ESP Flash Download Tool** or `esptool.py` to flash it to the B4M controller.
3. **Flash Address**: `0x0` (as indicated in the forum post).

## Compiling from Source
1. **Environment**: Install Arduino IDE and add ESP32-S3 board support (via Boards Manager).
2. **Dependencies**:
   - `HardwareSerial.h` (built-in with ESP32 core)
3. **Steps**:
   - Open `src/B4M_04_rs485_test.ino` in Arduino IDE.
   - Select the correct board (`B4M`) and port.
   - Compile and upload.

## Expected Behavior
- The board will repeatedly send the message `Hello from B4M!` over RS485 every 3 seconds (1-second delay after send + 2-second delay before next send).
- If another RS485 device is connected and responds, received messages will be printed to the Serial Monitor in the format:
  Received: <response message>

## Important Notes
- **Pin Definition Correction**: The code uses the correct RS485 pins for B4M: **RXD = GPIO39, TXD = GPIO38**. Please ignore the conflicting pin numbers in the code comments (which incorrectly mention GPIO18 and GPIO8). Always refer to the actual `#define` values in the code.
- **Loopback Test**: To test without another device, you can connect the RS485 TX and RX pins (through a converter or directly) to see your own sent message echoed back.
- **Baud Rate**: The communication is set to `9600` baud. Ensure any connected device uses the same settings.
- **Serial Monitor**: Open the Serial Monitor at **115200 baud** to view debug output and received messages.