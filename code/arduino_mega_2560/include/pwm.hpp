#ifndef PWM_HPP
#define PWM_HPP

#include <Arduino.h>
#include <avr/io.h>
#include "base.hpp"
#include "Timer.hpp"

// timer1,3,4を使ったinverter pwm出力
class PWM : Base
{
  public:
	static const uint8_t HIGH_U_PIN = Timer::TIMER1A_PIN;
	static const uint8_t LOW_U_PIN = Timer::TIMER1B_PIN;
	static const uint8_t HIGH_V_PIN = Timer::TIMER3A_PIN;
	static const uint8_t LOW_V_PIN = Timer::TIMER3B_PIN;
	static const uint8_t HIGH_W_PIN = Timer::TIMER4A_PIN;
	static const uint8_t LOW_W_PIN = Timer::TIMER4B_PIN;

	static const CLK_MODE clk = CLK_MODE::Prescaling_8;
	static const uint16_t max = 1000;
	static const uint16_t dead_time = 3;

	static void initialize();
	static void getDuty(uint16_t *u, uint16_t *v, uint16_t *w);
	static void setDuty(uint16_t u, uint16_t v, uint16_t w);

  protected:
  private:
	static uint16_t duty_u;
	static uint16_t duty_v;
	static uint16_t duty_w;
	static uint16_t duty_u_l;
	static uint16_t duty_v_l;
	static uint16_t duty_w_l;

	static uint16_t duty_u_n1;
	static uint16_t duty_v_n1;
	static uint16_t duty_w_n1;

	PWM();
	~PWM();
	static void calcDuty(uint16_t duty, uint16_t *high, uint16_t *low);
};

#endif
