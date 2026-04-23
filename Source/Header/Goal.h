#pragma once
#include "Object.h"
#include <DxLib.h>

class Goal : public Object
{
private:
    int mnGoalModelHandle;   //読み込んだアイテムのモデルハンドル

    VECTOR mvGoalRotation;   //アイテムの回転

public:

    Goal();   //コンストラクタ
    ~Goal();  //デストラクタ

    void Initaliza(); //初期化
    void Update();    //更新
    void Draw();      //描画
    void Finaliza();  //終了処理

    //回転
    void SetRotation(float RX, float RY, float RZ) { mvGoalRotation = VGet(RX, RY, RZ); }

    //モデルの取得
    int mnGoal() { return mnGoalModelHandle; }


};