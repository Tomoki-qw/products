#include "COscillator.h"

COscillator::COscillator()
{
	pitch = 440.0;
	bend = 1.0;
	phase= 0.0;
	type = 0.0f;//仮のタイプ指定：sine
	coarse = 1.0;
	oct = 0;
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
	phase += pitch * bend * coarse * pow(double(2.0), double(oct)) / sampling_rate;
	phase -= floor(phase);
}

double COscillator::process()
{
	return waveform.waveform_type(type, phase);
}

void COscillator::setPitchBend(float value)
{
	bend = (double)value;
}

void COscillator::setWaveformType(float value) 
{
	type = value;
};

double COscillator::process_FM(double modulator) {
	return waveform.waveform_type(type, phase, modulator);
}

void COscillator::setModCoarse(float value) {
	if (0.0f <= value && value < 0.05f) { coarse = 0.5; }
	else if (0.05f <= value && value < 0.15f) { coarse = 1.0; }
	else if (0.15f <= value && value < 0.25f) { coarse = 2.0; }
	else if (0.25f <= value && value < 0.35f) { coarse = 3.0; }
	else if (0.35f <= value && value < 0.45f) { coarse = 4.0; }
	else if (0.45f <= value && value < 0.55f) { coarse = 5.0; }
	else if (0.55f <= value && value < 0.65f) { coarse = 6.0; }
	else if (0.65f <= value && value < 0.75f) { coarse = 7.0; }
	else if (0.75f <= value && value < 0.85f) { coarse = 8.0; }
	else if (0.85f <= value && value < 0.95f) { coarse = 9.0; }
	else if (0.95f <= value && value<= 1.0f) { coarse = 10.0; }
}

void COscillator::setModOct(float value) {
	if (0.0f <= value && value < 0.0625f) { oct = -4; }//0
	else if (0.0625f <= value && value < 0.1875f) { oct = -3; }//0.125
	else if (0.1875f <= value && value < 0.3125f) { oct = -2; }//0.25
	else if (0.3125f <= value && value < 0.4375f) { oct = -1; }//0.375
	else if (0.4375f <= value && value < 0.5625f) { oct = 0; }//0.5
	else if (0.5625f <= value && value < 0.6875f) { oct = 1; }//0.625
	else if (0.6875f <= value && value < 0.8125f) { oct = 2; }//0.75
	else if (0.8125f <= value && value < 0.9375f) { oct = 3; }//0.875
	else if (0.9375f <= value && value < 1.0f) { oct = 4; }//1
}
