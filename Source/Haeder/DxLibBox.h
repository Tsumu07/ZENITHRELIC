#pragma once

#include "DxLib.h"
#include <string>

class DxLibBox
{
private:
	VERTEX3D vertex[24];
	unsigned short index[36];
	int graph; //テクスチャハンドル

	VECTOR pos;
	VECTOR rot;
	VECTOR scale;
	VECTOR offset;

	MATRIX world;
	MATRIX* parent;

public:
	DxLibBox();
	~DxLibBox();

	//                  幅          高さ　　      奥行   
	void Create(float width, float height, float depth);

	void SetPos(float x, float y, float z);
	void SetRot(float x, float y, float z);
	void SetRot(VECTOR r);
	void SetScale(float x, float y, float z);
	void SetOffset(float x, float y, float z);
	void SetParent(MATRIX* p);
	void SetTexture(std::string texName);
	MATRIX* GetMatrix(void);

	void SetUVFront(float u, float v, float uw, float vh);
	void SetUVBack(float u, float v, float uw, float vh);
	void SetUVUp(float u, float v, float uw, float vh);
	void SetUVBottom(float u, float v, float uw, float vh);
	void SetUVRight(float u, float v, float uw, float vh);
	void SetUVLeft(float u, float v, float uw, float vh);

	void Transform(void); //ワールド変換
	void Draw(void);      //描画
};