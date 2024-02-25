#include "COscillator.h"

COscillator::COscillator()
{
	pitch = 440.0f;
	bend = 1.0f;
	phase= 0.0;
}

void COscillator::start(float freq)
{
	pitch = freq;
	phase = 0.0;
}

void COscillator::stop()
{

}

void COscillator::update()
{
	phase += pitch * bend / sampling_rate;
	phase -= floor(phase);
}

float COscillator::process()
{
	return waveform.waveform_type(type, phase);
}

void COscillator::setPitchBend(float value)
{
	bend = value;
}

void COscillator::setWaveformType(float value) 
{
	type = value;
};

float COscillator::process_FM(float modulator) {
	return waveform.waveform_type(type, phase, modulator);
}