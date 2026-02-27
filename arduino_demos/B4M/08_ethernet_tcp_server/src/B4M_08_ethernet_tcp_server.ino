/*
 * This Arduino program sets up an ESP32-S3 with a W5500 Ethernet module
 * as a TCP server. It listens on port 4196 and echoes back any string 
 * received from a client.
 *
 * Hardware connections:
 * - CLK: GPIO42
 * - MOSI: GPIO43
 * - MISO: GPIO44
 * - CS: GPIO41
 * - RST: GPIO1
 * - INT: GPIO2
 *
 * Static IP address: 192.168.3.55
 * Subnet Mask: 255.255.255.0
 * Gateway: 192.168.3.1
 * DNS: 192.168.3.1
 */

#include <SPI.h>
#include <Ethernet.h>

// Define the W5500 Ethernet module pins
#define W5500_CS_PIN  42
#define W5500_RST_PIN 44
#define W5500_INT_PIN 43
#define W5500_CLK_PIN 1
#define W5500_MOSI_PIN 2
#define W5500_MISO_PIN 41

// MAC address for your Ethernet shield (must be unique on your network)
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Static IP address configuration
IPAddress ip(192, 168, 3, 55);       // Static IP address
IPAddress subnet(255, 255, 255, 0);   // Subnet mask
IPAddress gateway(192, 168, 3, 1);    // Default gateway
IPAddress dns(192, 168, 3, 1);        // DNS server address

// Create an EthernetServer object to handle TCP connections
EthernetServer server(4196);

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for serial port to connect
  }

  // Initialize the W5500 module
  pinMode(W5500_RST_PIN, OUTPUT);
  pinMode(W5500_INT_PIN, INPUT);
  digitalWrite(W5500_RST_PIN, LOW);  // Reset the W5500 module
  delay(100);                       // Wait for reset to complete
  digitalWrite(W5500_RST_PIN, HIGH); // Release reset

  // Initialize SPI with the correct pin definitions
  SPI.begin(W5500_CLK_PIN, W5500_MISO_PIN, W5500_MOSI_PIN);

  // Set up the Ethernet library with W5500-specific pins
  Ethernet.init(W5500_CS_PIN);

  // Start the Ethernet connection with static IP configuration
  Ethernet.begin(mac, ip, dns, gateway, subnet);

  // Print the IP address to the serial monitor
  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());

  // Start listening for incoming TCP connections
  server.begin();
}

void loop() {
  // Check for incoming client connections
  EthernetClient client = server.available();
  if (client) {
    Serial.println("New client connected");

    // Read data from the client and echo it back
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        server.write(c);
      }
    }

    // Close the connection when done
    client.stop();
    Serial.println("Client disconnected");
  }
}
