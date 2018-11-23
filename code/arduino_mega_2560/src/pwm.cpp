#include "PWM.hpp"

uint16_t PWM::duty_u;
uint16_t PWM::duty_v;
uint16_t PWM::duty_w;
uint16_t PWM::duty_u_l;
uint16_t PWM::duty_v_l;
uint16_t PWM::duty_w_l;
uint16_t PWM::duty_u_n1;
uint16_t PWM::duty_v_n1;
uint16_t PWM::duty_w_n1;

void PWM::initialize(void)
{
	Timer::initialize_Timer1(PWM::clk, PWM::max);
	Timer::initialize_Timer3(PWM::clk, PWM::max);
	Timer::initialize_Timer4(PWM::clk, PWM::max);
}

void PWM::getDuty(uint16_t *u, uint16_t *v, uint16_t *w)
{
	*u = duty_u;
	*v = duty_v;
	*w = duty_w;
}

void PWM::setDuty(uint16_t u, uint16_t v, uint16_t w)
{
	duty_u_n1 = duty_u;
	duty_v_n1 = duty_v;
	duty_w_n1 = duty_w;

	// deadtimeを考慮したduty算出
	calcDuty(u, &duty_u, &duty_u_l);
	calcDuty(v, &duty_v, &duty_v_l);
	calcDuty(w, &duty_w, &duty_w_l);

	// 縦短絡防止
	// Timer1:u相
	if (duty_u > duty_u_n1)
	{
		OCR1B = duty_u_l;
		OCR1A = duty_u;
	}
	else
	{
		OCR1A = duty_u;
		OCR1B = duty_u_l;
	}

	// Timer3:v相
	if (duty_v > duty_v_n1)
	{
		OCR3B = duty_v_l;
		OCR3A = duty_v;
	}
	else
	{
		OCR3A = duty_v;
		OCR3B = duty_v_l;
	}

	// Timer4:w相
	if (duty_w > duty_w_n1)
	{
		OCR4B = duty_w_l;
		OCR4A = duty_w;
	}
	else
	{
		OCR4A = duty_w;
		OCR4B = duty_w_l;
	}
}

void PWM::calcDuty(uint16_t duty, uint16_t *high, uint16_t *low)
{
	if (duty <= dead_time)
	{
		*high = 0;
		*low = 0;
	}
	else if (duty >= (PWM::max - dead_time))
	{
		*high = PWM::max;
		*low = PWM::max;
	}
	else
	{
		*high = duty;
		*low = duty + dead_time;
	}
}
