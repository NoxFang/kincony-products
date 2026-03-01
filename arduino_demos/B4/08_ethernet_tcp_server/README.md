# B4 Arduino Example 08: Ethernet W5500 TCP Server

## Description
This example demonstrates how to use the W5500 Ethernet module on the B4 board as a TCP server. The server listens on port **4196** and echoes back any string received from a connected client. It uses a static IP configuration.

## File Structure
- `src/B4_08_ethernet_tcp_server.ino` – Arduino source code for customization and compilation.
- `precompiled/B4_08_ethernet_tcp_server.bin` – Precompiled firmware binary for ESP32-S3, ready for direct flashing.

## Using the Precompiled Binary (.bin)
1. Download the `.bin` file from the `precompiled/` folder.
2. Use the official **ESP Flash Download Tool** or `esptool.py` to flash it to the B4 controller.
3. **Flash Address**: `0x0` (as indicated in the forum post).

## Compiling from Source
1. **Environment**: Install Arduino IDE and add ESP32-S3 board support (via Boards Manager).
2. **Dependencies**:
   - `SPI.h` (built-in)
   - `Ethernet.h` (built-in, part of the Arduino Ethernet library)
3. **Steps**:
   - Open `src/B4_08_ethernet_tcp_server.ino` in Arduino IDE.
   - Select the correct board (`esp32-s3-devkitc-1`) and port.
   - Compile and upload.

## Expected Behavior
- After uploading, open the Serial Monitor at **115200 baud**. The device will display its assigned IP address (static: 192.168.3.55).
- It acts as a TCP server on port 4196. You can connect to it using a TCP client tool (e.g., PuTTY, telnet, or a Python script).
- Any data sent by the client will be echoed back immediately.

## Important Notes
- **Pin Definition Correction**: The code uses the following **actual pin definitions** (see `#define` directives):
  - **CLK** (SCK)  = GPIO1
  - **MOSI**       = GPIO2
  - **MISO**       = GPIO41
  - **CS**         = GPIO42
  - **RST**        = GPIO44
  - **INT**        = GPIO43
  **Please ignore the conflicting pin order in the code comments**; always refer to the `#define` values.
- **Network Configuration**: The static IP is set to `192.168.3.55` with gateway `192.168.3.1`. Modify these values in the code to match your local network.
- **MAC Address**: The code uses a sample MAC `{0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED}`. If multiple devices on your network use the same MAC, change it to a unique one.
- **SPI Initialization**: The line `SPI.begin(W5500_CLK_PIN, W5500_MISO_PIN, W5500_MOSI_PIN)` correctly initializes SPI with the defined pins.
- **Ethernet Library**: Ensure you are using a version of the Ethernet library compatible with the W5500 and ESP32. The built-in library usually works.