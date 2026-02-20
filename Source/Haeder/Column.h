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