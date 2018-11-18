#include <Arduino.h>
#include <avr/io.h>
#include "inverter_pwm.hpp"

uint8_t d;

void setup()
{
	d = 255;

	// deadtime = 128us
	inverter_pwm::initialize(clk_mode::Prescaling_1024, 1);
	inverter_pwm::setDuty(d, d, d);
	inverter_pwm::start();
}

void loop()
{
	delay(100);
	//inverter_pwm::setDuty(d, d, d);
	//d++;
}