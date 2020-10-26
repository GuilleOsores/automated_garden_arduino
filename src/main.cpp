#include <Arduino.h>

#include "pump/Pump.h"
#include "time/Time.h"

// moisture sensor
#define MOISTURE_SENSOR A0
#define AIR_MOISTURE 470 // 0%
#define WATER_MOISTURE 160 // 100%
#define HUMIDITY_THRESHOLD 300

// pump
#define PUMP_PIN 4
#define PUMP_SECONDS_UNTIL_TURN_AGAIN 5 * 60
#define PUMP_SECONDS_UNTIL_TURN_OFF 5
// #define PUMP_SECONDS_UNTIL_TURN_AGAIN 15
// #define PUMP_SECONDS_UNTIL_TURN_OFF 5

// global variables
Pump *pump;

int getHumidity() {
  return analogRead(MOISTURE_SENSOR);
}

bool needToTurnOnPump(int soil_moisture) {
  bool turnOn = false;
  if (soil_moisture >= HUMIDITY_THRESHOLD) {
    if (timeDiff(getNow(), pump->getLastTurnOn()) >= PUMP_SECONDS_UNTIL_TURN_AGAIN) {
      turnOn = true;
    }
  }
  return turnOn;
}

bool needToTurnOffPump(int soil_moisture) {
  bool turnOff = false;
  if (soil_moisture < HUMIDITY_THRESHOLD || timeDiff(getNow(), pump->getLastTurnOn()) >= PUMP_SECONDS_UNTIL_TURN_OFF) {
      turnOff = true;
  }
  return turnOff;
}

uint8_t parseHumidityIntoPercent(int soil_moisture) {
  return map(soil_moisture, AIR_MOISTURE, WATER_MOISTURE, 0, 100);
}

void setup() {
  Serial.begin(9600);
  pump = new Pump(PUMP_PIN);
}

void loop() {
  // delay(1000);

  int soil_moisture = getHumidity();
  // Serial.print("soil moisture: ");
  // Serial.println(soil_moisture);
  // int moisture_percent = parseHumidityIntoPercent(soil_moisture);
  // Serial.print("soil moisture: %");
  // Serial.println(moisture_percent);

  if (pump->isOn()) {
    if (needToTurnOffPump(soil_moisture)) {
      pump->turnOff();
      Serial.println("pump off");
    }
  } else {
    if (needToTurnOnPump(soil_moisture)) {
      pump->turnOn();
      Serial.println("pump on");
    }
  }
}
