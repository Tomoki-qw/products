#include "CVoice.h"
#include <Windows.h>

CVoice::CVoice()
{
	bend = 0.0f;
	suspedal_cvoice = false;
}


void CVoice::start(int channel, int noteNo, float velocity)
{
	for (int i = 0; i < OSCILLATOR_NUM; i++) {
		oscillator[i].start(channel, noteNo, velocity);
		bend = 0.0f;
		suspedal_cvoice = false;
	}
}

void CVoice::stop()
{
	for (int i = 0; i < OSCILLATOR_NUM; i++) {
		oscillator[i].stop();
	}
}

void CVoice::update()
{
	for (int i = 0; i < OSCILLATOR_NUM; i++) {
		oscillator[i].update();
	}
}

float CVoice::process()
{
	float result = 0.0f;
	for (int i = 0; i < OSCILLATOR_NUM; i++) {

		result +=  oscillator[i].process();
	}
	return result;
}

void CVoice::setPitchBend(float value)
{
	for (int i = 0; i < OSCILLATOR_NUM; i++) {
		oscillator[i].setPitchBend(value);
	}
}
//—v‰ü‘P
int CVoice::getState() {
		return oscillator[0].getState();
}
int CVoice::getKey() { 
		return oscillator[0].getKey();
}


void CVoice::setWaveformType(int tag, float value)
{
		oscillator[tag].setWaveformType(value);
};

//ADSRÝ’è
void CVoice::setADSR(int tag, float value)
{
	switch (tag) {
	case ADSR_OSC1_A:
	case ADSR_OSC1_D:
	case ADSR_OSC1_S:
	case ADSR_OSC1_R:
		oscillator[0].setADSR(tag, value);
		break;
	case ADSR_OSC2_A:
	case ADSR_OSC2_D:
	case ADSR_OSC2_S:
	case ADSR_OSC2_R:
		oscillator[1].setADSR(tag, value);
		break;
	}
}
;
