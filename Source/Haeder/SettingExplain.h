#pragma once
#include "../Haeder/SceneBase.h"

class SettingExplain : public SceneBase
{
public:
	SettingExplain();  //コンストラクタ
	~SettingExplain(); //デストラクタ

	void Initaliza();  //初期化
	void Update();     //更新
	void Draw();       //描画
	void Finaliza();   //終了処理

private:

};