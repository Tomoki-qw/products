#include "CVoice.h"
#include <Windows.h>

CVoice::CVoice()
{
	bend = 0.0f;
	suspedal_cvoice = false;
}


void CVoice::start(int channel, int noteNo, float velocity)
{
	for (int i = 0; i < VCA_NUM; i++) {
		vca[i].start(channel, noteNo, velocity);
		bend = 0.0f;
		suspedal_cvoice = false;
	}
}

void CVoice::stop()
{
	for (int i = 0; i < VCA_NUM; i++) {
		vca[i].stop();
	}
}

void CVoice::update()
{
	for (int i = 0; i < VCA_NUM; i++) {
		vca[i].update();
	}
}

double CVoice::process()
{
	double amp = 0.0;
	if (synth_mode == MODE_ANALOG) {
		return additiveSynth(amp);
		//return 0.0f;
	}
	else  {
		return FMSynth(amp);
		//return 0.0f;
	}
	
}

void CVoice::setPitchBend(float value)
{
	for (int i = 0; i < VCA_NUM; i++) {
		vca[i].setPitchBend(value);
	}
}
//要改善
int CVoice::getState() {
		return vca[0].getState();
}
int CVoice::getKey() { 
		return vca[0].getKey();
}


void CVoice::setWaveformType(int tag, float value)
{
		vca[tag].setWaveformType(value);
};

//ADSR設定
void CVoice::setADSR(int tag, float value)
{
	switch (tag) {
	case ADSR_OSC1_A:
	case ADSR_OSC1_D:
	case ADSR_OSC1_S:
	case ADSR_OSC1_R:
		vca[0].setADSR(tag, value);
		break;
	case ADSR_OSC2_A:
	case ADSR_OSC2_D:
	case ADSR_OSC2_S:
	case ADSR_OSC2_R:
		vca[1].setADSR(tag, value);
		break;
	case ADSR_OSC3_A:
	case ADSR_OSC3_D:
	case ADSR_OSC3_S:
	case ADSR_OSC3_R:
		vca[2].setADSR(tag, value);
		break;
	}
}
;


double CVoice::additiveSynth(double amp) {
	for (int i = 0; i < VCA_NUM; i++) {
		amp += vca[i].process();
	}
	return amp;
}


double CVoice::FMSynth(double amp) {
	double modulator = vca[2].process();
	modulator = vca[1].process_FM(modulator);
	double carrier = vca[0].process_FM(modulator);
	return carrier;
}

void CVoice::setVolume(int tag, float value) {
	
	//vca1ボリューム(キャリア)
	if (tag == VOLUME_TAG_1) 
	{
		vca[0].setVolume(value);
	}

	//vca2ボリューム(モジュレータ)
	else if (tag == VOLUME_TAG_2) 
	{
		vca[1].setVolume(value);
	}
	//vca2ボリューム(モジュレータ)
	else if (tag == VOLUME_TAG_3)
	{
		vca[2].setVolume(value);
	}
}

void CVoice::switchSynthMode()
{
	
	if (synth_mode == MODE_ANALOG) {
		synth_mode = MODE_FM;
	}
	else {
		synth_mode = MODE_ANALOG;
	}
	//synth_mode = MODE_FM;
}

void CVoice::setModCoarse(int tag, float value) {
	switch (tag) {
	case MOD_COARSE1_TAG:
		vca[0].setModCoarse(value);
		break;
	case MOD_COARSE2_TAG:
		vca[1].setModCoarse(value);
		break;
	case MOD_COARSE3_TAG:
		vca[2].setModCoarse(value);
		break;
	}
}

void CVoice::setModOct(int tag, float value) {
	switch (tag) {
	case MOD_OCT1_TAG:
		vca[0].setModOct(value);
		break;
	case MOD_OCT2_TAG:
		vca[1].setModOct(value);
		break;
	case MOD_OCT3_TAG:
		vca[2].setModOct(value);
		break;
	}
}

void CVoice::setFilterFreq(int tag, float value) {
	switch (tag) {
	case O1_FILTER_FREQ:
		vca[0].setFilterFreq(value);
	case O2_FILTER_FREQ:
		vca[1].setFilterFreq(value);
	case O3_FILTER_FREQ:
		vca[2].setFilterFreq(value);

	}
}

void CVoice::setFilterQ(int tag, float value) {
	switch (tag) {
	case O1_FILTER_Q:
		vca[0].setFilterQ(value);
	case O2_FILTER_Q:
		vca[1].setFilterQ(value);
	case O3_FILTER_Q:
		vca[2].setFilterQ(value);
	}
}

void CVoice::setFilterType(int tag, float type) {
	switch (tag) {
	case O1_FILTER_TYPE:
		vca[0].setFilterType(type);
	case O2_FILTER_TYPE:
		vca[1].setFilterType(type);
	case O3_FILTER_TYPE:
		vca[2].setFilterType(type);
	}
}

void CVoice::setFilterGain(int tag, float value) {
	switch (tag) {
	case O1_FILTER_GAIN:
		vca[0].setFilterGain(value);
	case O2_FILTER_GAIN:
		vca[1].setFilterGain(value);
	case O3_FILTER_GAIN:
		vca[2].setFilterGain(value);
	}
}