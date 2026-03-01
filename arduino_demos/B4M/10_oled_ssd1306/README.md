# B4M Arduino Example 10: Print Text on SSD1306 OLED Display

## Description
This example demonstrates how to display text on the onboard SSD1306 128x64 OLED display using the U8g2 library. It shows two lines:
- **"HUBORIN"** in a larger font.
- **"www.huborin.com"** in a smaller font.
The display is connected via I2C (software I2C implementation).

## File Structure
- `src/B4M_10_oled_ssd1306.ino` – Arduino source code for customization and compilation.
- `precompiled/B4M_10_oled_ssd1306.bin` – Precompiled firmware binary for ESP32-S3, ready for direct flashing.

## Using the Precompiled Binary (.bin)
1. Download the `.bin` file from the `precompiled/` folder.
2. Use the official **ESP Flash Download Tool** or `esptool.py` to flash it to the B4M controller.
3. **Flash Address**: `0x0` (as indicated in the forum post).

## Compiling from Source
1. **Environment**: Install Arduino IDE and add ESP32-S3 board support (via Boards Manager).
2. **Dependencies**:
   - `Wire.h` (built-in)
   - `U8g2lib.h` – Install via Library Manager (search for "U8g2" by "oliver")
3. **Steps**:
   - Open `src/B4M_10_oled_ssd1306.ino` in Arduino IDE.
   - Select the correct board (`esp32-s3-devkitc-1`) and port.
   - Compile and upload.

## Expected Behavior
After flashing, the OLED display will show:
- **HUBORIN** near the top of the screen.
- **www.huborin.com** below it.
The display content is static and continuously refreshed in the `loop()`.

## Important Notes
- **I2C Pins**: The code uses software I2C with **SCL = GPIO18, SDA = GPIO8**, matching the B4M pin definition.
- **I2C Address**: The display address is `0x3C`. In the code, it is set using `u8g2.setI2CAddress(0x3C*2);` because the U8g2 library expects the 8-bit shifted address (0x78). Do not change this unless your display uses a different address.
- **Software I2C**: The display is initialized with `U8G2_SSD1306_128X64_NONAME_F_SW_I2C`, which uses software I2C. This is flexible but may be slightly slower than hardware I2C. For better performance, you could switch to hardware I2C by using the appropriate constructor (e.g., `U8G2_SSD1306_128X64_NONAME_1_HW_I2C`) and ensuring `Wire` is properly initialized.
- **Font Selection**: The example uses Times Roman fonts (`u8g2_font_timR18_tf` and `u8g2_font_timR12_tf`). U8g2 includes many built-in fonts; you can change them as needed.
- **UTF-8 Support**: `u8g2.enableUTF8Print()` is called to allow printing UTF-8 characters. This is useful for displaying special characters or symbols.

## References
- For detailed pinout information, see the [B4M pin definition](../../../pin_definitions/B4M_pin_definition.md).
- For more U8g2 examples and font lists, visit the [U8g2 library documentation](https://github.com/olikraus/u8g2).