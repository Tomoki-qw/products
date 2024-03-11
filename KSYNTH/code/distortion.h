#pragma once
#include "CFilter.h"

float dist_gain = 1.0f;
float dist_volume = 1.0f;
bool isDistOn = 0;//0がoff,1がon

void distortion(float inL[], float inR[], float outL[], float outR[], int wavelength, float di_gain, float di_volume)
{
	// inL[]、inR[]、outL[]、outR[]はそれぞれ入力信号と出力信号のバッファ(左右)
	// wavelenghtはバッファのサイズ、サンプリング周波数は44100Hzとする

	// エフェクターのパラメーター
	float gain = di_gain; // 増幅量。10～300程度(dB換算で20dB～50dB程度)
	float volume = di_volume;   // 出力信号の音量。0.0～1.0の範囲

	// 内部変数
	CFilter highpassL, highpassR; 



	// 入力信号にエフェクターを適用する
	for (int i = 0; i < wavelength; i++)
	{
		// 入力信号にフィルタを適用
		float tmpL = inL[i];
		// 入力信号にゲインを掛けて増幅する
		tmpL = gain * tmpL;

		// 振幅の最大値(ここでは-1.0～1.0)を超えたものをクリッピングする
		if (tmpL > 1.0) { tmpL = 1.0; }
		if (tmpL < -1.0) { tmpL = -1.0; }

		// 右側の入力信号も同様に処理
		float tmpR = inR[i];
		tmpR = gain * tmpR;
		if (tmpR > 1.0) { tmpR = 1.0; }
		if (tmpR < -1.0) { tmpR = -1.0; }

		// 入力信号にフィルタをかける
		outL[i] = volume * tmpL;
		outR[i] = volume * tmpR;
	}
}