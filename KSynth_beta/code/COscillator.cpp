#include "COscillator.h"

COscillator::COscillator()
{
	key = 0;
	velo = 0.0f;
	
}

void COscillator::start(int channel, int noteNo, float velocity) {
	key = noteNo;
	velo = velocity;
	//音程(Hz)を計算
	float pitch = (float)(440.0 * pow(2.0, (double)(key - (69.0)) / 12.0));
	//波形再生とエンベロープジェネレータの動作を開始
	wave.start(pitch);
	vca.start();
}

void COscillator::stop() {
	//オシレータとエンベロープジェネレータの動作を停止(RELEASE状態に移行)
	wave.stop();
	vca.stop();
}

void COscillator::update() {
	//オシレータとエンベロープジェネレータの動作を更新
	wave.update();
	vca.update();
}
float COscillator::process() {
	float out = 0.0f;
	//オシレータの振幅を取得
	out = wave.process();

	//ベロシティとエンベロープの値をかけ合わせる
	out = out * velo * vca.process();

	//計算された振幅値を返す
	return out;
}

void COscillator::setPitchBend(float value) {
	wave.setPitchBend(value);
}

void COscillator::setWaveformType(float value)
{
	wave.setWaveformType(value);
};
//ADSR設定
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