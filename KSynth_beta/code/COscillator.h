#pragma once
#include "CWaveform.h"
#include <math.h>
#include <stdio.h>


class COscillator
{
protected:
	float pitch; // オシレーターのピッチ(周波数)
	float bend;  // ピッチベンド量(0.5～2の範囲)
	double phase;
	double sampling_rate = 44100;
	CWaveform waveform;
	float type = 0.0f;//仮のタイプ指定：sine
public:
	COscillator();

	// MIDIノートオンのときに呼び出される関数
	void start(float freq);

	// MIDIノートオフのときに呼び出される関数
	void stop();

	// オシレーター状態を更新する関数
	void update();

	// 現在のオシレータの振幅を返す関数
	float process();

	// ピッチベンド用変数 (2音下～2音上の範囲)
	void setPitchBend(float value);

	// waveformtypeを設定する関数
	void setWaveformType(float value);

	//キャリアのFM処理
	float process_FM(float modulator);
};
