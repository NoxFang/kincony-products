/*
 * RS485 Communication Test
 *
 * This program is a simple test for RS485 communication using ESP32-S3.
 * It will send a message over RS485 and then read incoming messages.
 * The TXD pin is defined as GPIO 18 and RXD pin is defined as GPIO 8.
 *
 */

#include <HardwareSerial.h>

// Define RS485 pins
#define RS485_RXD 39
#define RS485_TXD 38

// Create a hardware serial object
HardwareSerial rs485Serial(1);

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  while (!Serial);

  // Initialize RS485 Serial communication
  rs485Serial.begin(9600, SERIAL_8N1, RS485_RXD, RS485_TXD);
  
  Serial.println("RS485 Test Start");
}

void loop() {
  // Send a test message
  rs485Serial.println("Hello from B4M Controller!");

  // Wait for a short period
  delay(1000);

  // Check if data is available to read
  if (rs485Serial.available()) {
    String receivedMessage = "";
    while (rs485Serial.available()) {
      char c = rs485Serial.read();
      receivedMessage += c;
    }
    // Print the received message
    Serial.print("Received: ");
    Serial.println(receivedMessage);
  }

  // Wait before sending the next message
  delay(2000);
}
