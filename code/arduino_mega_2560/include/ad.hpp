#ifndef AD_HPP
#define AD_HPP

#include <ad.hpp>
#include <Arduino.h>
#include <task.hpp>

class AD : Task<AD>
{
public:
    static void initialize(void)
    {
        pinMode(A0, INPUT);
        //ADクロックを設定する

        ADMUX = _BV(MUX4)
        ADCSRB = _BV(MUX5);
        ADCSRA = _BV(ADEN) | _BV(ADSC);
        ADCSRB = 0;
        DIDR0 = 0;
        DIDR2 = 0;
    }

    static void process(void)
    {
        //AD設定
        analogRead(A0);
    }

    static void finalize(void)
    {
        //AD変換停止
    }
};
#endif
