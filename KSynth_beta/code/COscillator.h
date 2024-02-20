#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CEnvGen.h"
#include "CWave.h"
#include "myvst3def.h"



class COscillator
{
protected:
	int key;
	float velo;
	CWave wave;
	CEnvGen vca;
public:
	COscillator();

	void start(int channel, int noteNo, float velocity);

	void stop();

	void update();
	
	float process();

	int getState() { return vca.getState(); }
	int getKey() { return key; }

	void setPitchBend(float value);

	void setWaveformType(float value);

	//ADSRê›íË
	void setADSR(int tag, float value);
};

