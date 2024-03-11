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
	double volume; // �G���x���[�v�W�F�l���[�^�̌��݂̒l
	double volumeReleased; // �m�[�gOff���̃G���x���[�v�W�F�l���[�^�̒l
	double samplerate = 44100.0;
	int state; // ���݂̏��

	double A; // �A�^�b�N����volume������
	double D; // �f�B�P�C����volume������
	double S; // �T�X�e�C������volume
	double R; // �����[�X����volume������

public:
	CEnvGen(void);

	// MIDI�m�[�g�I���̂Ƃ��ɌĂяo�����֐�
	void start();

	// MIDI�m�[�g�I�t�̂Ƃ��ɌĂяo�����֐�
	void stop();

	// �G���x���[�v�W�F�l���[�^�̏�ԍX�V����֐�
	void update();

	// ���݂̃G���x���[�v�W�F�l���[�^�̒l��Ԃ��֐�
	double process();

	// ADSR�̒l��ݒ肷��֐�
	// Attack�ADecay�ARelease�̓~���b�ŁASustein��0.0�`1.0�͈̔͂Őݒ肷��
	void setADSR(double Attack, double Decay, double Sustain, double Release);

	void setA(double Attack);
	void setD(double Decay);
	void setS(double Sustain);
	void setR(double Release);
	// �G���x���[�v�W�F�l���[�^�̏�Ԃ�Ԃ��֐�
	int getState() { return state; };


};


