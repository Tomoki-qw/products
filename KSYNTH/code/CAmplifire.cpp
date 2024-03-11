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
	//音程(Hz)を計算
	float pitch = (float)(440.0 * pow(2.0, (double)(key - (69.0)) / 12.0));
	//波形再生とエンベロープジェネレータの動作を開始
	vco.start(pitch);
	eg.start();
	fg.start();

}

void CAmplifire::stop() {
	//オシレータとエンベロープジェネレータの動作を停止(RELEASE状態に移行)
	vco.stop();
	eg.stop();
}

void CAmplifire::update() {
	//オシレータとエンベロープジェネレータの動作を更新
	vco.update();
	eg.update();
}
double CAmplifire::process() {
	//オシレータの振幅を取得
	out = vco.process();

	//ベロシティとエンベロープの値をかけ合わせる
	out = out * velo * (double)volume * eg.process();
	out = fg.process(out);
	//計算された振幅値を返す
	return out ;
}

void CAmplifire::setPitchBend(float value) {
	vco.setPitchBend(value);
}

void CAmplifire::setWaveformType(float value)
{
	vco.setWaveformType(value);
};
//ADSR設定
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
	//オシレータの振幅を取得
	out = vco.process_FM(modulator);

	//ベロシティとエンベロープの値をかけ合わせる
	out = out * velo  * volume * eg.process();

	//計算された振幅値を返す
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