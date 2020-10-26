#include <Arduino.h>
#include "../time/Time.h"

#ifndef PUMP_H
#define PUMP_H

class Pump {
  private:
    int pin;
    bool is_on;
    time_t last_turn_on;

    void setLastTurnOn(time_t);

  public:
    Pump(int pin);
    void turnOn();
    void turnOff();
    bool isOn();
    time_t getLastTurnOn();
    // ~Pump();
};

#endif /* PUMP_H */