/*
 * Description:
 * This Arduino program reads the state of a 16-channel PCF8574 I/O expander
 * and prints the state of all input pins to the Serial Monitor. The state of 
 * each pin is represented as a bit in a 8-bit value, where each bit corresponds 
 * to an input pin. The program prints the input state in binary format.
 *
 * Pin Definitions:
 * - SDA: GPIO 21
 * - SCL: GPIO 22
 * - PCF8575 I2C Address: 0x24
 */

#include "Arduino.h"
#include "PCF8574.h"

// Define I2C pins
#define I2C_SDA 8  // Define SDA pin
#define I2C_SCL 18  // Define SCL pin

// Set I2C address
PCF8574 pcf8574_IN1(0x24); // The I2C address of the PCF8575

void setup() {
    Serial.begin(115200);

    // Initialize I2C communication
    Wire.begin(I2C_SDA, I2C_SCL); // Initialize I2C with defined SDA and SCL pins

    pcf8574_IN1.pinMode(P0, INPUT);
    pcf8574_IN1.pinMode(P1, INPUT);
    pcf8574_IN1.pinMode(P2, INPUT);
    pcf8574_IN1.pinMode(P3, INPUT);

    pcf8574_IN1.begin(); // Initialize the PCF8575

    Serial.println("F4 Controller 4 channel input state 0:ON  1:OFF");
}

void loop() {
    uint16_t state = 0;

    // Read the state of each pin (assuming 16 pins)
    for (int pin = 0; pin < 4; pin++) {
        if (pcf8574_IN1.digitalRead(pin)) {
            state |= (1 << pin); // Set the bit for the active pin
        }
    }

    Serial.print("Input state: ");
    Serial.println(state, BIN); // Print the state of inputs in binary

    delay(500); // Delay 500ms
}
