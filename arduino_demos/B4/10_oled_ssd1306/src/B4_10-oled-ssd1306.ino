/* 
 * This Arduino program demonstrates how to display text on an SSD1306 128x64 OLED display using the U8g2 library.
 * The program draws two lines of text on the display:
 * - The first line is "B4 Controller" in a larger font.
 * - The second line is "www.huborin.com" in a smaller font.
 * 
 * The display is connected via I2C (software implementation) with:
 * - SCL (clock) on pin IO18
 * - SDA (data) on pin IO8
 * 
 * The display's I2C address is set to 0x3C.
 */

#include <U8g2lib.h>  // Include the U8g2 library for controlling the OLED display
#include <Wire.h>     // Include the Wire library for I2C communication

// Initialize the display using the software I2C method (SCL = IO18, SDA = IO8)
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0,  18, 8, U8X8_PIN_NONE);  // Screen rotation: U8G2_R0

// Function to display page 1 content
void page1() {
  // Set font size 18 for the larger "B4 Controller" text
  u8g2.setFont(u8g2_font_timR18_tf);  // Use the Times Roman font, size 18
  u8g2.setFontPosTop();               // Set the text position at the top of the display
  u8g2.setCursor(5, 0);               // Position the cursor at coordinates (5, 0)
  u8g2.print("B4 Controller");              // Display the text "B4 Controller" on the screen

  // Set font size 12 for the smaller "www.huborin.com" text
  u8g2.setFont(u8g2_font_timR12_tf);  // Use the Times Roman font, size 12
  u8g2.setCursor(0, 40);              // Position the cursor at coordinates (0, 40)
  u8g2.print("www.huborin.com");      // Display the text "www.huborin.com"
}

// Setup function, runs once when the program starts
void setup() {
  // Set the I2C address for the display to 0x3C
  u8g2.setI2CAddress(0x3C*2);  // I2C address shift for 8-bit format
  
  // Initialize the display
  u8g2.begin();
  
  // Enable UTF-8 character printing for the display
  u8g2.enableUTF8Print();  // Allow UTF-8 encoded text to be printed
}

// Main loop function, continuously runs after setup()
void loop() {
  // Begin the display drawing process
  u8g2.firstPage();  // Prepare the first page for drawing
  do {
    // Call the page1() function to draw content on the display
    page1();
  } while (u8g2.nextPage());  // Continue to the next page until all pages are drawn
}
