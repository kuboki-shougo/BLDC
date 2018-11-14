#include <Arduino.h>
#include <avr/io.h>

void setup()
{
  const int dead_time = 3;
  u8 duty = 25;

  pinMode(13, INPUT); // OCR0B pin5
  pinMode(4, OUTPUT); // OCR0A pin6

  //TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(COM0B0) | _BV(WGM01) | _BV(WGM00);

  // Phase Correct PWM Mode = _BV(WGM00)
  // OCR0A = inverte = _BV(COM0A1)
  // OCR0B = normal = _BV(COM0B1) | _BV(COM0B0)
  TCCR0A = _BV(COM0A1) | _BV(COM0B1) | _BV(COM0B0) | _BV(WGM00);

  // clkI/O/1024 (From prescaler) = _BV(CS02) | _BV(CS00)
  TCCR0B = _BV(CS02) | _BV(CS00);

  OCR0A = duty + dead_time; // pin6
  OCR0B = 0xFF - duty - dead_time;  // pin5

  // pinMode(9, OUTPUT); // OCR1A pin9
  // pinMode(10, OUTPUT); // OCR1B pin10

  // TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(WGM10);
  // TCCR1B = _BV(WGM12) | _BV(CS10);
  // OCR1A = 160; // pin9
  // OCR1B = 200;  // pin10
  
  // pinMode(3, OUTPUT); // OCR2B pin3
  // pinMode(11, OUTPUT); // OCR2A pin11
  
  // TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  // TCCR2B = _BV(CS20);
  // OCR2A = 240; // pin11
  // OCR2B = 40;  // pin3 
}

void loop()
{
}