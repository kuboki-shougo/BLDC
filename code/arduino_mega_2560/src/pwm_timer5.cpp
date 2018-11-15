#include "pwm.hpp"

uint16_t timer5::duty;

void timer5::initialize(clk_mode clk)
{
	pinMode(highside_pin, OUTPUT);
	pinMode(lowside_pin, OUTPUT);
	pinMode(44, INPUT);

	duty = 0;

	timer5::helper::timer_register reg;
	reg.OCR_A_H = &OCR5AH;
	reg.OCR_A_L = &OCR5AL;
	reg.OCR_B_H = &OCR5BH;
	reg.OCR_B_L = &OCR5BL;
	reg.TCCR_A = &TCCR5A;
	reg.TCCR_B = &TCCR5B;
	timer5::helper::initialize(clk, &reg);
}

void timer5::setDuty(uint16_t d)
{
	duty = d;
	OCR5AL = duty + u8DeadTime;
	OCR5BL = 0xFF - duty - u8DeadTime;
	OCR5CL = 0;
}
