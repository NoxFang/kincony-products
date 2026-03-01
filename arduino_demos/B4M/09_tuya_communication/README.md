# B4M Arduino Example 09: Communication with Tuya WiFi Module

## Description
This example demonstrates how the B4M board (ESP32-S3) communicates with an attached Tuya WiFi module via UART. It listens for specific command packets from the Tuya module and sends the appropriate predefined responses. This is a foundational example for integrating Tuya-based cloud control.

The handled commands include:
- Heartbeat (initial and subsequent)
- Product information request
- Work mode request
- Network status request

## File Structure
- `src/B4M_09_tuya_communication.ino` – Arduino source code for customization and compilation.
- `precompiled/B4M_09_tuya_communication.bin` – Precompiled firmware binary for ESP32-S3, ready for direct flashing.

## Using the Precompiled Binary (.bin)
1. Download the `.bin` file from the `precompiled/` folder.
2. Use the official **ESP Flash Download Tool** or `esptool.py` to flash it to the B4M controller.
3. **Flash Address**: `0x0` (as indicated in the forum post).

## Compiling from Source
1. **Environment**: Install Arduino IDE and add ESP32-S3 board support (via Boards Manager).
2. **Dependencies**:
   - `HardwareSerial.h` (built-in with ESP32 core)
3. **Steps**:
   - Open `src/B4M_09_tuya_communication.ino` in Arduino IDE.
   - Select the correct board (`esp32-s3-devkitc-1`) and port.
   - Compile and upload.

## Expected Behavior
- After uploading, open the Serial Monitor at **115200 baud** for debug output.
- The ESP32 will initialize serial communication with the Tuya module on pins TX=15, RX=16 at 9600 baud.
- When the Tuya module sends specific command packets, the ESP32 will log the received packet and send the corresponding response.
- Debug messages (e.g., "Heartbeat received", "Sent packet: ...") will be printed to the Serial Monitor.

## Important Notes
- **Pin Connections**: The code uses **TXD_PIN = 15, RXD_PIN = 16**, which matches the B4M pin definition for the Tuya module interface.
- **Baud Rate**: Communication with the Tuya module is fixed at **9600 baud**. Do not change this unless your module requires a different rate.
- **Packet Formats**: The response packets (heartbeat, product info, etc.) are hardcoded as byte arrays. These are based on typical Tuya module protocols. If your module uses a different firmware version, the required responses might differ.
- **First vs. Subsequent Heartbeat**: Note that the code sends `heartBeatResponse` for the first detected heartbeat, and `secondHeartBeatResponse` for later heartbeats (the code logic routes them correctly based on the command bytes).
- **Product Info Payload**: The `productInfoResponse` contains a JSON-like structure embedded in the byte array. It informs the Tuya module about the product capabilities.
- **Serial Monitor**: Use the Serial Monitor to observe the handshake process. It helps in debugging if the Tuya module does not enter the expected state.

## References
- For more details on the Tuya module pinout, refer to the [B4M pin definition](../../../pin_definitions/B4M_pin_definition.md).