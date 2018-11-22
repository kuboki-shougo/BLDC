#include "pwm.hpp"

uint16_t pwm::duty_u;
uint16_t pwm::duty_v;
uint16_t pwm::duty_w;
uint16_t pwm::duty_u_l;
uint16_t pwm::duty_v_l;
uint16_t pwm::duty_w_l;
uint16_t pwm::duty_u_n1;
uint16_t pwm::duty_v_n1;
uint16_t pwm::duty_w_n1;

void pwm::initialize(void)
{
	timer::initialize_timer1(pwm::clk, pwm::max);
	timer::initialize_timer3(pwm::clk, pwm::max);
	timer::initialize_timer4(pwm::clk, pwm::max);
}

void pwm::getDuty(uint16_t *u, uint16_t *v, uint16_t *w)
{
	*u = duty_u;
	*v = duty_v;
	*w = duty_w;
}

void pwm::setDuty(uint16_t u, uint16_t v, uint16_t w)
{
	duty_u_n1 = duty_u;
	duty_v_n1 = duty_v;
	duty_w_n1 = duty_w;

	// deadtimeを考慮したduty算出
	calcDuty(u, &duty_u, &duty_u_l);
	calcDuty(v, &duty_v, &duty_v_l);
	calcDuty(w, &duty_w, &duty_w_l);

	// 縦短絡防止
	// timer1:u相
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

	// timer3:v相
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

	// timer4:w相
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

void pwm::calcDuty(uint16_t duty, uint16_t *high, uint16_t *low)
{
	if (duty <= dead_time)
	{
		*high = 0;
		*low = 0;
	}
	else if (duty >= (pwm::max - dead_time))
	{
		*high = pwm::max;
		*low = pwm::max;
	}
	else
	{
		*high = duty;
		*low = duty + dead_time;
	}
}
