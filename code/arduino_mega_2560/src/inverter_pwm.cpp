#include "inverter_pwm.hpp"

duty_mode inverter_pwm::current_mode;
uint16_t inverter_pwm::duty_u_h;
uint16_t inverter_pwm::duty_v_h;
uint16_t inverter_pwm::duty_w_h;
uint16_t inverter_pwm::duty_u_l;
uint16_t inverter_pwm::duty_v_l;
uint16_t inverter_pwm::duty_w_l;
uint16_t inverter_pwm::deat_time;

void inverter_pwm::initialize(clk_mode clk)
{
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
	OCR1BH = (uint8_t)0xFF;

	// timer 3
	OCR3AH = (uint8_t)0x00;
	OCR3AL = (uint8_t)0x00;
	OCR3BH = (uint8_t)0xFF;
	OCR3BH = (uint8_t)0xFF;

	// timer 4
	OCR4AH = (uint8_t)0x00;
	OCR4AL = (uint8_t)0x00;
	OCR4BH = (uint8_t)0xFF;
	OCR4BH = (uint8_t)0xFF;

	uint8_t c = static_cast<uint8_t>(clk) & (uint8_t)0x07;
	TCCR1B = c;
	TCCR3B = c;
	TCCR4B = c;

	stop();
}

void inverter_pwm::setDuty(duty_mode mode, uint16_t u, uint16_t v, uint16_t w)
{
	switch (mode)
	{
	case duty_mode::Stop:
		stop();
		outputLow();
		current_mode = mode;
		break;

	case duty_mode::Short:
		stop();
		outputShort();
		current_mode = mode;
		break;

	case duty_mode::Normal:
		calcDuty(u, v, w, deat_time);
		OCR1AH = (uint8_t)(duty_u_h >> 8);
		OCR1AL = (uint8_t)duty_u_h;
		OCR1BH = 0xFF - (uint8_t)(duty_u_l >> 8);
		OCR1BL = 0xFF - (uint8_t)duty_u_l;

		OCR3AH = (uint8_t)(duty_v_h >> 8);
		OCR3AL = (uint8_t)duty_v_h;
		OCR3BH = 0xFF - (uint8_t)(duty_v_l >> 8);
		OCR3BL = 0xFF - (uint8_t)duty_v_l;

		OCR4AH = (uint8_t)duty_w_h >> 8;
		OCR4AL = (uint8_t)duty_w_h;
		OCR4BH = 0xFF - (uint8_t)(duty_w_l >> 8);
		OCR4BL = 0xFF - (uint8_t)duty_w_l;
		current_mode = mode;
		break;

	default:
		break;
	}
}

void inverter_pwm::setDeadTime(uint16_t time)
{
	deat_time = time;
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

void inverter_pwm::stop(void)
{
	TCCR1A = _BV(WGM10);
	TCCR3A = _BV(WGM30);
	TCCR4A = _BV(WGM40);
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

void inverter_pwm::calcDuty(uint16_t u, uint16_t v, uint16_t w, uint16_t dead)
{
	// u相
	if (dead > u)
	{
		duty_u_h = MIN_DUTY;
		duty_u_l = MAX_DUTY;
	}
	else if (u > (MAX_DUTY - dead))
	{
		duty_u_h = MAX_DUTY;
		duty_u_l = MIN_DUTY;
	}
	else
	{
		duty_u_h = u - dead;
		duty_u_l = MAX_DUTY - ( u + dead );
	}

	// v相
	if (dead > v)
	{
		duty_v_h = MIN_DUTY;
		duty_v_l = MAX_DUTY;
	}
	else if (v > (MAX_DUTY - dead))
	{
		duty_v_h = MAX_DUTY;
		duty_v_l = MIN_DUTY;
	}
	else
	{
		duty_v_h = v - dead;
		duty_v_l = MAX_DUTY - ( v + dead );
	}

	// w相
	if (dead > w)
	{
		duty_w_h = MIN_DUTY;
		duty_w_l = MAX_DUTY;
	}
	else if (w > (MAX_DUTY - dead))
	{
		duty_w_h = MAX_DUTY;
		duty_w_l = MIN_DUTY;
	}
	else
	{
		duty_w_h = w - dead;
		duty_w_l = MAX_DUTY - ( w + dead );
	}
}
