#ifndef TIMER_HPP
#define TIMER_HPP

#include <Arduino.h>
#include <avr/io.h>
#include "base.hpp"

enum struct clk_mode : uint8_t
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
class timer : base
{
  public:
	static const uint8_t TIMER0A_PIN = 13; // timer 0
	static const uint8_t TIMER0B_PIN = 4;  // timer 0
	static const uint8_t TIMER1A_PIN = 11; // timer 1
	static const uint8_t TIMER1B_PIN = 12; // timer 1
	static const uint8_t TIMER1C_PIN = 13; // timer 1
	static const uint8_t TIMER3A_PIN = 5; // timer 3
	static const uint8_t TIMER3B_PIN = 2; // timer 3
	static const uint8_t TIMER3C_PIN = 3; // timer 3
	static const uint8_t TIMER4A_PIN = 6; // timer 4
	static const uint8_t TIMER4B_PIN = 7; // timer 4
	static const uint8_t TIMER4C_PIN = 8; // timer 4
	static const uint8_t TIMER5A_PIN = 46; // timer 5
	static const uint8_t TIMER5B_PIN = 45; // timer 5
	static const uint8_t TIMER5C_PIN = 44; // timer 5

	static void initialize_timer0(clk_mode clk, uint16_t max);
	static void initialize_timer1(clk_mode clk, uint16_t max);
	static void initialize_timer3(clk_mode clk, uint16_t max);
	static void initialize_timer4(clk_mode clk, uint16_t max);
	static void initialize_timer5(clk_mode clk, uint16_t max);
	static void timer_start(void);
	static void timer_stop(void);

  protected:
  private:
	timer();
	~timer();
};

#endif
