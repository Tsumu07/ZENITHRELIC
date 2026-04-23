#pragma once
#include "Object.h"
#include "DxLib.h"

class Field : public Object
{
private:
	VERTEX3D mVertex[4];   //頂点データ
	VECTOR TopLeft;        //左上座標
	int diameter;
	int floorhandle;       //画像
	int floornormalhandle; //法線マップ

public:
	Field();
	~Field();

	void Initaliza() override;
	void Update() override;
	void Draw() override;
	void Finaliza() override;

};