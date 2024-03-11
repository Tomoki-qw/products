#pragma once

#include <math.h>

#include "CRingBuffur.h"

float chorus_mix = 0.5f;
float chorus_rate = 16.0f;
float chorus_depth = 200.0f;
float chorus_feedback = 0.8f;
bool isChorusOn = 0;
// 線形補間
float lerp(float v1, float v2, float t)
{
	return (1.0f - t) * v1 + t * v2;
}

void chorus(float inL[], float inR[], float outL[], float outR[], int wavelength, float ch_mix, float ch_rate, float ch_depth, float ch_feedback)
{


	// エフェクターのパラメーター
	float mix = ch_mix; // コーラスのかかり具合。0.0～1.0の間
	float rate = ch_rate; // コーラスの揺らぎの間隔。0Hz～16Hz程度
	float depth = ch_depth; // コーラスの揺らぎの深さ。5.0～200.0サンプル程度
	float feedback = ch_feedback; // コーラスのフィードバック量。0.0～1.0の間

	// 内部変数
	CRingBuffur ringbufL, ringbufR; 

	// ディレイタイムをサンプル数に変換して設定
	int delaysample = 1000;
	ringbufL.SetInterval(delaysample);
	ringbufR.SetInterval(delaysample);

	float theta = 0; // ディレイ読み込み位置を揺らすためのsin関数の角度 θ。初期値は0
	float speed = (2.0f * 3.14159265f * rate) / 44100.0f; // 揺らぎのスピード。角速度ωと同じ。

	// 入力信号にコーラスかける
	for (int i = 0; i < wavelength; i++)
	{
		// 角度θに角速度を加える
		theta += speed;

		// 読み込み位置を揺らす量を計算
		// sin()関数の結果にdepthを掛ける
		float a = sin(theta) * depth;

		// 読み込み位置を揺らした際の前後の整数値を取得(あとで線形補間するため)
		int p1 = (int)a;
		int p2 = a + 1;

		// 前後の整数値から読み込み位置の値を線形補間で割り出す
		float lerpL1 = lerp(ringbufL.Read(p1), ringbufL.Read(p2), a - (float)p1);
		float lerpR1 = lerp(ringbufR.Read(p1), ringbufR.Read(p2), a - (float)p1);



		// 入力信号にディレイ信号を混ぜる
		float tmpL = (1.0f - mix) * inL[i] + mix * lerpL1;
		float tmpR = (1.0f - mix) * inR[i] + mix * lerpR1;

		// ディレイ信号として入力信号とフィードバック信号をリングバッファに書き込み
		ringbufL.Write((1.0f - feedback) * inL[i] + feedback * tmpL);
		ringbufR.Write((1.0f - feedback) * inR[i] + feedback * tmpR);

		// リングバッファの状態を更新する
		ringbufL.Update();
		ringbufR.Update();

		// 出力信号に書き込む
		outL[i] = tmpL;
		outR[i] = tmpR;
	}
}