#include "inverter_pwm.hpp"

uint16_t inverter_pwm::duty_u;
uint16_t inverter_pwm::duty_v;
uint16_t inverter_pwm::duty_w;
uint16_t inverter_pwm::duty_u_l;
uint16_t inverter_pwm::duty_v_l;
uint16_t inverter_pwm::duty_w_l;
uint16_t inverter_pwm::deat_time;

void inverter_pwm::initialize(clk_mode clk, uint16_t dead)
{
	deat_time = dead;

	pinMode(HIGH_U_PIN, OUTPUT);
	pinMode(HIGH_V_PIN, OUTPUT);
	pinMode(HIGH_W_PIN, OUTPUT);

	pinMode(LOW_U_PIN, OUTPUT);
	pinMode(LOW_V_PIN, OUTPUT);
	pinMode(LOW_W_PIN, OUTPUT);

	// timer 1
	OCR1AH = (uint8_t)0x00;
	OCR1AL = (uint8_t)0x00;
	OCR1BH = (uint8_t)0xFF;
	OCR1BL = (uint8_t)0xFF;

	// timer 3
	OCR3AH = (uint8_t)0x00;
	OCR3AL = (uint8_t)0x00;
	OCR3BH = (uint8_t)0xFF;
	OCR3BL = (uint8_t)0xFF;

	// timer 4
	OCR4AH = (uint8_t)0x00;
	OCR4AL = (uint8_t)0x00;
	OCR4BH = (uint8_t)0xFF;
	OCR4BL = (uint8_t)0xFF;

	stop(stop_mode::Normal);

	uint8_t c = static_cast<uint8_t>(clk) & (uint8_t)0x07;
	TCCR1B = c;
	TCCR3B = c;
	TCCR4B = c;
}

void inverter_pwm::start(void)
{
	// Phase Correct PWM Mode
	// A timer = normal
	// B timer = invert
	TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1B0) | _BV(WGM10);
	TCCR3A = _BV(COM3A1) | _BV(COM3B1) | _BV(COM3B0) | _BV(WGM30);
	TCCR4A = _BV(COM4A1) | _BV(COM4B1) | _BV(COM4B0) | _BV(WGM40);
}

void inverter_pwm::stop(stop_mode mode)
{
	// timer停止
	TCCR1A = _BV(WGM10);
	TCCR3A = _BV(WGM30);
	TCCR4A = _BV(WGM40);

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
	OCR1AH = (uint8_t)(duty_u >> 8);
	OCR1AL = (uint8_t)duty_u;
	OCR1BH = (uint8_t)(duty_u_l >> 8);
	OCR1BL = (uint8_t)duty_u_l;

	// timer3:v相
	OCR3AH = (uint8_t)(duty_v >> 8);
	OCR3AL = (uint8_t)duty_v;
	OCR3BH = (uint8_t)(duty_v_l >> 8);
	OCR3BL = (uint8_t)duty_v_l;

	// timer4:w相
	OCR4AH = (uint8_t)(duty_w >> 8);
	OCR4AL = (uint8_t)duty_w;
	OCR4BH = (uint8_t)(duty_w_l >> 8);
	OCR4BL = (uint8_t)duty_w_l;
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
		duty_u = MIN_DUTY;
		duty_u_l = MIN_DUTY;
	}
	else if (u > (MAX_DUTY - dead))
	{
		duty_u = MAX_DUTY;
		duty_u_l = MAX_DUTY;
	}
	else
	{
		duty_u = u;
		duty_u_l = u - dead;
	}

	// v相
	if (dead > v)
	{
		duty_v = MIN_DUTY;
		duty_v_l = MIN_DUTY;
	}
	else if (v > (MAX_DUTY - dead))
	{
		duty_v = MAX_DUTY;
		duty_v_l = MAX_DUTY;
	}
	else
	{
		duty_v = v;
		duty_v_l = v - dead;
	}

	// w相
	if (dead > w)
	{
		duty_w = MIN_DUTY;
		duty_w_l = MIN_DUTY;
	}
	else if (w > (MAX_DUTY - dead))
	{
		duty_w = MAX_DUTY;
		duty_w_l = MAX_DUTY;
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