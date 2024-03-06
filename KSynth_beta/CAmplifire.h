#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CEnvGen.h"
#include "COscillator.h"
#include "myvst3def.h"



class CAmplifire
{
protected:
	int key;
	float velo;
	float volume;
	COscillator vco;
	CEnvGen eg;

	float out = 0.0f;
public:
	CAmplifire();

	void start(int channel, int noteNo, float velocity);

	void stop();

	void update();
	
	float process();

	int getState() { return eg.getState(); }
	int getKey() { return key; }

	void setPitchBend(float value);

	void setWaveformType(float value);

	//ADSR設定
	void setADSR(int tag, float value);

	//キャリアのFM処理
	float process_FM(float modulator);

	//ボリューム設定
	void setVolume(float value);

	void setModCoarse(float value);

	void setModOct(float value);
};

