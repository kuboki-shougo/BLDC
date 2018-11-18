#include "pwm.hpp"

uint16_t timer1::duty;

void timer1::initialize(clk_mode clk)
{
	pinMode(highside_pin, OUTPUT);
	pinMode(lowside_pin, OUTPUT);
	pinMode(13, INPUT);

	duty = 0;

	timer1::helper::timer_register reg;
	reg.OCR_A_H = &OCR1AH;
	reg.OCR_A_L = &OCR1AL;
	reg.OCR_B_H = &OCR1BH;
	reg.OCR_B_L = &OCR1BL;
	reg.TCCR_A = &TCCR1A;
	reg.TCCR_B = &TCCR1B;
	timer1::helper::initialize(clk, &reg);
}

void timer1::setDuty(uint16_t d)
{
	duty = d;
	OCR1AL = duty;
	OCR1BL = 0xFF - duty - u8DeadTime;
	OCR1CL = 0;
}
