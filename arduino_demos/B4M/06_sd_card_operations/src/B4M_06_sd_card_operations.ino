/*
 * SD Card File Operations
 *
 * This program demonstrates basic file operations on an SD card using the ESP32.
 * It includes functionality to:
 * - Initialize and test the SD card
 * - Read from, write to, append to, and delete files on the SD card
 * - Measure file read and write performance
 *
 * Hardware Connections:
 * - SCK: GPIO 11
 * - MISO: GPIO 12
 * - MOSI: GPIO 10
 * - CS: GPIO 9
 */

#include "FS.h"
#include "SD.h"
#include "SPI.h"

// Pin definitions for SD card
#define SCK  11
#define MISO 12
#define MOSI 10
#define CS   9

/**
 * @brief Reads the contents of a file from the SD card and prints it to the serial monitor.
 * 
 * @param fs File system to use (in this case, SD).
 * @param path Path of the file to read.
 */
void readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available()) {
    Serial.print((char)file.read());
  }
  file.close();
}

/**
 * @brief Writes a message to a file on the SD card.
 * 
 * @param fs File system to use (in this case, SD).
 * @param path Path of the file to write.
 * @param message Message to write to the file.
 */
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

/**
 * @brief Appends a message to a file on the SD card.
 * 
 * @param fs File system to use (in this case, SD).
 * @param path Path of the file to append.
 * @param message Message to append to the file.
 */
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}

/**
 * @brief Deletes a file from the SD card.
 * 
 * @param fs File system to use (in this case, SD).
 * @param path Path of the file to delete.
 */
void deleteFile(fs::FS &fs, const char * path) {
  Serial.printf("Deleting file: %s\n", path);
  if (fs.remove(path)) {
    Serial.println("File deleted");
  } else {
    Serial.println("Delete failed");
  }
}

/**
 * @brief Tests file read and write performance.
 * 
 * @param fs File system to use (in this case, SD).
 * @param path Path of the file to test.
 */
void testFileIO(fs::FS &fs, const char * path) {
  File file = fs.open(path);
  static uint8_t buf[512];
  size_t len = 0;
  uint32_t start = millis();
  uint32_t end = start;

  if (file) {
    len = file.size();
    size_t flen = len;
    start = millis();
    while (len) {
      size_t toRead = len;
      if (toRead > 512) {
        toRead = 512;
      }
      file.read(buf, toRead);
      len -= toRead;
    }
    end = millis() - start;
    Serial.printf("%u bytes read for %u ms\n", flen, end);
    file.close();
  } else {
    Serial.println("Failed to open file for reading");
  }

  file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  size_t i;
  start = millis();
  for (i = 0; i < 2048; i++) {
    file.write(buf, 512);
  }
  end = millis() - start;
  Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
  file.close();
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);
  
  // Initialize SPI and SD card
  SPIClass spi = SPIClass(HSPI);
  spi.begin(SCK, MISO, MOSI, CS);

  if (!SD.begin(CS, spi, 80000000)) {
    Serial.println("Card Mount Failed");
    return;
  }

  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  delay(2000);

  // Perform file operations
  deleteFile(SD, "/hello.txt");
  writeFile(SD, "/hello.txt", "Hello ");
  appendFile(SD, "/hello.txt", "World!\n");
  readFile(SD, "/hello.txt");
  testFileIO(SD, "/test.txt");
  Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
  Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}

void loop() {
  // No operation in loop
}