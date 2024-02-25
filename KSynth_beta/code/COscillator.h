#pragma once
#include "CWaveform.h"
#include <math.h>
#include <stdio.h>


class COscillator
{
protected:
	float pitch; // �I�V���[�^�[�̃s�b�`(���g��)
	float bend;  // �s�b�`�x���h��(0.5�`2�͈̔�)
	double phase;
	double sampling_rate = 44100;
	CWaveform waveform;
	float type = 0.0f;//���̃^�C�v�w��Fsine
public:
	COscillator();

	// MIDI�m�[�g�I���̂Ƃ��ɌĂяo�����֐�
	void start(float freq);

	// MIDI�m�[�g�I�t�̂Ƃ��ɌĂяo�����֐�
	void stop();

	// �I�V���[�^�[��Ԃ��X�V����֐�
	void update();

	// ���݂̃I�V���[�^�̐U����Ԃ��֐�
	float process();

	// �s�b�`�x���h�p�ϐ� (2�����`2����͈̔�)
	void setPitchBend(float value);

	// waveformtype��ݒ肷��֐�
	void setWaveformType(float value);

	//�L�����A��FM����
	float process_FM(float modulator);
};
