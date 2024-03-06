#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CVoice.h"
#include "myvst3def.h"

// 最大同時発音数
#define VOICE_NUM 32

class CVoiceManager
{
protected:
	CVoice voice[VOICE_NUM]; // Voiceクラス

	float pitchbend; // ピッチベンド用変数 (2音下～2音上の範囲)
	bool  suspedal;  // サステインペダル用変数 (trueで踏まれている状態)
	float master_volume;
public:
	CVoiceManager();

	// MIDIノートオン、オフのときに呼び出される関数
	void noteOn(int channel, int noteNo, float velocity);
	void noteOff(int noteNo);

	// 全Voiceの状態を更新する関数。VSTのprocess関数内で毎サンプルごとに呼び出される
	void update();

	// 全Voiceの振幅状態を合計して返す関数。VSTのprocess関数内で毎サンプルごとに呼び出される
	float process();

	// ピッチベンドとサステインペダルが操作されたときの関数
	void setPitchBend(float value);
	void susPedal (bool state);
	bool getSusPedal() { return suspedal; };

	// waveformtypeを設定する関数
	void setWaveformType(int tag, float value);

	//ADSR設定
	void setADSR(int tag, float value);

	//volume調整
	void setVolume(int tag, float value);

	void setMasterVolume(float value);

	void switchSynthMode();

	void setModCoarse(int tag, float value);

	void setModOct(int tag, float value);
};
