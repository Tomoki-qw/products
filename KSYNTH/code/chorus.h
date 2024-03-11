#pragma once

#include <math.h>

#include "CRingBuffur.h"

float chorus_mix = 0.5f;
float chorus_rate = 16.0f;
float chorus_depth = 200.0f;
float chorus_feedback = 0.8f;
bool isChorusOn = 0;
// ���`���
float lerp(float v1, float v2, float t)
{
	return (1.0f - t) * v1 + t * v2;
}

void chorus(float inL[], float inR[], float outL[], float outR[], int wavelength, float ch_mix, float ch_rate, float ch_depth, float ch_feedback)
{


	// �G�t�F�N�^�[�̃p�����[�^�[
	float mix = ch_mix; // �R�[���X�̂������B0.0�`1.0�̊�
	float rate = ch_rate; // �R�[���X�̗h�炬�̊Ԋu�B0Hz�`16Hz���x
	float depth = ch_depth; // �R�[���X�̗h�炬�̐[���B5.0�`200.0�T���v�����x
	float feedback = ch_feedback; // �R�[���X�̃t�B�[�h�o�b�N�ʁB0.0�`1.0�̊�

	// �����ϐ�
	CRingBuffur ringbufL, ringbufR; 

	// �f�B���C�^�C�����T���v�����ɕϊ����Đݒ�
	int delaysample = 1000;
	ringbufL.SetInterval(delaysample);
	ringbufR.SetInterval(delaysample);

	float theta = 0; // �f�B���C�ǂݍ��݈ʒu��h�炷���߂�sin�֐��̊p�x �ƁB�����l��0
	float speed = (2.0f * 3.14159265f * rate) / 44100.0f; // �h�炬�̃X�s�[�h�B�p���x�ւƓ����B

	// ���͐M���ɃR�[���X������
	for (int i = 0; i < wavelength; i++)
	{
		// �p�x�ƂɊp���x��������
		theta += speed;

		// �ǂݍ��݈ʒu��h�炷�ʂ��v�Z
		// sin()�֐��̌��ʂ�depth���|����
		float a = sin(theta) * depth;

		// �ǂݍ��݈ʒu��h�炵���ۂ̑O��̐����l���擾(���ƂŐ��`��Ԃ��邽��)
		int p1 = (int)a;
		int p2 = a + 1;

		// �O��̐����l����ǂݍ��݈ʒu�̒l����`��ԂŊ���o��
		float lerpL1 = lerp(ringbufL.Read(p1), ringbufL.Read(p2), a - (float)p1);
		float lerpR1 = lerp(ringbufR.Read(p1), ringbufR.Read(p2), a - (float)p1);



		// ���͐M���Ƀf�B���C�M����������
		float tmpL = (1.0f - mix) * inL[i] + mix * lerpL1;
		float tmpR = (1.0f - mix) * inR[i] + mix * lerpR1;

		// �f�B���C�M���Ƃ��ē��͐M���ƃt�B�[�h�o�b�N�M���������O�o�b�t�@�ɏ�������
		ringbufL.Write((1.0f - feedback) * inL[i] + feedback * tmpL);
		ringbufR.Write((1.0f - feedback) * inR[i] + feedback * tmpR);

		// �����O�o�b�t�@�̏�Ԃ��X�V����
		ringbufL.Update();
		ringbufR.Update();

		// �o�͐M���ɏ�������
		outL[i] = tmpL;
		outR[i] = tmpR;
	}
}