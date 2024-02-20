#pragma once

#include <math.h>
#include <stdio.h>


#define ENVGEN_ATTACK    0
#define ENVGEN_DECAY     1
#define ENVGEN_SUSTAIN   2
#define ENVGEN_RELEASE   3
#define ENVGEN_STOP      4


class CEnvGen
{
protected:
	float volume; // �G���x���[�v�W�F�l���[�^�̌��݂̒l
	float volumeReleased; // �m�[�gOff���̃G���x���[�v�W�F�l���[�^�̒l
	float samplerate = 44100.0f;
	int state; // ���݂̏��

	float A; // �A�^�b�N����volume������
	float D; // �f�B�P�C����volume������
	float S; // �T�X�e�C������volume
	float R; // �����[�X����volume������

public:
	CEnvGen(void);

	// MIDI�m�[�g�I���̂Ƃ��ɌĂяo�����֐�
	void start();

	// MIDI�m�[�g�I�t�̂Ƃ��ɌĂяo�����֐�
	void stop();

	// �G���x���[�v�W�F�l���[�^�̏�ԍX�V����֐�
	void update();

	// ���݂̃G���x���[�v�W�F�l���[�^�̒l��Ԃ��֐�
	float process();

	// ADSR�̒l��ݒ肷��֐�
	// Attack�ADecay�ARelease�̓~���b�ŁASustein��0.0�`1.0�͈̔͂Őݒ肷��
	void setADSR(float Attack, float Decay, float Sustain, float Release);

	void setA(float Attack);
	void setD(float Decay);
	void setS(float Sustain);
	void setR(float Release);
	// �G���x���[�v�W�F�l���[�^�̏�Ԃ�Ԃ��֐�
	int getState() { return state; };


};


