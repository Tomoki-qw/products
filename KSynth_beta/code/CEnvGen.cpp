#include "CEnvGen.h"


CEnvGen::CEnvGen(void)
{
	volume = 0.0f;
	volumeReleased = 0.0f;

	state = ENVGEN_STOP;

	setADSR(50.0f, 300.0f, 0.5f, 1000.0f);
}

void CEnvGen::start()
{
	volume = 0.0f;
	volumeReleased = 0.0f;

	state = ENVGEN_ATTACK;
}

void CEnvGen::stop()
{
	volumeReleased = volume;

	state = ENVGEN_RELEASE;
}

void CEnvGen::update()
{
	switch (state)
	{
	case ENVGEN_ATTACK:

		volume = volume + A;

		if (volume >= 1.0f)
		{
			volume = 1.0f;
			state = ENVGEN_DECAY;
		}
		return;
	case ENVGEN_DECAY:

		volume = volume - (1.0f - S) * D;

		if (volume <= S)
		{
			volume = S;
			state = ENVGEN_SUSTAIN;
		}
		return;
	case ENVGEN_SUSTAIN:

		return;
	case ENVGEN_RELEASE:
		volume = volume - (volumeReleased)* R;

		if (volume <= 0)
		{
			volume = 0.0f;
			state = ENVGEN_STOP;
		}
		return;
	case ENVGEN_STOP:
		volume = 0.0f;
		return;
	default:
		volume = 0.0f;
		return;
	}
}


float CEnvGen::process()
{
	return volume;
}


void CEnvGen::setADSR(float Attack, float Decay, float Sustain, float Release)
{

	A = 1.0f / (samplerate * Attack / 1000.0f);
	D = 1.0f / (samplerate * Decay / 1000.0f);
	S = Sustain;
	R = 1.0f / (samplerate * Release / 1000.0f);
}
void CEnvGen::setA(float Attack) {
	A = 1.0f / (samplerate * (Attack + 0.005f));
}

void CEnvGen::setD(float Decay) {
	D = 1.0f / (samplerate * (Decay + 0.005f));
}


void CEnvGen::setS(float Sustain) {
	S = Sustain + 0.005f;
}

void CEnvGen::setR(float Release) {
	R = 1.0f / (samplerate * (Release + 0.005f));
}

