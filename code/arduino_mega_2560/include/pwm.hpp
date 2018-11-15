#ifndef PWM_HPP
#define PWM_HPP

#include <Arduino.h>
#include <avr/io.h>
#include "base.hpp"
#include "configuration.h"

enum clk_mode
{
	Prescaling_1,
	Prescaling_8,
	Prescaling_64,
	Prescaling_256,
	Prescaling_1024,
};

template <class T>
class interface_pwm_8bit_timer : base
{
  public:
	static const uint8_t highside_pin;
	static const uint8_t lowside_pin;

	void initialize(clk_mode clk) { static_cast<T &>(this)->initialize(); }
	void setDuty(uint8_t d) { static_cast<T &>(this)->setDuty(); }

  protected:
	class helper
	{
	  public:
		struct timer_register
		{
			volatile uint8_t *OCR_A;
			volatile uint8_t *OCR_B;
			volatile uint8_t *TCCR_A;
			volatile uint8_t *TCCR_B;
		};

		static void initialize(clk_mode clk, timer_register *reg)
		{
			*reg->OCR_A = (uint8_t)0;
			*reg->OCR_B = (uint8_t)0xFF;

			// Phase Correct PWM Mode = _BV(WGM00)
			// OCR0A = inverte = _BV(COM0A1)
			// OCR0B = normal = _BV(COM0B1) | _BV(COM0B0)
			*reg->TCCR_A = _BV(COM0A1) | _BV(COM0B1) | _BV(COM0B0) | _BV(WGM00);

			switch (clk)
			{
			case clk_mode::Prescaling_1:
				*reg->TCCR_B = _BV(CS00);
				break;
			case clk_mode::Prescaling_8:
				*reg->TCCR_B = _BV(CS01);
				break;
			case clk_mode::Prescaling_64:
				*reg->TCCR_B = _BV(CS01) | _BV(CS00);
				break;
			case clk_mode::Prescaling_256:
				*reg->TCCR_B = _BV(CS02);
				break;
			case clk_mode::Prescaling_1024:
				*reg->TCCR_B = _BV(CS02) | _BV(CS00);
				break;
			default:
				break;
			}		
		}
	};
};

class timer0 : interface_pwm_8bit_timer<timer0>
{
  public:
	static const uint8_t highside_pin = 4;
	static const uint8_t lowside_pin = 13;
	static void initialize(clk_mode clk);
	static void setDuty(uint8_t d);

  protected:
	static uint8_t duty;
};

template <class T>
class interface_pwm_16bit_timer : base
{
  public:
	static const uint8_t highside_pin;
	static const uint8_t lowside_pin;

	void initialize(clk_mode clk) { static_cast<T &>(this)->initialize(); }
	void setDuty(uint16_t d) { static_cast<T &>(this)->setDuty(); }

  protected:
	class helper
	{
	  public:
		struct timer_register
		{
			volatile uint8_t *OCR_A_H;
			volatile uint8_t *OCR_A_L;
			volatile uint8_t *OCR_B_H;
			volatile uint8_t *OCR_B_L;
			volatile uint8_t *TCCR_A;
			volatile uint8_t *TCCR_B;
		};

		static void initialize(clk_mode clk, timer_register *reg)
		{
			*reg->OCR_A_H = (uint8_t)0;
			*reg->OCR_A_L = (uint8_t)0;
			*reg->OCR_B_H = (uint8_t)0xFF;
			*reg->OCR_B_L = (uint8_t)0xFF;

			// Phase Correct PWM Mode = _BV(WGM00)
			// OCR0A = inverte = _BV(COM0A1)
			// OCR0B = normal = _BV(COM0B1) | _BV(COM0B0)
			*reg->TCCR_A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1B0) | _BV(WGM10);

			switch (clk)
			{
			case clk_mode::Prescaling_1:
				*reg->TCCR_B = _BV(CS10);
				break;
			case clk_mode::Prescaling_8:
				*reg->TCCR_B = _BV(CS11);
				break;
			case clk_mode::Prescaling_64:
				*reg->TCCR_B = _BV(CS11) | _BV(CS10);
				break;
			case clk_mode::Prescaling_256:
				*reg->TCCR_B = _BV(CS12);
				break;
			case clk_mode::Prescaling_1024:
				*reg->TCCR_B = _BV(CS12) | _BV(CS10);
				break;
			default:
				break;
			}
		}
	};
};

class timer1 : interface_pwm_16bit_timer<timer1>
{
  public:
	static const uint8_t highside_pin = 12;
	static const uint8_t lowside_pin = 11;
	static void initialize(clk_mode clk);
	static void setDuty(uint16_t d);

  protected:
	static uint16_t duty;
};

class timer3 : interface_pwm_16bit_timer<timer1>
{
  public:
	static const uint8_t highside_pin = 5;
	static const uint8_t lowside_pin = 2;
	static void initialize(clk_mode clk);
	static void setDuty(uint16_t d);

  protected:
	static uint16_t duty;
};

class timer4 : interface_pwm_16bit_timer<timer1>
{
  public:
	static const uint8_t highside_pin = 6;
	static const uint8_t lowside_pin = 7;
	static void initialize(clk_mode clk);
	static void setDuty(uint16_t d);

  protected:
	static uint16_t duty;
};

class timer5 : interface_pwm_16bit_timer<timer1>
{
  public:
	static const uint8_t highside_pin = 46;
	static const uint8_t lowside_pin = 45;
	static void initialize(clk_mode clk);
	static void setDuty(uint16_t d);

  protected:
	static uint16_t duty;
};

#endif
