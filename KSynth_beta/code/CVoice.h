#pragma once

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CEnvGen.h"
#include "COscillator.h"
#include "myvst3def.h"

class CVoice
{
protected:
	//int         key;  // MIDI�m�[�gNo
	//float       velo; // ���F���V�e�B (float�ɒ��ӁB0.0�`1.0�̊�)
	COscillator oscillator[OSCILLATOR_NUM];  // �g�`�N���X(VCO)
	CEnvGen     vca;  // �G���x���[�v�W�F�l���[�^(VCA)
	float bend;     // �s�b�`�x���h�� (0.5�`2�͈̔�)
	bool  suspedal_cvoice; // �T�X�e�C���y�_���p�ϐ� (true�̂Ƃ����܂ꂽ��Ԃ�noteOff���󂯂�)
public:
	CVoice();

	// MIDI�m�[�g�I���̂Ƃ��ɌĂяo�����֐��BVoice�𔭉�������
	void start(int channel, int noteNo, float velocity);
	
	// MIDI�m�[�g�I�t�̂Ƃ��ɌĂяo�����֐��BVoice�𔭉�������
	void stop();

	// Voice���̃I�V���[�^�[�ƃG���x���[�v�W�F�l���[�^��Ԃ��X�V����֐��B
	void update();

	// �I�V���[�^�[�ƃG���x���[�v�W�F�l���[�^����Voice�̐U���l���v�Z���ĕԂ��֐��B
	float process();

	// �s�b�`�x���h�̑�����I�V���[�^�ɔ��f������֐�
	void setPitchBend(float value);

	// �T�X�e�C���y�_���̏�Ԃ𑀍�E�擾����֐�
	void setSusPedal(bool state) { suspedal_cvoice = state; }
	bool getSusPedal() { return suspedal_cvoice; }

	// Voice�̏�Ԃ┭�����̃L�[�̒l��Ԃ��֐�
	int getState();
	int getKey();

	// waveformtype��ݒ肷��֐�
	void setWaveformType(int tag, float value);

	//ADSR�ݒ�
	void setADSR(int tag, float value);
};
