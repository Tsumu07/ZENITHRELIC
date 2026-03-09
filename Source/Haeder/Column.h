#pragma once
#pragma once
#include "Object.h"
#include <DxLib.h>

class Column : public Object
{
private:

    int mnColumnModelHandle;   //読み込んだアイテムのモデルハンドル

    int ColumnRotationY;        //回転

    VECTOR mvColumnPosition;   //アイテムのポジション

    int DeleteColumnCount;  //崩れるまでのカウントダウン

    int ItemRandom;        //ランダムアイテム出現

    bool IsCylinder() const override { return true; }

    float m_deadTimer;        // 死亡演出用タイマー
    float m_startY;           // 開始Y座標保存
    bool  m_isDeadStarted;    // 演出開始フラグ
    VECTOR Deadpos;

    //SE
    int ColumnSE;

public:

    Column();   //コンストラクタ
    ~Column();  //デストラクタ

    void Initaliza(); //初期化
    void Update();    //更新
    void Draw();      //描画
    void Finaliza();  //終了処理

    //モデルの取得
    int ColumnItem() { return mnColumnModelHandle; }


};