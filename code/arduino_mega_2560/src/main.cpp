#include <Arduino.h>
#include <avr/io.h>
#include "pwm.hpp"
#include "timer.hpp"
#include "duty.hpp"

uint16_t d;

void setup()
{
	d = 0;;
	timer::timer_stop();
	pwm::initialize();
	pwm::setDuty(d,d,d);
	timer::timer_start();
}

void loop()
{
	int vdc = analogRead(0);
	float ad = 5.0f * ( (float)vdc / 1024.0f );
	d = duty::calcDuty(1.0, ad);
	pwm::setDuty(d,d,d);
	// delay(10);
	// if ( d >= pwm::max)
	// 	d = 0;
	// pwm::setDuty(d, d, d);
	// d += 1;
}