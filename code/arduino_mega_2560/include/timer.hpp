#ifndef TIMER_HPP
#define TIMER_HPP

#include <Arduino.h>
#include <avr/io.h>
#include <base.hpp>

enum struct CLK_MODE : uint8_t
{
    // 16000000 = 16Mhz = 0.0625us
    STOP = 0,
    PRESCALING_1 = 1,	// 0.0625us = 62500Hz
    PRESCALING_8 = 2,	// 0.5us = 7812.5Hz
    PRESCALING_64 = 3,   // 4.0us = 976.5625Hz
    PRESCALING_256 = 4,  // 16.0us = 244.140625Hz
    PRESCALING_1024 = 5, // 64.0us = 61.03515625Hz
    EXT_FALLING_EDGE = 6,
    EXT_RISSING_EDGE = 7,
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

    static void initializeTimer0(CLK_MODE clk, uint16_t max);
    static void initializeTimer1(CLK_MODE clk, uint16_t max);
    static void initializeTimer3(CLK_MODE clk, uint16_t max);
    static void initializeTimer4(CLK_MODE clk, uint16_t max);
    static void initializeTimer5(CLK_MODE clk, uint16_t max);
    static void start(void);
    static void stop(void);

  protected:
  private:
    Timer();
    ~Timer();
};

#endif
