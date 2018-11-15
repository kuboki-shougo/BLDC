#include "pwm.hpp"

uint8_t timer0::duty;

void timer0::initialize(clk_mode clk)
{
	pinMode(highside_pin, OUTPUT);
	pinMode(lowside_pin, OUTPUT);

	duty = 0;

	timer0::helper::timer_register reg;
	reg.OCR_A = &OCR0A;
	reg.OCR_B = &OCR0B;
	reg.TCCR_A = &TCCR0A;
	reg.TCCR_B = &TCCR0B;
	timer0::helper::initialize(clk, &reg);
}

void timer0::setDuty(uint8_t d)
{
	duty = d;
	OCR0A = duty + u8DeadTime;
	OCR0B = 0xFF - duty - u8DeadTime;
}
