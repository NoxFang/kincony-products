/*
 * DS3231 RTC with Arduino
 *
 * This program demonstrates how to use the DS3231 RTC (Real-Time Clock) module with the Arduino.
 * It includes functionality to:
 * - Initialize the DS3231 RTC module
 * - Read the current date and time from the RTC
 * - Set the RTC time based on a serial command:Command format: DYYYY-MM-DDTHH:MM:SS
*    Set date and time command example: D2024-09-19T11:50:22
*    print current date and time command: current time
*
 *
 * Hardware Connections:
 * - SDA: GPIO 8
 * - SCL: GPIO 18
 */

#include <DS3231.h>
#include <Wire.h>

String serial_cmd_rcv = ""; // Serial port receiver

typedef struct
{
  byte year;    // Last two digits of the year, library adds 2000.
  byte month;
  byte day;
  byte hour;
  byte minute;
  byte second;
} MY_DATE_STR;

MY_DATE_STR my_date_str = {0};

// Define constants for relay control
#define OPEN_RLY_DATA    26
#define OPEN_RLY_MONTH   4
#define CLOSE_RLY_DATA   2
#define CLOSE_RLY_MONTH  5

// Define pin connections
#define SDA_PIN   8
#define SCL_PIN   18

DS3231 rtc; // Create an instance of the DS3231 RTC
bool h12Flag;
bool pmFlag;
static bool bCentury = false;
static bool old_level_high = false;
static bool old_level_low = false;


/**
 * @brief Print the current time from the RTC to the Serial Monitor.
 */
static void PrintfCurTime()
{
  Serial.print("Current time is: ");
  int year = rtc.getYear() + 2000;
  Serial.print(year);
  Serial.print("-");

  Serial.print(rtc.getMonth(bCentury), DEC);
  Serial.print("-");

  Serial.print(rtc.getDate(), DEC);
  Serial.print(" ");

  Serial.print(rtc.getHour(h12Flag, pmFlag), DEC);
  Serial.print(":");
  Serial.print(rtc.getMinute(), DEC);
  Serial.print(":");
  Serial.println(rtc.getSecond(), DEC);
}

/**
 * @brief Process serial commands to set the RTC time.
 * Command format: DYYYY-MM-DDTHH:MM:SS
 */
static void GetSerialCmd()
{
  if (Serial.available() > 0)
  {
    delay(100);
    int num_read = Serial.available();
    while (num_read--)
      serial_cmd_rcv += char(Serial.read());
  }
  else return;

  serial_cmd_rcv.trim();

  if (serial_cmd_rcv == "current time")
  {
    PrintfCurTime();
    serial_cmd_rcv = "";
    return;
  }

  Serial.print("Received length: ");
  Serial.println(serial_cmd_rcv.length());

  int indexof_d = serial_cmd_rcv.indexOf('D');
  int indexof_t = serial_cmd_rcv.indexOf('T');

  Serial.print("D index: ");
  Serial.print(indexof_d);
  Serial.print(" T index: ");
  Serial.println(indexof_t);

  if (serial_cmd_rcv.length() != 20 || 
      serial_cmd_rcv.substring(0, 1) != "D" ||
      serial_cmd_rcv.substring(11, 12) != "T")  
  {
    Serial.println(serial_cmd_rcv);
    serial_cmd_rcv = "";
    return;
  }

  Serial.println("Setting time...");

  my_date_str.year = (byte)serial_cmd_rcv.substring(3, 5).toInt();
  my_date_str.month = (byte)serial_cmd_rcv.substring(6, 8).toInt();
  my_date_str.day = (byte)serial_cmd_rcv.substring(9, 11).toInt();
  my_date_str.hour = (byte)serial_cmd_rcv.substring(12, 14).toInt();
  my_date_str.minute = (byte)serial_cmd_rcv.substring(15, 17).toInt();
  my_date_str.second = (byte)serial_cmd_rcv.substring(18).toInt();

  rtc.setYear(my_date_str.year);
  rtc.setMonth(my_date_str.month);
  rtc.setDate(my_date_str.day);
  rtc.setHour(my_date_str.hour);
  rtc.setMinute(my_date_str.minute);
  rtc.setSecond(my_date_str.second);

  serial_cmd_rcv = "";

  Serial.println("Time set.");
}

void setup() {
  // Initialize the I2C interface
  Wire.begin(SDA_PIN, SCL_PIN, 40000);
  
  // Initialize Serial communication
  Serial.begin(115200);
   
  // Set the RTC to 24-hour mode
  rtc.setClockMode(false); // 24-hour format

  // Print current time to Serial Monitor
  PrintfCurTime();

  // Clear any remaining serial data
  while (Serial.read() >= 0) {}
}

void loop() {
  // Process incoming serial commands
  GetSerialCmd(); 
  delay(1000); // Delay for 1 second
}
