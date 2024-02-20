#include "COscillator.h"

COscillator::COscillator()
{
	key = 0;
	velo = 0.0f;
	
}

void COscillator::start(int channel, int noteNo, float velocity) {
	key = noteNo;
	velo = velocity;
	//����(Hz)���v�Z
	float pitch = (float)(440.0 * pow(2.0, (double)(key - (69.0)) / 12.0));
	//�g�`�Đ��ƃG���x���[�v�W�F�l���[�^�̓�����J�n
	wave.start(pitch);
	vca.start();
}

void COscillator::stop() {
	//�I�V���[�^�ƃG���x���[�v�W�F�l���[�^�̓�����~(RELEASE��ԂɈڍs)
	wave.stop();
	vca.stop();
}

void COscillator::update() {
	//�I�V���[�^�ƃG���x���[�v�W�F�l���[�^�̓�����X�V
	wave.update();
	vca.update();
}
float COscillator::process() {
	float out = 0.0f;
	//�I�V���[�^�̐U�����擾
	out = wave.process();

	//�x���V�e�B�ƃG���x���[�v�̒l���������킹��
	out = out * velo * vca.process();

	//�v�Z���ꂽ�U���l��Ԃ�
	return out;
}

void COscillator::setPitchBend(float value) {
	wave.setPitchBend(value);
}

void COscillator::setWaveformType(float value)
{
	wave.setWaveformType(value);
};
//ADSR�ݒ�
void COscillator::setADSR(int tag, float value) {
	switch (tag) {
		case ADSR_OSC1_A:
		case ADSR_OSC2_A:
			vca.setA(value);
			break;
		case ADSR_OSC1_D:
		case ADSR_OSC2_D:
			vca.setD(value);
			break;
		case ADSR_OSC1_S:
		case ADSR_OSC2_S:
			vca.setS(value);
			break;
		case ADSR_OSC1_R:
		case ADSR_OSC2_R:
			vca.setR(value);
			break;
	}
};