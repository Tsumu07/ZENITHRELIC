#include "../Haeder/Field.h"
#include "DxLib.h"

Field::Field()
: Object()
,TopLeft(VGet(0.0f,0.0f,0.0f))
,diameter(0.0f)
,floorhandle(0.0f)
,floornormalhandle(0.0f)
,mVertex()
{

}

Field::~Field()
{

}

void Field::Initaliza()
{

	floorhandle = LoadGraph("Assets/floor_No2.png");
	//floornormalhandle = LoadGraph("Assets/NomalMap_floor.png");

    SetTextureAddressModeUV(DX_TEXADDRESS_WRAP, DX_TEXADDRESS_WRAP);

    const float MAP_SIZE = 7000;

    const float TEX_WORLD_W = 674.0f;
    const float TEX_WORLD_D = 367.0f;

    // 左上の位置
    TopLeft = VGet(-MAP_SIZE * 0.5f, 0.0f, MAP_SIZE * 0.5f);
    diameter = MAP_SIZE;

    const float U_MAX = MAP_SIZE / TEX_WORLD_W;
    const float V_MAX = MAP_SIZE / TEX_WORLD_D;

    // 左上
    mVertex[0].pos = VGet(TopLeft.x, TopLeft.y, TopLeft.z);
    mVertex[0].norm = VGet(0.0f, 1.0f, 0.0f);
    mVertex[0].dif = GetColorU8(255, 255, 255, 255);
    mVertex[0].spc = GetColorU8(0, 0, 0, 0);
    mVertex[0].u = 0.0f;
    mVertex[0].v = 0.0f;
    mVertex[0].su = 0.0f;
    mVertex[0].sv = 0.0f;

    // 右上
    mVertex[1].pos = VGet(TopLeft.x + diameter, TopLeft.y, TopLeft.z);
    mVertex[1].norm = VGet(0.0f, 1.0f, 0.0f);
    mVertex[1].dif = GetColorU8(255, 255, 255, 255);
    mVertex[1].spc = GetColorU8(0, 0, 0, 0);
    mVertex[1].u = U_MAX;
    mVertex[1].v = 0.0f;
    mVertex[1].su = U_MAX;
    mVertex[1].sv = 0.0f;

    // 左下
    mVertex[2].pos = VGet(TopLeft.x, TopLeft.y, TopLeft.z - diameter);
    mVertex[2].norm = VGet(0.0f, 1.0f, 0.0f);
    mVertex[2].dif = GetColorU8(255, 255, 255, 255);
    mVertex[2].spc = GetColorU8(0, 0, 0, 0);
    mVertex[2].u = 0.0f;
    mVertex[2].v = V_MAX;
    mVertex[2].su = 0.0f;
    mVertex[2].sv = V_MAX;

    // 右下
    mVertex[3].pos = VGet(TopLeft.x + diameter, TopLeft.y, TopLeft.z - diameter);
    mVertex[3].norm = VGet(0.0f, 1.0f, 0.0f);
    mVertex[3].dif = GetColorU8(255, 255, 255, 255);
    mVertex[3].spc = GetColorU8(0, 0, 0, 0);
    mVertex[3].u = U_MAX;
    mVertex[3].v = V_MAX;
    mVertex[3].su = U_MAX;
    mVertex[3].sv = V_MAX;
    //法線を求める
    VECTOR vec = VCross(VSub(mVertex[0].pos, mVertex[1].pos), VSub(mVertex[0].pos, mVertex[2].pos));
    mVertex[0].norm = VNorm(vec);
    mVertex[1].norm = mVertex[0].norm;
    mVertex[2].norm = mVertex[0].norm;
    mVertex[3].norm = mVertex[0].norm;

}

void Field::Update()
{

    return;
}

void Field::Draw()
{

    // 2ポリゴン分のインデックスデータをセット
    WORD index[6] = { 0,1,2,2,1,3 };

    if (m_team == 0)
    {
        // ２ポリゴンの描画
        DrawPolygonIndexed3D(mVertex, 4, index, 2, floorhandle, true);
    }

    else
    {
        VERTEX3DSHADER vertex[4];
        for (int i = 0; i < 4; i++)
        {
            vertex[i].pos = mVertex[i].pos;
            vertex[i].norm = mVertex[i].norm;
            vertex[i].dif = mVertex[i].dif;
            vertex[i].spc = mVertex[i].spc;
            vertex[i].u = mVertex[i].u;
            vertex[i].v = mVertex[i].v;
            vertex[i].su = mVertex[i].su;
            vertex[i].sv = mVertex[i].sv;
        }
        // 使用するテクスチャを０番にセット
        SetUseTextureToShader(0, floorhandle);
        SetUseTextureToShader(1, floornormalhandle);

        DrawPolygonIndexed3DToShader(vertex, 4, index, 2);

    }

}

void Field::Finaliza()
{
    DeleteGraph(floorhandle);
    DeleteGraph(floornormalhandle);
}
