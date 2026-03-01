/*
 * This Arduino program implements communication between ESP32 and the Tuya module
 * via UART (serial communication). It listens for specific packets from the Tuya module
 * and responds according to the predefined commands.
 * 
 * Functionality:
 * 1. When the ESP32 receives a heartbeat packet (55 AA 00 00 00 00 FF),
 *    it sends a heartbeat response (55 AA 03 00 00 01 00 03).
 * 2. When the ESP32 receives a product information request (55 AA 00 01 00 00 00),
 *    it sends a product information response (55 AA 03 01 ...).
 * 3. When the ESP32 receives a work mode request (55 AA 00 02 00 00 01),
 *    it sends a work mode response (55 AA 03 02 00 03 10 1C 14 47).
 * 4. When the ESP32 receives a network status request (55 AA 00 03 00 01 00 03),
 *    it sends a network status response (55 AA 03 03 00 00 05).
 * 5. Subsequent heartbeat packets (55 AA 00 00 00 00 FF) are responded to with
 *    (55 AA 03 00 00 01 01 04).
 */

#include <HardwareSerial.h>

// Create a HardwareSerial object for UART communication on ESP32
HardwareSerial tuyaSerial(1);

// Define the GPIO pins for TXD and RXD used for serial communication
#define TXD_PIN 15
#define RXD_PIN 16

// Set the baud rate for Tuya module communication to 9600
#define BAUD_RATE 9600

// Define the response packets for different commands from the Tuya module

// Heartbeat response: 55 AA 03 00 00 01 00 03
uint8_t heartBeatResponse[] = {0x55, 0xAA, 0x03, 0x00, 0x00, 0x01, 0x00, 0x03};

// Product info response with a detailed payload (e.g., firmware version, product name, etc.)
uint8_t productInfoResponse[] = {
  0x55, 0xAA, 0x03, 0x01, 0x00, 0x2A, 0x7B, 0x22, 0x70, 0x22, 0x3A, 0x22, 
  0x63, 0x68, 0x6D, 0x7A, 0x6C, 0x67, 0x6A, 0x70, 0x61, 0x64, 0x70, 0x71, 
  0x78, 0x64, 0x6B, 0x6F, 0x22, 0x2C, 0x22, 0x76, 0x22, 0x3A, 0x22, 0x31, 
  0x2E, 0x30, 0x2E, 0x30, 0x22, 0x2C, 0x22, 0x6D, 0x22, 0x3A, 0x30, 0x7D, 0xAA
};

// Work mode response: 55 AA 03 02 00 03 10 1C 14 47
uint8_t workModeResponse[] = {0x55, 0xAA, 0x03, 0x02, 0x00, 0x03, 0x10, 0x1C, 0x14, 0x47};

// Network status response: 55 AA 03 03 00 00 05
uint8_t netStatusResponse[] = {0x55, 0xAA, 0x03, 0x03, 0x00, 0x00, 0x05};

// Subsequent heartbeat response: 55 AA 03 00 00 01 01 04
uint8_t secondHeartBeatResponse[] = {0x55, 0xAA, 0x03, 0x00, 0x00, 0x01, 0x01, 0x04};

void setup() {
  // Initialize the serial communication for debugging at 115200 baud rate
  Serial.begin(115200);

  // Initialize the serial communication with Tuya module at 9600 baud rate
  tuyaSerial.begin(BAUD_RATE, SERIAL_8N1, RXD_PIN, TXD_PIN);

  // Debug message to indicate that the serial communication has been initialized
  Serial.println("ESP32-Tuya serial communication initialized.");
}

void loop() {
  // Check if data is available from the Tuya module
  if (tuyaSerial.available()) {
    uint8_t incomingPacket[7];  // Array to store the received packet
    size_t bytesRead = tuyaSerial.readBytes(incomingPacket, 7); // Read 7 bytes from Tuya

    // Check if the packet has a valid header (0x55, 0xAA)
    if (bytesRead >= 2 && incomingPacket[0] == 0x55 && incomingPacket[1] == 0xAA) {
      // If less than 7 bytes were received, wait for more data
      if (bytesRead < 7) {
        Serial.println("Incomplete packet received. Waiting for remaining bytes...");
        delay(50); // Delay to allow more data to be received
        while (tuyaSerial.available()) {
          incomingPacket[bytesRead++] = tuyaSerial.read(); // Continue reading remaining bytes
          if (bytesRead >= 7) break;
        }
      }

      // If still less than 7 bytes, discard the incomplete packet
      if (bytesRead < 7) {
        Serial.println("Error: Incomplete packet discarded.");
        return;
      }

      // Debug: Print the received packet for logging
      Serial.print("Received packet: ");
      for (size_t i = 0; i < 7; i++) {
        Serial.print(incomingPacket[i], HEX);
        Serial.print(" ");
      }
      Serial.println();

      // Call the function to process the received packet
      processTuyaPacket(incomingPacket, 7);

    } else {
      // If the header is invalid, discard the packet and flush the buffer
      Serial.print("Error: Invalid packet header. Data received: ");
      for (size_t i = 0; i < bytesRead; i++) {
        Serial.print(incomingPacket[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
      tuyaSerial.flush(); // Clear the serial buffer
    }
  }

  // Delay to avoid CPU overuse
  delay(100);
}

// Function to process the received packet and send the appropriate response
void processTuyaPacket(uint8_t* packet, size_t size) {
  // Ensure the packet size is 7 and the header is valid
  if (size == 7 && packet[0] == 0x55 && packet[1] == 0xAA) {
    // Determine the command in the packet (packet[2])
    switch(packet[2]) {
      case 0x00:
        if (packet[3] == 0x00 && packet[4] == 0x00 && packet[5] == 0x00 && packet[6] == 0xFF) {
          Serial.println("Heartbeat received.");
          sendPacket(heartBeatResponse, sizeof(heartBeatResponse));
        } else if (packet[3] == 0x01 && packet[4] == 0x00 && packet[5] == 0x00 && packet[6] == 0x00) {
          Serial.println("Product info request received.");
          sendPacket(productInfoResponse, sizeof(productInfoResponse));
        } else if (packet[3] == 0x02 && packet[4] == 0x00 && packet[5] == 0x00 && packet[6] == 0x01) {
          Serial.println("Work mode request received.");
          sendPacket(workModeResponse, sizeof(workModeResponse));
        } else if (packet[3] == 0x03 && packet[4] == 0x00 && packet[5] == 0x01 && packet[6] == 0x00) {
          Serial.println("Network status request received.");
          sendPacket(netStatusResponse, sizeof(netStatusResponse));
        }
        break;

      default:
        Serial.println("Error: Unhandled command received.");
        break;
    }
  }
}

// Function to send the response packet to the Tuya module
void sendPacket(uint8_t* packet, size_t size) {
  // Send the packet via UART to Tuya module
  tuyaSerial.write(packet, size);

  // Debug: Print the sent packet for logging
  Serial.print("Sent packet: ");
  for (size_t i = 0; i < size; i++) {
    Serial.print(packet[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}
