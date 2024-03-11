#include "distortion.h"

void distortion(float inL[], float inR[], float outL[], float outR[], int wavelength, float di_gain, float di_volume)
{
	// inL[]、inR[]、outL[]、outR[]はそれぞれ入力信号と出力信号のバッファ(左右)
	// wavelenghtはバッファのサイズ、サンプリング周波数は44100Hzとする

	// エフェクターのパラメーター
	float gain = di_gain; // 増幅量。10～300程度(dB換算で20dB～50dB程度)
	float volume = di_volume;   // 出力信号の音量。0.0～1.0の範囲

	// 内部変数
	CFilter highpassL, highpassR; // フィルタークラス(https://www.utsbox.com/?page_id=728 より)

	// 高音域のみ通す(低音域をカットする)フィルタ設定(左右分)
	// カットする周波数の目安は20Hz～300Hz程度
	// 増幅量が大きくなれば、カットオフ周波数も大きくするとよい
	//highpassL.HighPass(200.0f, 1.0f / sqrt(2.0f));
	//highpassR.HighPass(200.0f, 1.0f / sqrt(2.0f));

	
	// 入力信号にエフェクターを適用する
	for (int i = 0; i < wavelength; i++)
	{
		// 入力信号にフィルタを適用する
		//float tmpL = highpassL.process(inL[i]);
		float tmpL = inL[i];
		// 入力信号にゲインを掛けて増幅する
		tmpL = gain * tmpL;

		// 振幅の最大値(ここでは-1.0～1.0)を超えたものをクリッピングする
		if (tmpL > 1.0) { tmpL = 1.0; }
		if (tmpL < -1.0) { tmpL = -1.0; }

		// 右側の入力信号も同様に処理
		//float tmpR = highpassR.process(inR[i]);
		float tmpR = inR[i];
		tmpR = gain * tmpR;
		if (tmpR > 1.0) { tmpR = 1.0; }
		if (tmpR < -1.0) { tmpR = -1.0; }

		// 入力信号にフィルタをかける
		outL[i] = volume * tmpL;
		outR[i] = volume * tmpR;
	}
}