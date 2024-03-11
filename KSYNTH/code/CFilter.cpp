#pragma once
#include <math.h>
#include "CFilter.h"
// --------------------------------------------------------------------------------
// �R���X�g���N�^
// --------------------------------------------------------------------------------
CFilter::CFilter()
{
	// �����o�[�ϐ���������
	a0 = 1.0f; // 0�ȊO�ɂ��Ă����Ȃ��Ə��Z�ŃG���[�ɂȂ�
	a1 = 0.0f;
	a2 = 0.0f;
	b0 = 1.0f;
	b1 = 0.0f;
	b2 = 0.0f;

	in1 = 0.0f;
	in2 = 0.0f;

	out1 = 0.0f;
	out2 = 0.0f;
	freq = 20000.0f;
	q = 1.0f;
	type = 0.0f;
	gain = 0.0f;
}

void CFilter::start() {
	calcFilter(type, freq, q, gain);
}

void CFilter::stop() {

}

void CFilter::update() {

}



float CFilter::pinknoise(float in) {
	const int m = 16;
	float z[m];
	float k[m];
	//init_pink
	for (int i = 0; i < m; i++)
		z[i] = 0;
	k[m - 1] = 0.5;
	for (int i = m - 1; i > 0; i--)
		k[i - 1] = k[i] * (float)0.25;
	//filter
	static float   t = 0.0;
	float          q;
	q = in;
	for (int i = 0; i < m; i++) {
		z[i] = (q * k[i] + z[i] * ((float)1.0 - k[i]));
		q = (q + z[i]) * (float)0.5;
	}
	float out = (float)0.75 * q + (float)0.25 * t; /* add 1st order LPF */
	return out;
}

// --------------------------------------------------------------------------------
// ���͐M���Ƀt�B���^��K�p����֐�
// --------------------------------------------------------------------------------
float CFilter::process(float in)
{
	// ���͐M���Ƀt�B���^��K�p���A�o�͐M���ϐ��ɕۑ��B
	float out = b0 / a0 * in + b1 / a0 * in1 + b2 / a0 * in2
		- a1 / a0 * out1 - a2 / a0 * out2;

	in2 = in1; // 2�O�̓��͐M�����X�V
	in1 = in;  // 1�O�̓��͐M�����X�V

	out2 = out1; // 2�O�̏o�͐M�����X�V
	out1 = out;  // 1�O�̏o�͐M�����X�V

	// �o�͐M����Ԃ�
	return out;
}


void CFilter::setFreq(float value) {
	freq = 20.0f * pow((15000.0f / 20.0f), value);
	calcFilter(type, freq, q, gain);	
}

void CFilter::setQ(float value) {
	q = 0.1f * pow((18.0f / 0.1f), value);
	calcFilter(type, freq, q, gain);
}

void CFilter::setType(float value) {
	type = value;
	calcFilter(type, freq, q, gain);
}

void CFilter::setGain(float value) {
	gain = value * 30.0f - 15.0f;//-15db����15db
	calcFilter(type, freq, q, gain);
}


void CFilter::calcFilter(float type, float freq, float q, float gain) {
	
	if( type == 0.0f){LowPass(freq, q);}
	else if (type == 0.125f) { LowPass(freq, q); }
	else if (type == 0.25f) {HighPass(freq, q);}
	else if (type == 0.375f){BandPass(freq, q);}
	else if (type == 0.5f){Notch(freq, q);}
	else if (type == 0.675f){LowShelf(freq, q, gain); }
	else if (type == 0.75f){HighShelf(freq, q, gain); }
	else if (type == 0.875f){Peaking(freq, q, gain); }
	else {AllPass(freq, q); }
	
}
// --------------------------------------------------------------------------------
// �t�B���^�W�����v�Z���郁���o�[�֐�
// --------------------------------------------------------------------------------
void CFilter::LowPass(float freq, float q, float samplerate)
{
	// �t�B���^�W���v�Z�Ŏg�p���钆�Ԓl�����߂�B
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	// �t�B���^�W�������߂�B
	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = (1.0f - cos(omega)) / 2.0f;
	b1 = 1.0f - cos(omega);
	b2 = (1.0f - cos(omega)) / 2.0f;
}

void CFilter::HighPass(float freq, float q, float samplerate)
{
	// �t�B���^�W���v�Z�Ŏg�p���钆�Ԓl�����߂�B
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	// �t�B���^�W�������߂�B
	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = (1.0f + cos(omega)) / 2.0f;
	b1 = -(1.0f + cos(omega));
	b2 = (1.0f + cos(omega)) / 2.0f;
}

void CFilter::BandPass(float freq, float bw, float samplerate)
{
	// �t�B���^�W���v�Z�Ŏg�p���钆�Ԓl�����߂�B
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));

	// �t�B���^�W�������߂�B
	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = alpha;
	b1 = 0.0f;
	b2 = -alpha;
}

void CFilter::Notch(float freq, float bw, float samplerate)
{
	// �t�B���^�W���v�Z�Ŏg�p���钆�Ԓl�����߂�B
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));

	// �t�B���^�W�������߂�B
	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = 1.0f;
	b1 = -2.0f * cos(omega);
	b2 = 1.0f;
}

void CFilter::LowShelf(float freq, float q, float gain, float samplerate)
{
	// �t�B���^�W���v�Z�Ŏg�p���钆�Ԓl�����߂�B
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);
	float A = pow(10.0f, (gain / 40.0f));
	float beta = sqrt(A) / q;

	// �t�B���^�W�������߂�B
	a0 = (A + 1.0f) + (A - 1.0f) * cos(omega) + beta * sin(omega);
	a1 = -2.0f * ((A - 1.0f) + (A + 1.0f) * cos(omega));
	a2 = (A + 1.0f) + (A - 1.0f) * cos(omega) - beta * sin(omega);
	b0 = A * ((A + 1.0f) - (A - 1.0f) * cos(omega) + beta * sin(omega));
	b1 = 2.0f * A * ((A - 1.0f) - (A + 1.0f) * cos(omega));
	b2 = A * ((A + 1.0f) - (A - 1.0f) * cos(omega) - beta * sin(omega));
}

void CFilter::HighShelf(float freq, float q, float gain, float samplerate)
{
	// �t�B���^�W���v�Z�Ŏg�p���钆�Ԓl�����߂�B
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);
	float A = pow(10.0f, (gain / 40.0f));
	float beta = sqrt(A) / q;

	// �t�B���^�W�������߂�B
	a0 = (A + 1.0f) - (A - 1.0f) * cos(omega) + beta * sin(omega);
	a1 = 2.0f * ((A - 1.0f) - (A + 1.0f) * cos(omega));
	a2 = (A + 1.0f) - (A - 1.0f) * cos(omega) - beta * sin(omega);
	b0 = A * ((A + 1.0f) + (A - 1.0f) * cos(omega) + beta * sin(omega));
	b1 = -2.0f * A * ((A - 1.0f) + (A + 1.0f) * cos(omega));
	b2 = A * ((A + 1.0f) + (A - 1.0f) * cos(omega) - beta * sin(omega));
}


void CFilter::Peaking(float freq, float bw, float gain, float samplerate)
{
	// �t�B���^�W���v�Z�Ŏg�p���钆�Ԓl�����߂�B
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) * sinh(log(2.0f) / 2.0 * bw * omega / sin(omega));
	float A = pow(10.0f, (gain / 40.0f));

	// �t�B���^�W�������߂�B
	a0 = 1.0f + alpha / A;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha / A;
	b0 = 1.0f + alpha * A;
	b1 = -2.0f * cos(omega);
	b2 = 1.0f - alpha * A;
}

void CFilter::AllPass(float freq, float q, float samplerate)
{
	// �t�B���^�W���v�Z�Ŏg�p���钆�Ԓl�����߂�B
	float omega = 2.0f * 3.14159265f * freq / samplerate;
	float alpha = sin(omega) / (2.0f * q);

	// �t�B���^�W�������߂�B
	a0 = 1.0f + alpha;
	a1 = -2.0f * cos(omega);
	a2 = 1.0f - alpha;
	b0 = 1.0f - alpha;
	b1 = -2.0f * cos(omega);
	b2 = 1.0f + alpha;
}