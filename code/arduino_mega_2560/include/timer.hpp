#ifndef TIMER_HPP
#define TIMER_HPP

#include <Arduino.h>
#include <avr/io.h>
#include "Base.hpp"

enum struct CLK_MODE : uint8_t
{
	// 16000000 = 16Mhz = 0.0625us
	Stop = 0,
	Prescaling_1 = 1,	// 0.0625us = 62500Hz
	Prescaling_8 = 2,	// 0.5us = 7812.5Hz
	Prescaling_64 = 3,   // 4.0us = 976.5625Hz
	Prescaling_256 = 4,  // 16.0us = 244.140625Hz
	Prescaling_1024 = 5, // 64.0us = 61.03515625Hz
	Ext_Falling_Edge = 6,
	Ext_Rissing_Edge = 7,
};

// timer1,3,4を使ったinverter pwm出力
class Timer : Base
{
  public:
	static const uint8_t TIMER0A_PIN = 13; // Timer 0
	static const uint8_t TIMER0B_PIN = 4;  // Timer 0
	static const uint8_t TIMER1A_PIN = 11; // Timer 1
	static const uint8_t TIMER1B_PIN = 12; // Timer 1
	static const uint8_t TIMER1C_PIN = 13; // Timer 1
	static const uint8_t TIMER3A_PIN = 5; // Timer 3
	static const uint8_t TIMER3B_PIN = 2; // Timer 3
	static const uint8_t TIMER3C_PIN = 3; // Timer 3
	static const uint8_t TIMER4A_PIN = 6; // Timer 4
	static const uint8_t TIMER4B_PIN = 7; // Timer 4
	static const uint8_t TIMER4C_PIN = 8; // Timer 4
	static const uint8_t TIMER5A_PIN = 46; // Timer 5
	static const uint8_t TIMER5B_PIN = 45; // Timer 5
	static const uint8_t TIMER5C_PIN = 44; // Timer 5

	static void initialize_Timer0(CLK_MODE clk, uint16_t max);
	static void initialize_Timer1(CLK_MODE clk, uint16_t max);
	static void initialize_Timer3(CLK_MODE clk, uint16_t max);
	static void initialize_Timer4(CLK_MODE clk, uint16_t max);
	static void initialize_Timer5(CLK_MODE clk, uint16_t max);
	static void timer_start(void);
	static void timer_stop(void);

  protected:
  private:
	Timer();
	~Timer();
};

#endif
