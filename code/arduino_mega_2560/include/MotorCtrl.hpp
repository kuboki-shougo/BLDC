#ifndef MOTORCTRL_HPP
#define MOTORCTRL_HPP

#include <Arduino.h>
#include <math.h>
#include "Base.hpp"
#include "PWM.hpp"

class MotorCtrl : Base
{
  public:
	static float Ia;
	static float Ib;
	static float Id;
	static float Iq;

	static float Vq;
	static float Vd;
	static float Vu;
	static float Vv;
	static float Vw;
	static uint16_t Duty_u;
	static uint16_t Duty_v;
	static uint16_t Duty_w;
	static constexpr float pi23 = (float)(2.0 * PI / 3.0);

	static void Clark(float Iu, float Iv, float Iw)
	{
		Ia = Iu;
		Ib = (Iu + (2.0 * Iv)) / sqrt(3.0);	
	}

	static void Perk(float Ia, float Ib, float th)
	{
		Id = (Ia * cos(th)) + (Ib * sin(th));
		Iq = (-Ia * sin(th)) + (Ib * cos(th));
	}

	static void ClarkPerk(float Iu, float Iv, float Iw, float th)
	{
		float s = sqrt(2.0 / 3.0);
		Id = s * (cos(th) * Iu) + (cos(th - MotorCtrl::pi23) * Iv) + (cos(th + MotorCtrl::pi23) * Iw);
		Iq = s * (-1.0 * sin(th) * Iu) + (-1.0 * sin(th - MotorCtrl::pi23) * Iv) + (-1.0 * sin(th + MotorCtrl::pi23) * Iw);
	}

	static void InversePerk(float vq, float vd, float th)
	{
		float s = sqrt(2.0 / 3.0);
		Vu = s * (cos(th) * vd) + (-1.0 * sin(th) * vq);
		Vv = s * (cos(th - MotorCtrl::pi23) * vd) + (-1.0 * sin(th - MotorCtrl::pi23) * vq);
		Vw = s * (cos(th + MotorCtrl::pi23) * vd) + (-1.0 * sin(th + MotorCtrl::pi23) * vq);

		Duty_u = calcDuty(Vu, 5.0F);
		Duty_v = calcDuty(Vv, 5.0F);
		Duty_w = calcDuty(Vw, 5.0F);
	}

	// FPUを積んでないのでこの処理は暫定です。
	// 固定小数点で実装しなおす。
	static uint16_t calcDuty(float voltage, float vdc)
	{
		uint16_t duty;
		if (voltage >= vdc)
		{
			duty = PWM::max;
		}
		else if (voltage < 0.0)
		{
			duty = 0;
		}
		else
		{
			float ratio = voltage / vdc;
			duty = (uint16_t)((float)PWM::max * ratio);
		}
		return (duty);
	}
};
#endif
