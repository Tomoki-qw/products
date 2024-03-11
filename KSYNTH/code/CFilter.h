#pragma once

#include <math.h>
#include <stdio.h>
#include "myvst3def.h"
// --------------------------------------------------------------------------------
// CMyFilter
// --------------------------------------------------------------------------------
class CFilter
{
private:
	// フィルタの係数
	float a0, a1, a2, b0, b1, b2;
	// バッファ
	float out1, out2;
	float in1, in2;

	float freq, q;
	float type;
	float gain;
public:
	CFilter();

	void start();

	void stop();

	void update();



	// 入力信号にフィルタを適用する関数
	float pinknoise(float in);
	float process(float in);

	void setFreq(float value);
	void setQ(float value);
	void setType(float value);
	void setGain(float value);
	//inline float pinkfilter(float in);
	//inline void init_pink();
	void calcFilter(float type, float freq, float q, float gain);
	// フィルタ係数を計算するメンバー関数
	void Bypass();
	void LowPass(float freq, float q, float samplerate = 44100.0f);
	void HighPass(float freq, float q, float samplerate = 44100.0f);
	void BandPass(float freq, float bw, float samplerate = 44100.0f);
	void Notch(float freq, float bw, float samplerate = 44100.0f);
	void LowShelf(float freq, float q, float gain = 0, float samplerate = 44100.0f);
	void HighShelf(float freq, float q, float gain = 0, float samplerate = 44100.0f);
	void Peaking(float freq, float bw, float gain = 0, float samplerate = 44100.0f);
	void AllPass(float freq, float q, float samplerate = 44100.0f);
};
