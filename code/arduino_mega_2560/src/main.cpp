#include <Arduino.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "PWM.hpp"
#include "Timer.hpp"
#include "MotorCtrl.hpp"

volatile float rad;
volatile float th;

// 初期化
void setup()
{
	rad = 0.0F;
	th = 0.0F;

	//タイマ停止
	Timer::timer_stop();

	//PWM出力を初期化
	PWM::initialize();
	PWM::setDuty(0, 0, 0);

	//1ms周期割り込みを作成
	Timer::initialize_Timer5(CLK_MODE::Prescaling_8, 2000);

	//割り込み許可
	sei();

	//タイマ開始
	Timer::timer_start();
}

//1msタスク
ISR(TIMER5_COMPA_vect)
{
	//擬似角度作成処理
	rad += 0.036F;
	if (rad > 360.0F)
	{
		rad -= 360.0F;
	}
	th = rad * (float)PI / 180.0F;

	//逆パーク変換
	MotorCtrl::inversePerk(5.0F, 0.0F, th);

	//Duty設定
	PWM::setDuty(MotorCtrl::Duty_u, MotorCtrl::Duty_v, MotorCtrl::Duty_w);
}

// バックグラウンド
void loop()
{
}