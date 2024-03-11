#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CEnvGen.h"
#include "CFilter.h"
#include "COscillator.h"
#include "myvst3def.h"



class CAmplifire
{
protected:
	int key;
	double velo;
	double volume;
	COscillator vco;
	CEnvGen eg;
	CFilter fg;

	double out = 0.0;
public:
	CAmplifire();

	void start(int channel, int noteNo, float velocity);

	void stop();

	void update();
	
	double process();

	int getState() { return eg.getState(); }
	int getKey() { return key; }

	void setPitchBend(float value);

	void setWaveformType(float value);

	//ADSR設定
	void setADSR(int tag, float value);

	//キャリアのFM処理
	double process_FM(double modulator);

	//ボリューム設定
	void setVolume(float value);

	void setModCoarse(float value);

	void setModOct(float value);

	void setFilterFreq(float value);

	void setFilterQ(float value);

	void setFilterType(float type);

	void setFilterGain(float value);
};

