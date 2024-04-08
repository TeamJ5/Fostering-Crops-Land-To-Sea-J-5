#include "RTClib.h"


#include <Adafruit_BusIO_Register.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_I2CRegister.h>
#include <Adafruit_I2CDevice.h>
 // Include RTC library
#include <Wire.h>   // Include I2C Communication library

// Define constants
#define relayPin 8        // Digital pin connected to the relay control side
#define valveOpenTime 60000 // Time in milliseconds (1 hour) for valve activation

// Define watering times (replace with desired hours and minutes)
const int wateringHour1 = 8;   // Hour for 1st watering
const int wateringMinute1 = 0;  // Minute for 1st watering
const int wateringHour2 = 12;  // Hour for 2nd watering (noon)
const int wateringMinute2 = 0;  // Minute for 2nd watering
const int wateringHour3 = 18;  // Hour for 3rd watering
const int wateringMinute3 = 0;  // Minute for 3rd watering

// RTC module address (check datasheet if different)
const int RTC_ADDR = 0x68;

// Create an RTC object
RTC_DS1307 clock;

void setup() {
  pinMode(relayPin, OUTPUT);      // Set relay control pin as output
  Wire.begin();                  // Initialize I2C communication
  // Check for successful RTC initialization (optional)
  if (!clock.begin(RTC_ADDR)) {
    Serial.println("RTC initialization failed!");
    while (1); // Halt if RTC initialization fails (optional)
  }
  // Optional: Set initial time on RTC using clock.adjust(dateTime);
  Serial.begin(9600);             // Initialize serial communication for debugging (optional)
}

void loop() {
  DateTime now = clock.now(); // Get current time from RTC

  // Check for each watering time throughout the day
  if (now.hour() == wateringHour1 && now.minute() == wateringMinute1) {
    activateValve();
    Serial.println("Watering activated at 8:00 AM"); // Optional debug message
  } else if (now.hour() == wateringHour2 && now.minute() == wateringMinute2) {
    activateValve();
    Serial.println("Watering activated at 12:00 PM"); // Optional debug message
  } else if (now.hour() == wateringHour3 && now.minute() == wateringMinute3) {
    activateValve();
    Serial.println("Watering activated at 6:00 PM"); // Optional debug message
  }
}

void activateValve() {
  digitalWrite(relayPin, HIGH); // Activate relay, opening the valve
  delay(valveOpenTime);        // Wait for the set watering duration
  digitalWrite(relayPin, LOW);  // Deactivate relay, closing the valve
}
