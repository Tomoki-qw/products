#include "distortion.h"

void distortion(float inL[], float inR[], float outL[], float outR[], int wavelength, float di_gain, float di_volume)
{
	// inL[]�AinR[]�AoutL[]�AoutR[]�͂��ꂼ����͐M���Əo�͐M���̃o�b�t�@(���E)
	// wavelenght�̓o�b�t�@�̃T�C�Y�A�T���v�����O���g����44100Hz�Ƃ���

	// �G�t�F�N�^�[�̃p�����[�^�[
	float gain = di_gain; // �����ʁB10�`300���x(dB���Z��20dB�`50dB���x)
	float volume = di_volume;   // �o�͐M���̉��ʁB0.0�`1.0�͈̔�

	// �����ϐ�
	CFilter highpassL, highpassR; // �t�B���^�[�N���X(https://www.utsbox.com/?page_id=728 ���)

	// ������̂ݒʂ�(�ቹ����J�b�g����)�t�B���^�ݒ�(���E��)
	// �J�b�g������g���̖ڈ���20Hz�`300Hz���x
	// �����ʂ��傫���Ȃ�΁A�J�b�g�I�t���g�����傫������Ƃ悢
	//highpassL.HighPass(200.0f, 1.0f / sqrt(2.0f));
	//highpassR.HighPass(200.0f, 1.0f / sqrt(2.0f));

	
	// ���͐M���ɃG�t�F�N�^�[��K�p����
	for (int i = 0; i < wavelength; i++)
	{
		// ���͐M���Ƀt�B���^��K�p����
		//float tmpL = highpassL.process(inL[i]);
		float tmpL = inL[i];
		// ���͐M���ɃQ�C�����|���đ�������
		tmpL = gain * tmpL;

		// �U���̍ő�l(�����ł�-1.0�`1.0)�𒴂������̂��N���b�s���O����
		if (tmpL > 1.0) { tmpL = 1.0; }
		if (tmpL < -1.0) { tmpL = -1.0; }

		// �E���̓��͐M�������l�ɏ���
		//float tmpR = highpassR.process(inR[i]);
		float tmpR = inR[i];
		tmpR = gain * tmpR;
		if (tmpR > 1.0) { tmpR = 1.0; }
		if (tmpR < -1.0) { tmpR = -1.0; }

		// ���͐M���Ƀt�B���^��������
		outL[i] = volume * tmpL;
		outR[i] = volume * tmpR;
	}
}