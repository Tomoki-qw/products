#include "CWaveform.h"
#include<stdlib.h>

#define M_PI 3.1415926
CWaveform::CWaveform()
{

}
double CWaveform::waveform_sine(double phase, double modulator) {
	return sin(2.0 * M_PI * phase + modulator);
}

double CWaveform::waveform_saw(double phase, double modulator) {
    phase -= floor(phase + modulator);
	return 2.0 * (phase - 0.5);
}

double CWaveform::waveform_triangle(double phase, double modulator) {
	double tr;
    phase -= floor(phase + modulator);
    if (phase > 0.5) {
        tr = 1.0 - phase;    // 0.5 ‚æ‚è‘å‚«‚¢‚Ì‚Å”½“]
    }
    else {
        tr = phase;          // ‚»‚¤‚Å‚È‚¯‚ê‚Î‚»‚Ì‚Ü‚Ü
    } 
    tr *= 2.0;               // 2”{‚µ‚Ä 0.0`1.0 ‚Ì”ÍˆÍ‚É
    return 2.0 * (tr - 0.5); // -1.0`1.0 ‚Ì”ÍˆÍ‚É
}

double CWaveform::waveform_pulse(double phase, double modulator) {
    phase -= floor(phase + modulator);
    if (phase > 0.5) {
        return 1.0;
    }
    else {
        return -1.0;
    }
}
double CWaveform::waveform_white(double phase, double modulator) {
    return 2.0 * ((double)rand() / RAND_MAX - 0.5);
}

double CWaveform::waveform_type(float type, double phase, double modulator)
{
    //0.0f  = sine
    //0.25f = saw
    //0.5f  = triangle
    //0.75f = pulse
    //1.0f  = white

        if (type == 0.0f) return waveform_sine(phase, modulator);
        else if (type == 0.25f) return waveform_saw(phase, modulator);
        else if (type == 0.5f) return waveform_triangle(phase, modulator);
        else if (type == 0.75f) return waveform_pulse(phase, modulator);
        else if (type == 1.0f) return waveform_white(phase, modulator);
        else return 0.0f;
};

