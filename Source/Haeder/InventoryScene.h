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

    //背景画像
    int Background;

    //メニューのUI
    int MenuUI[6];
    int RetrySelectUI;
    int TitleSelectUI;
    int ExitSelectUI;

    float MenuUIX;

    float RetryUI;

    float TitleUI;

    float ExitUI;

    float SelectpictureR;
    float SelectpictureL;
    float SelectY;

    bool InputJoycon;

    //メニュー画面の表示
    bool OpenMenu;

    //SE
    int CursorMusic;


public:
    Inventory();   //コンストラクタ
    ~Inventory();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

};