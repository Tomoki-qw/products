#include "CAmplifire.h"

CAmplifire::CAmplifire()
{
	key = 0;
	velo = 0.0f;
	volume = 1.0f;
}

void CAmplifire::start(int channel, int noteNo, float velocity) {
	key = noteNo;
	velo = velocity;
	//音程(Hz)を計算
	float pitch = (float)(440.0 * pow(2.0, (double)(key - (69.0)) / 12.0));
	//波形再生とエンベロープジェネレータの動作を開始
	vco.start(pitch);
	eg.start();
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
float CAmplifire::process() {
	float out = 0.0f;
	//オシレータの振幅を取得
	out = vco.process();

	//ベロシティとエンベロープの値をかけ合わせる
	out = out * velo * volume * eg.process();

	//計算された振幅値を返す
	return out;
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
			eg.setA(value);
			break;
		case ADSR_OSC1_D:
		case ADSR_OSC2_D:
			eg.setD(value);
			break;
		case ADSR_OSC1_S:
		case ADSR_OSC2_S:
			eg.setS(value);
			break;
		case ADSR_OSC1_R:
		case ADSR_OSC2_R:
			eg.setR(value);
			break;
	}
};

float CAmplifire::process_FM(float modulator) {
	float out = 0.0f;
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