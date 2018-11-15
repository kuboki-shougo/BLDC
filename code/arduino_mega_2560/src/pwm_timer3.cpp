#include "pwm.hpp"

uint16_t timer3::duty;

void timer3::initialize(clk_mode clk)
{
	pinMode(highside_pin, OUTPUT);
	pinMode(lowside_pin, OUTPUT);
	pinMode(3, INPUT);

	duty = 0;

	timer3::helper::timer_register reg;
	reg.OCR_A_H = &OCR3AH;
	reg.OCR_A_L = &OCR3AL;
	reg.OCR_B_H = &OCR3BH;
	reg.OCR_B_L = &OCR3BL;
	reg.TCCR_A = &TCCR3A;
	reg.TCCR_B = &TCCR3B;
	timer3::helper::initialize(clk, &reg);
}

void timer3::setDuty(uint16_t d)
{
	duty = d;
	OCR3AL = duty + u8DeadTime;
	OCR3BL = 0xFF - duty - u8DeadTime;
	OCR3CL = 0;
}
