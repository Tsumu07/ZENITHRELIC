#pragma once
#include "SceneBase.h"

class LoadingScreen :public SceneBase
{
public:
    LoadingScreen();   //コンストラクタ
    ~LoadingScreen();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

private:

    bool LoadingNow;

};