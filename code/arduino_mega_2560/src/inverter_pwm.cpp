#include "inverter_pwm.hpp"

uint16_t inverter_pwm::max_duty;
uint16_t inverter_pwm::min_duty;
uint16_t inverter_pwm::duty_u;
uint16_t inverter_pwm::duty_v;
uint16_t inverter_pwm::duty_w;
uint16_t inverter_pwm::duty_u_l;
uint16_t inverter_pwm::duty_v_l;
uint16_t inverter_pwm::duty_w_l;
uint16_t inverter_pwm::deat_time;

void inverter_pwm::initialize(clk_mode clk, uint16_t max, uint16_t dead)
{
	max_duty = max;
	min_duty = 0;
	deat_time = dead;

	// pin mode.
	pinMode(HIGH_U_PIN, OUTPUT);
	pinMode(HIGH_V_PIN, OUTPUT);
	pinMode(HIGH_W_PIN, OUTPUT);
	pinMode(LOW_U_PIN, OUTPUT);
	pinMode(LOW_V_PIN, OUTPUT);
	pinMode(LOW_W_PIN, OUTPUT);

	// Phase and Frequency Correct PWM Mode
	stop(stop_mode::Normal);
	uint8_t c = static_cast<uint8_t>(clk) & (uint8_t)0x07;
	TCCR1B = _BV(WGM13) | c;
	TCCR3B = _BV(WGM13) | c;
	TCCR4B = _BV(WGM13) | c;

	// timer 1
	ICR1 = max_duty;
	OCR1A = min_duty;
	OCR1B = max_duty;

	// timer 3
	ICR3 = max_duty;
	OCR3A = min_duty;
	OCR3B = max_duty;

	// timer 4
	ICR4 = max_duty;
	OCR4A = min_duty;
	OCR4B = max_duty;
}

void inverter_pwm::start(void)
{
	// Phase and Frequency Correct PWM Mode
	// A timer = normal
	// B timer = invert
	TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1B0) | _BV(WGM11);
	TCCR3A = _BV(COM3A1) | _BV(COM3B1) | _BV(COM3B0) | _BV(WGM31);
	TCCR4A = _BV(COM4A1) | _BV(COM4B1) | _BV(COM4B0) | _BV(WGM41);
}

void inverter_pwm::stop(stop_mode mode)
{
	// timer停止
	TCCR1A = _BV(WGM11);
	TCCR3A = _BV(WGM31);
	TCCR4A = _BV(WGM41);

	if (mode == stop_mode::Normal)
	{
		outputLow();
	}
	else if (mode == stop_mode::Short)
	{
		outputShort();
	}
}

void inverter_pwm::getDuty(uint16_t *u, uint16_t *v, uint16_t *w)
{
	*u = duty_u;
	*v = duty_v;
	*w = duty_w;
}

void inverter_pwm::setDuty(uint16_t u, uint16_t v, uint16_t w)
{
	// deadtimeを考慮したduty算出
	calcDuty(u, v, w, deat_time);

	// timer1:u相
	OCR1A = duty_u;
	OCR1B = duty_u_l;

	// timer3:v相
	OCR3A = duty_v;
	OCR3B = duty_v_l;

	// timer4:w相
	OCR4A = duty_w;
	OCR4B = duty_w_l;
}

uint16_t inverter_pwm::getDeadTime(void)
{
	return (deat_time);
}

void inverter_pwm::calcDuty(uint16_t u, uint16_t v, uint16_t w, uint16_t dead)
{
	// u相
	if (dead > u)
	{
		duty_u = min_duty;
		duty_u_l = min_duty;
	}
	else if (u > (max_duty - dead))
	{
		duty_u = max_duty;
		duty_u_l = max_duty;
	}
	else
	{
		duty_u = u;
		duty_u_l = u - dead;
	}

	// v相
	if (dead > v)
	{
		duty_v = min_duty;
		duty_v_l = min_duty;
	}
	else if (v > (max_duty - dead))
	{
		duty_v = max_duty;
		duty_v_l = max_duty;
	}
	else
	{
		duty_v = v;
		duty_v_l = v - dead;
	}

	// w相
	if (dead > w)
	{
		duty_w = min_duty;
		duty_w_l = min_duty;
	}
	else if (w > (max_duty - dead))
	{
		duty_w = max_duty;
		duty_w_l = max_duty;
	}
	else
	{
		duty_w = w;
		duty_w_l = w - dead;
	}
}

void inverter_pwm::outputLow(void)
{
	digitalWrite(LOW_U_PIN, LOW);
	digitalWrite(LOW_V_PIN, LOW);
	digitalWrite(LOW_W_PIN, LOW);
	digitalWrite(HIGH_U_PIN, LOW);
	digitalWrite(HIGH_V_PIN, LOW);
	digitalWrite(HIGH_W_PIN, LOW);
}

void inverter_pwm::outputShort(void)
{
	digitalWrite(HIGH_U_PIN, LOW);
	digitalWrite(HIGH_V_PIN, LOW);
	digitalWrite(HIGH_W_PIN, LOW);
	digitalWrite(LOW_U_PIN, HIGH);
	digitalWrite(LOW_V_PIN, HIGH);
	digitalWrite(LOW_W_PIN, HIGH);
}