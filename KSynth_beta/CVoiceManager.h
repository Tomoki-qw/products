#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CVoice.h"
#include "myvst3def.h"

// �ő哯��������
#define VOICE_NUM 32

class CVoiceManager
{
protected:
	CVoice voice[VOICE_NUM]; // Voice�N���X

	float pitchbend; // �s�b�`�x���h�p�ϐ� (2�����`2����͈̔�)
	bool  suspedal;  // �T�X�e�C���y�_���p�ϐ� (true�œ��܂�Ă�����)
	float master_volume;
public:
	CVoiceManager();

	// MIDI�m�[�g�I���A�I�t�̂Ƃ��ɌĂяo�����֐�
	void noteOn(int channel, int noteNo, float velocity);
	void noteOff(int noteNo);

	// �SVoice�̏�Ԃ��X�V����֐��BVST��process�֐����Ŗ��T���v�����ƂɌĂяo�����
	void update();

	// �SVoice�̐U����Ԃ����v���ĕԂ��֐��BVST��process�֐����Ŗ��T���v�����ƂɌĂяo�����
	float process();

	// �s�b�`�x���h�ƃT�X�e�C���y�_�������삳�ꂽ�Ƃ��̊֐�
	void setPitchBend(float value);
	void susPedal (bool state);
	bool getSusPedal() { return suspedal; };

	// waveformtype��ݒ肷��֐�
	void setWaveformType(int tag, float value);

	//ADSR�ݒ�
	void setADSR(int tag, float value);

	//volume����
	void setVolume(int tag, float value);

	void setMasterVolume(float value);

	void switchSynthMode();

	void setModCoarse(int tag, float value);

	void setModOct(int tag, float value);
};
