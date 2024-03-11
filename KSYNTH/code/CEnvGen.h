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
	double volume; // エンベロープジェネレータの現在の値
	double volumeReleased; // ノートOff時のエンベロープジェネレータの値
	double samplerate = 44100.0;
	int state; // 現在の状態

	double A; // アタック時のvolume増加量
	double D; // ディケイ時のvolume増加量
	double S; // サステイン時のvolume
	double R; // リリース時のvolume増加量

public:
	CEnvGen(void);

	// MIDIノートオンのときに呼び出される関数
	void start();

	// MIDIノートオフのときに呼び出される関数
	void stop();

	// エンベロープジェネレータの状態更新する関数
	void update();

	// 現在のエンベロープジェネレータの値を返す関数
	double process();

	// ADSRの値を設定する関数
	// Attack、Decay、Releaseはミリ秒で、Susteinは0.0～1.0の範囲で設定する
	void setADSR(double Attack, double Decay, double Sustain, double Release);

	void setA(double Attack);
	void setD(double Decay);
	void setS(double Sustain);
	void setR(double Release);
	// エンベロープジェネレータの状態を返す関数
	int getState() { return state; };


};


