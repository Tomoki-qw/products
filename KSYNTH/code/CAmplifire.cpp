#include "CAmplifire.h"

CAmplifire::CAmplifire()
{
	key = 0;
	velo = 0.0;
	volume = 1.0;
}

void CAmplifire::start(int channel, int noteNo, float velocity) {
	key = noteNo;
	velo = velocity;
	//����(Hz)���v�Z
	float pitch = (float)(440.0 * pow(2.0, (double)(key - (69.0)) / 12.0));
	//�g�`�Đ��ƃG���x���[�v�W�F�l���[�^�̓�����J�n
	vco.start(pitch);
	eg.start();
	fg.start();

}

void CAmplifire::stop() {
	//�I�V���[�^�ƃG���x���[�v�W�F�l���[�^�̓�����~(RELEASE��ԂɈڍs)
	vco.stop();
	eg.stop();
}

void CAmplifire::update() {
	//�I�V���[�^�ƃG���x���[�v�W�F�l���[�^�̓�����X�V
	vco.update();
	eg.update();
}
double CAmplifire::process() {
	//�I�V���[�^�̐U�����擾
	out = vco.process();

	//�x���V�e�B�ƃG���x���[�v�̒l���������킹��
	out = out * velo * (double)volume * eg.process();
	out = fg.process(out);
	//�v�Z���ꂽ�U���l��Ԃ�
	return out ;
}

void CAmplifire::setPitchBend(float value) {
	vco.setPitchBend(value);
}

void CAmplifire::setWaveformType(float value)
{
	vco.setWaveformType(value);
};
//ADSR�ݒ�
void CAmplifire::setADSR(int tag, float value) {
	switch (tag) {
		case ADSR_OSC1_A:
		case ADSR_OSC2_A:
		case ADSR_OSC3_A:
			eg.setA(value);
			break;
		case ADSR_OSC1_D:
		case ADSR_OSC2_D:
		case ADSR_OSC3_D:
			eg.setD(value);
			break;
		case ADSR_OSC1_S:
		case ADSR_OSC2_S:
		case ADSR_OSC3_S:
			eg.setS(value);
			break;
		case ADSR_OSC1_R:
		case ADSR_OSC2_R:
		case ADSR_OSC3_R:
			eg.setR(value);
			break;
	}
};

double CAmplifire::process_FM(double modulator) {
	double out = 0.0;
	//�I�V���[�^�̐U�����擾
	out = vco.process_FM(modulator);

	//�x���V�e�B�ƃG���x���[�v�̒l���������킹��
	out = out * velo  * volume * eg.process();

	//�v�Z���ꂽ�U���l��Ԃ�
	return out;
}

void CAmplifire::setVolume(float value) {
	volume = value;
}

void CAmplifire::setModCoarse(float value) {
	vco.setModCoarse(value);
}

void CAmplifire::setModOct(float value) {
	vco.setModOct(value);
}

void CAmplifire::setFilterFreq(float value) {
	fg.setFreq(value);
}

void CAmplifire::setFilterQ(float value) {
	fg.setQ(value);
}

void CAmplifire::setFilterType(float type) {
	fg.setType(type);
}

void CAmplifire::setFilterGain(float value) {
	fg.setGain(value);
}