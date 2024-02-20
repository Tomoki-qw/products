#pragma once

#include <math.h>
#include <stdio.h>


#define ENVGEN_ATTACK    0
#define ENVGEN_DECAY     1
#define ENVGEN_SUSTAIN   2
#define ENVGEN_RELEASE   3
#define ENVGEN_STOP      4


class CEnvGen
{
protected:
	float volume; // エンベロープジェネレータの現在の値
	float volumeReleased; // ノートOff時のエンベロープジェネレータの値
	float samplerate = 44100.0f;
	int state; // 現在の状態

	float A; // アタック時のvolume増加量
	float D; // ディケイ時のvolume増加量
	float S; // サステイン時のvolume
	float R; // リリース時のvolume増加量

public:
	CEnvGen(void);

	// MIDIノートオンのときに呼び出される関数
	void start();

	// MIDIノートオフのときに呼び出される関数
	void stop();

	// エンベロープジェネレータの状態更新する関数
	void update();

	// 現在のエンベロープジェネレータの値を返す関数
	float process();

	// ADSRの値を設定する関数
	// Attack、Decay、Releaseはミリ秒で、Susteinは0.0～1.0の範囲で設定する
	void setADSR(float Attack, float Decay, float Sustain, float Release);

	void setA(float Attack);
	void setD(float Decay);
	void setS(float Sustain);
	void setR(float Release);
	// エンベロープジェネレータの状態を返す関数
	int getState() { return state; };


};


