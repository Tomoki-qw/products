#include "CWave.h"

CWave::CWave()
{
	pitch = 440.0f;
	bend = 1.0f;
	phase= 0.0;
}

void CWave::start(float freq)
{
	pitch = freq;
	phase = 0.0;
}

void CWave::stop()
{

}

void CWave::update()
{
	phase += pitch * bend / sampling_rate;
	phase -= floor(phase);
}

float CWave::process()
{
	return waveform.waveform_type(type, phase);
}

void CWave::setPitchBend(float value)
{
	bend = value;
}

void CWave::setWaveformType(float value) 
{
	type = value;
};
