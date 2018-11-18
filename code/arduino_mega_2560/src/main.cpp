#include <Arduino.h>
#include <avr/io.h>
#include "inverter_pwm.hpp"

uint8_t d;

void setup()
{
	inverter_pwm::initialize(clk_mode::Prescaling_256, 5);
	inverter_pwm::start();
	d = 0;
}

void loop()
{
	delay(100);
	inverter_pwm::setDuty(d, d, d);
	d++;
}