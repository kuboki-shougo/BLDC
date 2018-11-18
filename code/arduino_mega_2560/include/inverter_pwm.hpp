#ifndef PWM_HPP
#define PWM_HPP

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

enum struct stop_mode : uint8_t
{
	Normal = 0,
	Short = 1,
};

// timer1,3,4を使ったinverter pwm出力
class inverter_pwm : base
{
  public:
	static const uint16_t MAX_DUTY = 255;
	static const uint16_t MIN_DUTY = 0;
	static const uint8_t HIGH_U_PIN = 11; // timer 1
	static const uint8_t LOW_U_PIN = 12;  // timer 1
	static const uint8_t HIGH_V_PIN = 5;  // timer 3
	static const uint8_t LOW_V_PIN = 2;   // timer 3
	static const uint8_t HIGH_W_PIN = 6;  // timer 4
	static const uint8_t LOW_W_PIN = 7;   // timer 4

	static void initialize(clk_mode clk, uint16_t dead_time);
	static void start(void);
	static void stop(stop_mode mode);

	static void getDuty(uint16_t *u, uint16_t *v, uint16_t *w);
	static void setDuty(uint16_t u, uint16_t v, uint16_t w);
	static uint16_t getDeadTime(void);

  protected:
  private:
	static uint16_t duty_u;
	static uint16_t duty_v;
	static uint16_t duty_w;
	static uint16_t deat_time;

	static void outputLow(void);
	static void outputShort(void);
	static void calcDuty(uint16_t u, uint16_t v, uint16_t w, uint16_t dead);
};

#endif
