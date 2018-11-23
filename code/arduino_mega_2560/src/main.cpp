#include <Arduino.h>
#include <avr/io.h>
#include "PWM.hpp"
#include "Timer.hpp"
#include "MotorCtrl.hpp"

float rad;
float th;

void setup()
{
	rad = 0.0F;
	th = 0.0F;
	Timer::timer_stop();
	PWM::initialize();
	PWM::setDuty(0,0,0);
	Timer::timer_start();
}

void loop()
{
	delay(1);
	rad += 3.6F;
	if ( rad > 360.0F) 
	{
		rad -= 360.0F;
	}
	th = rad * (float)PI / 180.0F;
	MotorCtrl::inversePerk(5.0F, 0.0F, th);
	PWM::setDuty(MotorCtrl::Duty_u, MotorCtrl::Duty_v, MotorCtrl::Duty_w);
	// 
	// if ( d >= PWM::max)
	// 	d = 0;
	// PWM::setDuty(d, d, d);
	// d += 1;
}