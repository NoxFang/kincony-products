# B4 Arduino Example 11: Digital Input Triggers Output Directly

## Description
This example demonstrates a direct linkage between the 4 digital inputs and the 4 relay outputs on the B4 board using the PCF8574 I/O expander. It continuously reads the state of input pins (P0-P3) and immediately updates the corresponding output pins (P4-P7). When an input pin is **LOW**, the associated relay output is set to **LOW** (turning the relay ON).

## File Structure
- `src/B4_11_input_trigger_output.ino` – Arduino source code for customization and compilation.
- `precompiled/B4_11_input_trigger_output.bin` – Precompiled firmware binary for ESP32-S3, ready for direct flashing.

## Using the Precompiled Binary (.bin)
1. Download the `.bin` file from the `precompiled/` folder.
2. Use the official **ESP Flash Download Tool** or `esptool.py` to flash it to the B4 controller.
3. **Flash Address**: `0x0` (as indicated in the forum post).

## Compiling from Source
1. **Environment**: Install Arduino IDE and add ESP32-S3 board support (via Boards Manager).
2. **Dependencies**:
   - `Wire.h` (built-in)
   - `PCF8574.h` – Install via Library Manager (search for "PCF8574" by Renzo Mischianti or similar).
3. **Steps**:
   - Open `src/B4_11_input_trigger_output.ino` in Arduino IDE.
   - Select the correct board (`esp32-s3-devkitc-1`) and port.
   - Compile and upload.

## Expected Behavior
- The board reads the four digital inputs (connected to PCF8574 pins P0-P3).
- The state of each input directly controls the corresponding relay output (PCF8574 pins P4-P7):
  - **Input 0 (P0) → Relay 1 (P4)**
  - **Input 1 (P1) → Relay 2 (P5)**
  - **Input 2 (P2) → Relay 3 (P6)**
  - **Input 3 (P3) → Relay 4 (P7)**
- When an input pin is connected to GND (LOW), its corresponding relay activates (LOW). When the input is floating or HIGH, the relay remains off (HIGH).
- There is a small 50ms delay between reading each input/output pair for stability.

## Important Notes
- **I2C Pins**: The code uses SDA = GPIO8, SCL = GPIO18, matching the B4 pin definition.
- **PCF8574 Address**: The I2C address is set to `0x24`, which is correct for the B4's PCF8574.
- **Input/Output Mapping**: The mapping is fixed in the `loop()`:
  ```cpp
  if (digitalRead(0)) digitalWrite(4, HIGH); else digitalWrite(4, LOW);
This means a HIGH input keeps the relay off (HIGH), and a LOW input turns the relay on (LOW).
- Pull-up Resistors: The inputs (P0-P3) on the B4 typically have pull-up resistors. This means they read HIGH when no connection is made. To trigger an input, connect it to GND.
- Relay Logic: The code assumes relays are active-LOW (energized when the pin is LOW). This matches typical KinCony hardware. Verify with your specific board revision.
- Debouncing: The example does not include software debouncing. For noisy environments, consider adding a small capacitor across the input or implementing a debounce routine.
- Serial Monitor: No serial output is used in this example, so the Serial Monitor is optional.

## References
1. For detailed pinout information, see the B4 pin definition.
2. For the PCF8574 library documentation, visit the library repository.