#include <Arduino.h>
#include <avr/io.h>
#include "pwm.hpp"
#include "timer.hpp"

uint16_t d;

void setup()
{
	d = 0;
	timer::timer_stop();
	pwm::initialize();
	pwm::setDuty(d,d,d);
	timer::timer_start();
}

void loop()
{
	delay(10);
	if ( d >= pwm::max)
		d = 0;
	pwm::setDuty(d, d, d);
	d += 1;
}