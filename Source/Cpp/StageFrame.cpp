#include "DxLib.h"
#include "../Haeder/StageFrame.h"

//枠
StageFrame::StageFrame(VECTOR  position, VECTOR topLeft, VECTOR bottomRigh)
    : Object()
{

    //左上
    //pos = ポジション 
    //norm = ホース
    //u = y
    mvertex[0].pos = VAdd(position, topLeft);
    mvertex[0].u = 0.0f;
    mvertex[0].v = 0.0f;
    //法線ベクトル↓
    mvertex[0].norm = VGet(-1.0f, 0.0f, 0.0f);
    mvertex[0].dif = GetColorU8(255, 255, 255, 255);
    mvertex[0].spc = GetColorU8(0, 0, 0, 0);
    mvertex[0].su = 0.0f;
    mvertex[0].sv = 0.0f;

    //右上
    mvertex[1].pos = VAdd(position, VGet(bottomRigh.x, topLeft.y, bottomRigh.z));
    mvertex[1].u = 1.0f;
    mvertex[1].v = 0.0f;
    //法線ベクトル↓
    mvertex[1].norm = VGet(-1.0f, 0.0f, 0.0f);
    mvertex[1].dif = GetColorU8(255, 255, 255, 255);
    mvertex[1].spc = GetColorU8(0, 0, 0, 0);
    mvertex[1].su = 1.0f;
    mvertex[1].sv = 0.0f;

    //左下
    mvertex[2].pos = VAdd(position, VGet(topLeft.x, bottomRigh.y, topLeft.z));
    mvertex[2].u = 0.0f;
    mvertex[2].v = 1.0f;
    //法線ベクトル↓
    mvertex[2].norm = VGet(-1.0f, 0.0f, 0.0f);
    mvertex[2].dif = GetColorU8(255, 255, 255, 255);
    mvertex[2].spc = GetColorU8(0, 0, 0, 0);
    mvertex[2].su = 0.0f;
    mvertex[2].sv = 1.0f;

    //右下
    mvertex[3].pos = VAdd(position, bottomRigh);
    mvertex[3].u = 1.0f;
    mvertex[3].v = 1.0f;
    //法線ベクトル↓
    mvertex[3].norm = VGet(0.0f, 0.0f, -1.0f);
    mvertex[3].dif = GetColorU8(255, 255, 255, 255);
    mvertex[3].spc = GetColorU8(0, 0, 0, 0);
    mvertex[3].su = 1.0f;
    mvertex[3].sv = 1.0f;

    //法線を求める
    VECTOR vec = VCross(VSub(mvertex[0].pos, mvertex[1].pos), VSub(mvertex[0].pos, mvertex[2].pos));
    mvertex[0].norm = VNorm(vec);
    mvertex[1].norm = mvertex[0].norm;
    mvertex[2].norm = mvertex[0].norm;
    mvertex[3].norm = mvertex[0].norm;


}


StageFrame::~StageFrame()
{
}


void StageFrame::Initaliza()
{
}

void StageFrame::Update()
{
}

void StageFrame::Draw()
{
    // 4頂点分のデータをセット
    WORD index[6];

    //2ポリゴン分のインデックスデータをセット
    index[0] = 0;
    index[1] = 1;
    index[2] = 2;
    index[3] = 3;
    index[4] = 2;
    index[5] = 1;

    SetUseLighting(false);

    SetUseLighting(true);

}

void StageFrame::Finaliza()
{
}
