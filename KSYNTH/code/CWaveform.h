#pragma once
#include <math.h>
#include <stdio.h>

class CWaveform
{
protected:
public:
	CWaveform();

	double waveform_sine(double phase,double modulator = 0);
	double waveform_saw(double phase, double modulator = 0);
	double waveform_triangle(double phase, double modulator = 0);
	double waveform_pulse(double phase, double modulator = 0);
	double waveform_white(double phase, double modulator = 0);

	double waveform_type(float type, double phase, double modulator = 0);
};