#pragma once
#include "CWaveform.h"
#include <math.h>
#include <stdio.h>


class COscillator
{
protected:
	double pitch; // �I�V���[�^�[�̃s�b�`(���g��)
	double bend;  // �s�b�`�x���h��(0.5�`2�͈̔�)
	double phase;
	double sampling_rate = 44100;
	CWaveform waveform;
	float type;

	double coarse;
	int oct;
public:
	COscillator();

	// MIDI�m�[�g�I���̂Ƃ��ɌĂяo�����֐�
	void start(float freq);

	// MIDI�m�[�g�I�t�̂Ƃ��ɌĂяo�����֐�
	void stop();

	// �I�V���[�^�[��Ԃ��X�V����֐�
	void update();

	// ���݂̃I�V���[�^�̐U����Ԃ��֐�
	double process();

	// �s�b�`�x���h�p�ϐ� (2�����`2����͈̔�)
	void setPitchBend(float value);

	// waveformtype��ݒ肷��֐�
	void setWaveformType(float value);

	//�L�����A��FM����
	double process_FM(double modulator);

	void setModCoarse(float value);
	
	void setModOct(float value);
};
