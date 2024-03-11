#include "CVoiceManager.h"
#include <windows.h>
CVoiceManager::CVoiceManager()
{
	pitchbend = 1.0f;
	suspedal = false;
	master_volume = 1.0f ;
}

void CVoiceManager::noteOn(int channel, int noteNo, float velocity)
{
	for (int i = 0; i<VOICE_NUM; i++)
	{
		if (voice[i].getState() == ENVGEN_STOP)
		{
			voice[i].start(channel, noteNo, velocity);
			voice[i].setPitchBend(pitchbend);
			return;
		}
	}

	for (int i = 0; i<VOICE_NUM; i++)
	{
		if (voice[i].getState() == ENVGEN_RELEASE)
		{
			voice[i].start(channel, noteNo, velocity);
			voice[i].setPitchBend(pitchbend);
			return;
		}
	}
}


void CVoiceManager::noteOff(int noteNo)
{
	for (int i = 0; i<VOICE_NUM; i++)
	{
		if (voice[i].getKey() == noteNo)
		{
			if (voice[i].getState() == ENVGEN_RELEASE
				|| voice[i].getState() == ENVGEN_STOP)
			{
				continue;
			}
			if (voice[i].getSusPedal())
			{
				continue;
			}
			if (suspedal)
			{
				voice[i].setSusPedal(true);
				//ここではstopは先延ばしにされ、ペダルが離されたタイミングでsusPedal関数側のvoice[i].stop()でstopされる
				//ノートオフにされて本来stopされるべきだが、サステインペダルのおかげで鳴り続けているノートにtrueという印を付けているとも考えられる
				break;
			}
			else
			{
				// サステインペダルが踏まれていない場合、
				// noteOff処理を行う
				voice[i].stop();
				break;
			}
		}
	}
}

void CVoiceManager::update()
{
	for (int i = 0; i<VOICE_NUM; i++)
	{
		voice[i].update();
	}
}

double CVoiceManager::process()
{
	double result = 0.0;
	for (int i = 0; i<VOICE_NUM; i++)
	{
		result += voice[i].process();
	}

	return result * 0.2 * (double)master_volume;
}

void CVoiceManager::setPitchBend(float value)
{
	pitchbend = pow(2.0f, (value / 12.0f));

	for (int i = 0; i<VOICE_NUM; i++)
	{
		voice[i].setPitchBend(pitchbend);
	}
}

void CVoiceManager::susPedal(bool state)
{
	// サステインペダルが踏まれた場合(false→trueに変わった場合)
	if (!suspedal && state)
	{
		// 特に何もしない
	}

	// サステインペダルが離された場合(true→falseに変わった場合)
	if (suspedal && !state)
	{
		for (int i = 0; i<VOICE_NUM; i++)
		{
			if (voice[i].getState() == ENVGEN_RELEASE
				|| voice[i].getState() == ENVGEN_STOP)
			{
				continue;
			}

			// サステインペダルが踏み込まれた状態でnoteOffされたVoiceを
			// 実際にnoteOffの処理を実行する
			if (voice[i].getSusPedal())
			{
				voice[i].stop();
			}
		}
	}
	suspedal = state;
}
void CVoiceManager::setWaveformType(int tag, float value) {
	for (int i = 0; i < VOICE_NUM; i++)
	{
		voice[i].setWaveformType(tag, value);
	}
}

void CVoiceManager::setADSR(int tag, float value)
{
	for (int i = 0; i < VOICE_NUM; i++)
	{
		voice[i].setADSR(tag, value);
	}
};

void CVoiceManager::setVolume(int tag, float value) {
	for (int i = 0; i < VOICE_NUM; i++)
	{
		voice[i].setVolume(tag,value);
	}
}
void CVoiceManager::setMasterVolume(float value) {
	master_volume = value;
}

void CVoiceManager::switchSynthMode() { 
	for (int i = 0; i < VOICE_NUM; i++)
	{
		voice[i].switchSynthMode();
	}
}

void CVoiceManager::setModCoarse(int tag, float value) {
	for (int i = 0; i < VOICE_NUM; i++)
	{
		voice[i].setModCoarse(tag, value);
	}
}

void CVoiceManager::setModOct(int tag, float value) {
	for (int i = 0; i < VOICE_NUM; i++)
	{
		voice[i].setModOct(tag, value);
	}
}

void CVoiceManager::setFilterFreq(int tag, float value) {
	for (int i = 0; i < VOICE_NUM; i++)
	{
		voice[i].setFilterFreq(tag, value);
	}
}

void CVoiceManager::setFilterQ(int tag, float value) {
	for (int i = 0; i < VOICE_NUM; i++)
	{
		voice[i].setFilterQ(tag, value);
	}
}

void CVoiceManager::setFilterType(int tag, float type) {
	for (int i = 0; i < VOICE_NUM; i++)
	{
		
		voice[i].setFilterType(tag, type);
	}
}

void CVoiceManager::setFilterGain(int tag, float type) {
	for (int i = 0; i < VOICE_NUM; i++)
	{

		voice[i].setFilterGain(tag, type);
	}
}