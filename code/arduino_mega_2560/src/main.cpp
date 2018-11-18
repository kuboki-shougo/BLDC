#include <Arduino.h>
#include <avr/io.h>
#include "configuration.h"
#include "inverter_pwm.hpp"

uint8_t d;

void setup()
{
	inverter_pwm::initialize(clk_mode::Prescaling_256);
	inverter_pwm::setDeadTime(5);
	inverter_pwm::start();

	//inverter_pwm::setDuty(duty_mode::Normal, 100, 150, 200);

	//timer0::initialize(clk_mode::Prescaling_1024);
	//timer0::setDuty(150);

	// timer1::initialize(clk_mode::Prescaling_1024);
	// timer1::setDuty(0);

	// timer3::initialize(clk_mode::Prescaling_1024);
	// timer3::setDuty(60);

	// timer4::initialize(clk_mode::Prescaling_1024);
	// timer4::setDuty(90);

	// timer5::initialize(clk_mode::Prescaling_1024);
	// timer5::setDuty(120);

	//pinMode(13, INPUT); // OCR0B pin5
	//pinMode(4, OUTPUT); // OCR0A pin6
	d = 0;
}

void loop()
{
	delay(100);
	inverter_pwm::setDuty(duty_mode::Normal, d, d, d);
	d++;
}