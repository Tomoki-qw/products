#pragma once
#include <math.h>
#include <stdio.h>

class CWaveform
{
protected:
public:
	CWaveform();

	float waveform_sine(double phase);
	float waveform_saw(double phase);
	float waveform_triangle(double phase);
	float waveform_pulse(double phase);
	float waveform_white(double phase);

	float waveform_type(float type, double phase);
};