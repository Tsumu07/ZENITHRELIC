#pragma once
#include "../Header/SceneBase.h"
#include "DxLib.h"

class Inventory : public SceneBase
{
private:

    //---画像の読み込み---//
    int Background;
    int MenuBack;
    int ItemBack;
    int SelectpictureR_Handle;
    int SelectpictureL_Handle;
    int Slot_Handle;

    //---UI関係---//
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

    //---キー入力---//
    bool Menu;
    bool CloseMenu;
    bool Down;
    bool Up;
    bool Decide;
    bool Equipment_No0;
    bool Equipment_No1;

    bool InputJoycon;

    //---セレクトの制限---//
    //上
    float MaxUp;

    //下
    float MaxUnder;

    int cursor;

    //---合計金額---//
    int TotalAmount;

    //---メニュー画面の表示---//
    bool OpenMenu;

    //---BGM---/
    int CursorMusic;

    int m_explainFontHandle;

public:
    Inventory();   //コンストラクタ
    ~Inventory();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

};