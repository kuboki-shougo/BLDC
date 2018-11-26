#ifndef MOTOR_CTRL_HPP
#define MOTOR_CTRL_HPP

#include <Arduino.h>
#include <math.h>
#include <task.hpp>
#include <pwm.hpp>

class MotorCtrl : Task<MotorCtrl>
{
  public:
    static constexpr float sqrt_2_3 = 0.81649658092772603273242802490196F; //sqrt(2.0 / 3.0);
    static constexpr float pi_2_3 = (float)(2.0 * PI / 3.0);

    static void initialize(void)
    {
        //変数初期化
    }

    static void process(void)
    {
        //1.電流値取得 & Vdc電圧取得

        //2.クラーク変換 & パーク変換
        
        //3.PI制御

        //4.逆パーク変換 or 空間ベクトル制御

        //5.Duty出力
    }

    static void finalize(void)
    {
        //Duty停止処理
    }


    static float Ia;
    static float Ib;
    static float Id;
    static float Iq;

    static float Vq;
    static float Vd;
    static float Vu;
    static float Vv;
    static float Vw;
    static uint16_t Duty_u;
    static uint16_t Duty_v;
    static uint16_t Duty_w;
    

    static void clark(float Iu, float Iv, float Iw)
    {
        Ia = Iu;
        Ib = (Iu + (2.0 * Iv)) / sqrt(3.0);	
    }

    static void perk(float Ia, float Ib, float th)
    {
        Id = (Ia * cos(th)) + (Ib * sin(th));
        Iq = (-Ia * sin(th)) + (Ib * cos(th));
    }

    static void clarkPerk(float Iu, float Iv, float Iw, float th)
    {
        Id = sqrt_2_3 * (cos(th) * Iu) + (cos(th - MotorCtrl::pi_2_3) * Iv) + (cos(th + MotorCtrl::pi_2_3) * Iw);
        Iq = sqrt_2_3 * (-1.0 * sin(th) * Iu) + (-1.0 * sin(th - MotorCtrl::pi_2_3) * Iv) + (-1.0 * sin(th + MotorCtrl::pi_2_3) * Iw);
    }

    static void inversePerk(float vq, float vd, float th)
    {
        Vu = sqrt_2_3 * (cos(th) * vd) + (-1.0 * sin(th) * vq);
        Vv = sqrt_2_3 * (cos(th - MotorCtrl::pi_2_3) * vd) + (-1.0 * sin(th - MotorCtrl::pi_2_3) * vq);
        Vw = sqrt_2_3 * (cos(th + MotorCtrl::pi_2_3) * vd) + (-1.0 * sin(th + MotorCtrl::pi_2_3) * vq);

        Duty_u = calcDuty(Vu, 5.0F);
        Duty_v = calcDuty(Vv, 5.0F);
        Duty_w = calcDuty(Vw, 5.0F);
    }

    // FPUを積んでないのでこの処理は暫定です。
    // 固定小数点で実装しなおす。
    static uint16_t calcDuty(float voltage, float vdc)
    {
        uint16_t duty;
        if (voltage >= vdc)
        {
            duty = PWM::max;
        }
        else if (voltage < 0.0)
        {
            duty = 0;
        }
        else
        {
            float ratio = voltage / vdc;
            duty = (uint16_t)((float)PWM::max * ratio);
        }
        return (duty);
    }
};
#endif
