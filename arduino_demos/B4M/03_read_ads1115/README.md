# B4M Arduino Example 03: Read ADS1115 Analog Input Ports Value

## Description
This example demonstrates how to read voltage values from all four channels (A0, A1, A2, A3) of the ADS1115 ADC module on the B4M board. The readings are printed to the Serial Monitor in millivolts (mV).

## File Structure
- `src/B4M_03_read_ads1115.ino` – Arduino source code for customization and compilation.
- `precompiled/B4M_03_read_ads1115.bin` – Precompiled firmware binary for ESP32-S3, ready for direct flashing.

## Using the Precompiled Binary (.bin)
1. Download the `.bin` file from the `precompiled/` folder.
2. Use the official **ESP Flash Download Tool** or `esptool.py` to flash it to the B4M controller.
3. **Flash Address**: `0x0` (as indicated in the forum post).

## Compiling from Source
1. **Environment**: Install Arduino IDE and add ESP32-S3 board support (via Boards Manager).
2. **Dependencies**:
   - `Wire.h` (built-in)
   - `DFRobot_ADS1115.h` – Install via Library Manager (search for "DFRobot ADS1115") or download from [DFRobot's GitHub](https://github.com/DFRobot/DFRobot_ADS1115).
3. **Steps**:
   - Open `src/B4M_03_read_ads1115.ino` in Arduino IDE.
   - Select the correct board (`esp32-s3-devkitc-1`) and port.
   - Compile and upload.

## Expected Output
After flashing and opening the Serial Monitor (set to **115200 baud**), you will see output like:
A0:1234mV, A1:5678mV, A2:910mV, A3:112mV
(Values depend on input voltages.)

## Important Notes
- **I2C Address**: The code uses address `0x49` (`ADS1115_IIC_ADDRESS0`). Verify your hardware configuration – the B4M pin definition post mentions address `0x48`. If your board uses `0x48`, change the line to:
  ```cpp
  ads.setAddr_ADS1115(ADS1115_IIC_ADDRESS1);   // 0x48
- I2C Pins: SDA = GPIO8, SCL = GPIO18 (as defined in the code).
- Gain Setting: The gain is set to eGAIN_TWOTHIRDS, which allows a maximum input of ±6.144V. Adjust if your signal range differs.