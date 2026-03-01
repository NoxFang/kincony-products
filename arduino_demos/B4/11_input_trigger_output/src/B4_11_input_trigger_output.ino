/*
 * This program reads 4 input states from a PCF8574 I/O expander and 
 * controls a corresponding 4-channel relay module. When an input pin 
 * is LOW, the corresponding relay is turned ON (LOW means ON for the relay).
 *
 * Pin Definitions:
 * - SDA: GPIO 8
 * - SCL: GPIO 18
 * - PCF8575 I2C Address: 0x24
 */

#include <Wire.h>
#include <PCF8574.h>

// I2C pins
#define SDA 8
#define SCL 18

// PCF8575 I2C address
#define INPUT_I2C_ADDRESS 0x24   

// Create PCF8575 object
PCF8574 pcf8574_IN(INPUT_I2C_ADDRESS);

void setup() {
  // Initialize I2C communication
  Wire.begin(SDA, SCL);

  // Initialize serial communication
  Serial.begin(115200);

    pcf8574_IN.pinMode(P0, INPUT);
    pcf8574_IN.pinMode(P1, INPUT);
    pcf8574_IN.pinMode(P2, INPUT);
    pcf8574_IN.pinMode(P3, INPUT);
	  pcf8574_IN.pinMode(P4, OUTPUT);
    pcf8574_IN.pinMode(P5, OUTPUT);
    pcf8574_IN.pinMode(P6, OUTPUT);
    pcf8574_IN.pinMode(P7, OUTPUT);

  // Initialize PCF8575
  pcf8574_IN.begin();

  // Turn off all relays first (assuming LOW activates the relay)
  for (int i = 4; i < 8; i++) {
    pcf8574_IN.digitalWrite(i, HIGH);  // Set to HIGH to turn off the relay
  }

  delay(50);
}

void loop() {

  if (pcf8574_IN.digitalRead(0)) pcf8574_IN.digitalWrite(4, HIGH); else pcf8574_IN.digitalWrite(4, LOW);
  delay(50);
  if (pcf8574_IN.digitalRead(1)) pcf8574_IN.digitalWrite(5, HIGH); else pcf8574_IN.digitalWrite(5, LOW);       
  delay(50);
  if (pcf8574_IN.digitalRead(2)) pcf8574_IN.digitalWrite(6, HIGH); else pcf8574_IN.digitalWrite(6, LOW);
  delay(50);
  if (pcf8574_IN.digitalRead(3)) pcf8574_IN.digitalWrite(7, HIGH); else pcf8574_IN.digitalWrite(7, LOW);
  delay(50);
}
