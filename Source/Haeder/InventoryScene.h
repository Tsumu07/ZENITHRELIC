#pragma once
#include "../Haeder/SceneBase.h"
#include "DxLib.h"

class Inventory : public SceneBase
{
private:
    //右の頂点
    float TriangleLeftX;
    float TriangleLeftY;

    //下の頂点
    float TriangleUnderX;
    float TriangleUnderY;

    //上の頂点
    float TriangleUpX;
    float TriangleUpY;

    //セレクトの制限
    //上
    float MaxUp;

    //下
    float MaxUnder;

    int cursor;

    //合計金額
    int TotalAmount;

    bool InputJoycon;


public:
    Inventory();   //コンストラクタ
    ~Inventory();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

    //合計金額の設定
    void SetTotalAmount(int total) { TotalAmount = total; }

    //合計金額の取得
    int GetTotalAmount()const { return TotalAmount; }

};

// 共通インスタンスを宣言（extern）
extern Inventory g_inventory;