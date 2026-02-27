/*
 * ESP32 GPIO State Reader
 * Reads the state of GPIO47, GPIO48, GPIO7, GPIO40, GPIO0, and GPIO5
 * and prints the results to the serial monitor.
 * 
 * Made by KinCony IoT: https://www.kincony.com
 */

#define GPIO_13  13
#define GPIO_40  40
#define GPIO_14  14
#define GPIO_48  48
#define GPIO_0   0
#define GPIO_47  47
#define GPIO_17  17
#define GPIO_21  21


void setup() {
    Serial.begin(115200); // Initialize serial communication at 115200 baud rate
    
    // Set GPIOs as input
    pinMode(GPIO_13, INPUT);
    pinMode(GPIO_40, INPUT);
    pinMode(GPIO_14, INPUT);
    pinMode(GPIO_48, INPUT);
    pinMode(GPIO_0, INPUT);
    pinMode(GPIO_47, INPUT);
    pinMode(GPIO_17, INPUT);
    pinMode(GPIO_21, INPUT);            
}

void loop() {
    // Read GPIO states
    int state_13 = digitalRead(GPIO_13);
    int state_40 = digitalRead(GPIO_40);
    int state_14  = digitalRead(GPIO_14);
    int state_48 = digitalRead(GPIO_48);
    int state_0  = digitalRead(GPIO_0);
    int state_47 = digitalRead(GPIO_47);
    int state_17 = digitalRead(GPIO_17);
    int state_21 = digitalRead(GPIO_21);

    // Print GPIO states to the serial monitor
    Serial.printf("GPIO13: %d, GPIO40: %d, GPIO14: %d, GPIO48: %d, GPIO0: %d, GPIO47: %d, GPIO17: %d, GPIO21: %d\n",
                  state_13, state_40, state_14, state_48, state_0, state_47, state_17, state_21);
    
    delay(1000); // Read GPIO states every second
}
