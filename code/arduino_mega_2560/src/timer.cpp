#include "Timer.hpp"

void Timer::initialize_Timer0(CLK_MODE clk, uint16_t max)
{

}

/// phase and freq correct  
/// A = normal
/// B = inverter
/// C = stop
void Timer::initialize_Timer1(CLK_MODE clk, uint16_t max)
{
	pinMode(Timer::TIMER1A_PIN, OUTPUT);
	pinMode(Timer::TIMER1B_PIN, OUTPUT);
	pinMode(Timer::TIMER1C_PIN, INPUT);

	uint8_t c = static_cast<uint8_t>(clk) & (uint8_t)0x07;
    TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1B0) | _BV(WGM11);
	TCCR1B = _BV(WGM13) | c;
	
    ICR1 = max;
    TCNT1 = 0;
    TIMSK1 = 0;
    TIFR1 = 0;
    OCR1A = 0;
    OCR1B = max;
}

/// phase and freq correct  
/// A = normal
/// B = inverter
/// C = stop
void Timer::initialize_Timer3(CLK_MODE clk, uint16_t max)
{
	pinMode(Timer::TIMER3A_PIN, OUTPUT);
	pinMode(Timer::TIMER3B_PIN, OUTPUT);
	pinMode(Timer::TIMER3C_PIN, INPUT);

	uint8_t c = static_cast<uint8_t>(clk) & (uint8_t)0x07;
    TCCR3A = _BV(COM3A1) | _BV(COM3B1) | _BV(COM3B0) | _BV(WGM31);
	TCCR3B = _BV(WGM33) | c;

    ICR3 = max;
    TCNT3 = 0;
    TIMSK3 = 0;
    TIFR3 = 0;
    OCR3A = 0;
    OCR3B = max;
}

/// phase and freq correct  
/// A = normal
/// B = inverter
/// C = stop
void Timer::initialize_Timer4(CLK_MODE clk, uint16_t max)
{
	pinMode(Timer::TIMER4A_PIN, OUTPUT);
	pinMode(Timer::TIMER4B_PIN, OUTPUT);
	pinMode(Timer::TIMER4C_PIN, INPUT);

	uint8_t c = static_cast<uint8_t>(clk) & (uint8_t)0x07;
	TCCR4A = _BV(COM4A1) | _BV(COM4B1) | _BV(COM4B0) | _BV(WGM41);
	TCCR4B = _BV(WGM43) | c;

    ICR4 = max;
    TCNT4 = 0;
    TIMSK4 = 0;
    TIFR4 = 0;
    OCR4A = 0;
    OCR4B = max;
}

void Timer::initialize_Timer5(CLK_MODE clk, uint16_t max)
{

}

void Timer::timer_start(void)
{
	GTCCR = 0x00;
}

void Timer::timer_stop(void)
{
    GTCCR = _BV(TSM) | _BV(PSRASY) | _BV(PSRSYNC);
}
