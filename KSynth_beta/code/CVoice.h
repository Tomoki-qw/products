#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CEnvGen.h"
#include "CAmplifire.h"
#include "myvst3def.h"

#define MODE_ANALOG 0
#define MODE_FM 1
class CVoice
{
protected:
	//int         key;  // MIDIノートNo
	//float       velo; // ヴェロシティ (floatに注意。0.0～1.0の間)
	CAmplifire vca[VCA_NUM];  // 波形クラス(VCO)
	CEnvGen     eg;  // エンベロープジェネレータ(VCA)
	float bend;     // ピッチベンド量 (0.5～2の範囲)
	bool  suspedal_cvoice; // サステインペダル用変数 (trueのとき踏まれた状態でnoteOffを受けた)

	int synth_mode = MODE_ANALOG; //0がアナログ、1がFM
public:
	CVoice();

	// MIDIノートオンのときに呼び出される関数。Voiceを発音させる
	void start(int channel, int noteNo, float velocity);
	
	// MIDIノートオフのときに呼び出される関数。Voiceを発音させる
	void stop();

	// Voice内のオシレーターとエンベロープジェネレータ状態を更新する関数。
	void update();

	// オシレーターとエンベロープジェネレータからVoiceの振幅値を計算して返す関数。
	float process();

	// ピッチベンドの操作をオシレータに反映させる関数
	void setPitchBend(float value);

	// サステインペダルの状態を操作・取得する関数
	void setSusPedal(bool state) { suspedal_cvoice = state; }
	bool getSusPedal() { return suspedal_cvoice; }

	// Voiceの状態や発音中のキーの値を返す関数
	int getState();
	int getKey();

	// waveformtypeを設定する関数
	void setWaveformType(int tag, float value);

	//ADSR設定
	void setADSR(int tag, float value);

	//加算方式アナログシンセモード
	float additiveSynth(float amp);
	
	//FMシンセモード
	float FMSynth(float amp);

	void setVolume(int tag, float value);

	void switchSynthMode();
};
