#ifndef DUTY_HPP
#define DUTY_HPP

#include <Arduino.h>
#include "base.hpp"
#include "pwm.hpp"

class duty : base
{
  public:
	// FPUを積んでないのでこの処理は暫定です。
	// 固定小数点で実装しなおす。
	static uint16_t calcDuty(float voltage, float vdc)
	{
		uint16_t duty;
		if (voltage >= vdc)
		{
			duty = pwm::max;
		}
		else if (voltage < 0.0)
		{
			duty = 0;
		}
		else
		{
			float ratio = voltage / vdc;
			duty = (uint16_t)((float)pwm::max * ratio);
		}
		return (duty);
	}
};
#endif
