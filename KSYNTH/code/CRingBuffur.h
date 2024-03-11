#pragma once
#ifndef __RINGBUF__
#define __RINGBUF__

#include <string.h>
#include <iostream>

// リングバッファのサイズ
#define RB_SIZE (44100 * 4)

// ===================================================================================
// リングバッファクラス
// ===================================================================================
class CRingBuffur
{
private:
    int rpos; // 読み込み位置
    int wpos; // 書き込み位置

    float* buf; // 内部バッファ（ヒープに確保）

public:
    inline CRingBuffur();
    inline ~CRingBuffur(); // デストラクタ

    inline void SetInterval(int interval);
    inline float Read(int pos = 0);
    inline void Write(float in);
    inline void Update();
};

// コンストラクタ
CRingBuffur::CRingBuffur()
{
    rpos = 0;
    wpos = RB_SIZE / 2; // とりあえずバッファサイズの半分ぐらいにしておく
    buf = new float[RB_SIZE]; // ヒープ上に動的に確保
    memset(buf, 0, sizeof(float) * RB_SIZE);
}

// デストラクタ
CRingBuffur::~CRingBuffur()
{
    delete[] buf; // 割り当てられたメモリを解放
}

// 読み込み位置と書き込み位置の間隔を設定する関数
void CRingBuffur::SetInterval(int interval)
{
    interval = interval % RB_SIZE;
    if (interval <= 0) { interval = 1; }
    wpos = (rpos + interval) % RB_SIZE;
}

// 内部バッファの読み込み位置(rpos)のデータを読み込む関数
float CRingBuffur::Read(int pos)
{
    int tmp = rpos + pos;
    while (tmp < 0)
    {
        tmp += RB_SIZE;
    }
    tmp = tmp % RB_SIZE; // バッファサイズ以上にならないよう処理
    return buf[tmp];
}

// 内部バッファの書き込み位置(wpos)にデータを書き込む関数
void CRingBuffur::Write(float in)
{
    buf[wpos] = in;
}

// 内部バッファの読み込み位置(rpos)、書き込み位置(wpos)を一つ進める関数
void CRingBuffur::Update()
{
    rpos = (rpos + 1) % RB_SIZE;
    wpos = (wpos + 1) % RB_SIZE;
}

#endif // __RINGBUF__
