/*
 * This program reads voltage values from the ADS1115 analog-to-digital converter
 * on all four channels (A0, A1, A2, A3) and prints the results through the serial port.
 * The ADS1115 communicates via the I2C protocol. This version of the code includes 
 * the capability to specify custom SDA and SCL pins for I2C communication.
 *
 */

#include <Wire.h>                // Library for I2C communication
#include <DFRobot_ADS1115.h>     // Library for ADS1115 ADC module

// Define the I2C SDA and SCL pins for communication with ADS1115
#define SDA_PIN 8  
#define SCL_PIN 18  

// Initialize ADS1115 instance using the Wire library
DFRobot_ADS1115 ads(&Wire);

void setup(void) 
{
    // Begin serial communication at a baud rate of 115200
    Serial.begin(115200);

    // Initialize the I2C bus using the defined SDA and SCL pins
    Wire.begin(SDA_PIN, SCL_PIN);

    // Set the I2C address for the ADS1115 (default: 0x49)
    ads.setAddr_ADS1115(ADS1115_IIC_ADDRESS0);   // Address is 0x49

    // Set the gain for the ADS1115 (2/3x gain allows for a maximum input voltage of 6.144V)
    ads.setGain(eGAIN_TWOTHIRDS);

    // Set the ADS1115 to operate in single-shot mode (each reading is a single conversion)
    ads.setMode(eMODE_SINGLE);

    // Set the sample rate to 128 samples per second (SPS)
    ads.setRate(eRATE_128);

    // Set the operational status mode to single-conversion start
    ads.setOSMode(eOSMODE_SINGLE);

    // Initialize the ADS1115 module
    ads.init();
}

void loop(void) 
{
    // Check if the ADS1115 is properly connected and functioning
    if (ads.checkADS1115())
    {
        // Variables to store the voltage readings for each channel
        int16_t adc0, adc1, adc2, adc3;

        // Read the voltage from channel A0 and print the value
        adc0 = ads.readVoltage(0);
        Serial.print("A0:");
        Serial.print(adc0);
        Serial.print("mV,  ");    // Print the value in millivolts

        // Read the voltage from channel A1 and print the value
        adc1 = ads.readVoltage(1);
        Serial.print("A1:");
        Serial.print(adc1);
        Serial.print("mV,  ");    // Print the value in millivolts

        // Read the voltage from channel A2 and print the value
        adc2 = ads.readVoltage(2);
        Serial.print("A2:");
        Serial.print(adc2);
        Serial.print("mV,  ");    // Print the value in millivolts

        // Read the voltage from channel A3 and print the value
        adc3 = ads.readVoltage(3);
        Serial.print("A3:");
        Serial.print(adc3);
        Serial.println("mV");     // Print the value in millivolts and end the line
    }
    else
    {
        // If ADS1115 is not connected, print a message indicating disconnection
        Serial.println("ADS1115 Disconnected!");
    }

    // Wait for 1 second before the next loop iteration
    delay(1000);
}
