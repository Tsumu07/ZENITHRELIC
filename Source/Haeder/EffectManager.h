#pragma once
#include <DxLib.h>

class EffectManager
{
public:
    EffectManager();   //コンストラクタ
    ~EffectManager();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

private:

    //画像の読み込み
    int LoadAnimetionGraph;


};
