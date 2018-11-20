#include <Arduino.h>
#include <avr/io.h>
#include "inverter_pwm.hpp"

uint16_t d;

void setup()
{
	d = 0;
	inverter_pwm::initialize(clk_mode::Prescaling_8, (uint16_t)1000, 3);
	inverter_pwm::setDuty(d, d, d);
	inverter_pwm::start();
}

void loop()
{
	// delay(2);
	// if ( d >= 1000)
	// 	d = 0;
	// inverter_pwm::setDuty(d, d, d);
	// d += 1;
}