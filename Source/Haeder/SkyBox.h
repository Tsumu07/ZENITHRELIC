#pragma once
#include "../Haeder/Object.h"
#include "../Haeder/FSM.h"
#include "../Haeder/BoxModel.h"
#include "../Haeder/DxLibBox.h"
#include "SceneManager.h"

class SkyBox : public Object
{
private:
	SceneName GetSceneName;
	VERTEX3DSHADER vertex[24];
	unsigned short index[36];
	int graph;  //テクスチャハンドル

	float width;
	float height;
	float depth;
	float rotationAngle; // 回転角度用

	std::string LoadBox;

public:
	SkyBox();   //コンストラクタ
	~SkyBox();  //デストラクタ

	void Initaliza() override;  //初期化
	void Update() override;     //更新
	void Draw() override;       //描画
	void Finaliza() override;   //終了処理
};