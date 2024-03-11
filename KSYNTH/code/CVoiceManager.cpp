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
				//�����ł�stop�͐扄�΂��ɂ���A�y�_���������ꂽ�^�C�~���O��susPedal�֐�����voice[i].stop()��stop�����
				//�m�[�g�I�t�ɂ���Ė{��stop�����ׂ������A�T�X�e�C���y�_���̂������Ŗ葱���Ă���m�[�g��true�Ƃ������t���Ă���Ƃ��l������
				break;
			}
			else
			{
				// �T�X�e�C���y�_�������܂�Ă��Ȃ��ꍇ�A
				// noteOff�������s��
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
	// �T�X�e�C���y�_�������܂ꂽ�ꍇ(false��true�ɕς�����ꍇ)
	if (!suspedal && state)
	{
		// ���ɉ������Ȃ�
	}

	// �T�X�e�C���y�_���������ꂽ�ꍇ(true��false�ɕς�����ꍇ)
	if (suspedal && !state)
	{
		for (int i = 0; i<VOICE_NUM; i++)
		{
			if (voice[i].getState() == ENVGEN_RELEASE
				|| voice[i].getState() == ENVGEN_STOP)
			{
				continue;
			}

			// �T�X�e�C���y�_�������ݍ��܂ꂽ��Ԃ�noteOff���ꂽVoice��
			// ���ۂ�noteOff�̏��������s����
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