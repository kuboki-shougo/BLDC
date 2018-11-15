#include "pwm.hpp"

uint16_t timer4::duty;

void timer4::initialize(clk_mode clk)
{
	pinMode(highside_pin, OUTPUT);
	pinMode(lowside_pin, OUTPUT);
	pinMode(8, INPUT);

	duty = 0;

	timer4::helper::timer_register reg;
	reg.OCR_A_H = &OCR4AH;
	reg.OCR_A_L = &OCR4AL;
	reg.OCR_B_H = &OCR4BH;
	reg.OCR_B_L = &OCR4BL;
	reg.TCCR_A = &TCCR4A;
	reg.TCCR_B = &TCCR4B;
	timer4::helper::initialize(clk, &reg);
}

void timer4::setDuty(uint16_t d)
{
	duty = d;
	OCR4AL = duty + u8DeadTime;
	OCR4BL = 0xFF - duty - u8DeadTime;
	OCR4CL = 0;
}
