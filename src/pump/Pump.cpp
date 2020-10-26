#include "Pump.h"

Pump::Pump(int pin)
{
  this->pin = pin;
  this->is_on = false;
  setLastTurnOn(getNow());

  pinMode(pin, OUTPUT);
}

void Pump::turnOn()
{
  digitalWrite(pin, HIGH);
  is_on = true;
  setLastTurnOn(getNow());
}

void Pump::turnOff()
{
  digitalWrite(pin, LOW);
  this->is_on = false;
}

bool Pump::isOn()
{
  return this->is_on;
}

void Pump::setLastTurnOn(time_t time)
{
  this->last_turn_on = time;
}

time_t Pump::getLastTurnOn()
{
  return this->last_turn_on;
}
