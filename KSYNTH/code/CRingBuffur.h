#pragma once
#ifndef __RINGBUF__
#define __RINGBUF__

#include <string.h>
#include <iostream>

// �����O�o�b�t�@�̃T�C�Y
#define RB_SIZE (44100 * 4)

// ===================================================================================
// �����O�o�b�t�@�N���X
// ===================================================================================
class CRingBuffur
{
private:
    int rpos; // �ǂݍ��݈ʒu
    int wpos; // �������݈ʒu

    float* buf; // �����o�b�t�@�i�q�[�v�Ɋm�ہj

public:
    inline CRingBuffur();
    inline ~CRingBuffur(); // �f�X�g���N�^

    inline void SetInterval(int interval);
    inline float Read(int pos = 0);
    inline void Write(float in);
    inline void Update();
};

// �R���X�g���N�^
CRingBuffur::CRingBuffur()
{
    rpos = 0;
    wpos = RB_SIZE / 2; // �Ƃ肠�����o�b�t�@�T�C�Y�̔������炢�ɂ��Ă���
    buf = new float[RB_SIZE]; // �q�[�v��ɓ��I�Ɋm��
    memset(buf, 0, sizeof(float) * RB_SIZE);
}

// �f�X�g���N�^
CRingBuffur::~CRingBuffur()
{
    delete[] buf; // ���蓖�Ă�ꂽ�����������
}

// �ǂݍ��݈ʒu�Ə������݈ʒu�̊Ԋu��ݒ肷��֐�
void CRingBuffur::SetInterval(int interval)
{
    interval = interval % RB_SIZE;
    if (interval <= 0) { interval = 1; }
    wpos = (rpos + interval) % RB_SIZE;
}

// �����o�b�t�@�̓ǂݍ��݈ʒu(rpos)�̃f�[�^��ǂݍ��ފ֐�
float CRingBuffur::Read(int pos)
{
    int tmp = rpos + pos;
    while (tmp < 0)
    {
        tmp += RB_SIZE;
    }
    tmp = tmp % RB_SIZE; // �o�b�t�@�T�C�Y�ȏ�ɂȂ�Ȃ��悤����
    return buf[tmp];
}

// �����o�b�t�@�̏������݈ʒu(wpos)�Ƀf�[�^���������ފ֐�
void CRingBuffur::Write(float in)
{
    buf[wpos] = in;
}

// �����o�b�t�@�̓ǂݍ��݈ʒu(rpos)�A�������݈ʒu(wpos)����i�߂�֐�
void CRingBuffur::Update()
{
    rpos = (rpos + 1) % RB_SIZE;
    wpos = (wpos + 1) % RB_SIZE;
}

#endif // __RINGBUF__
