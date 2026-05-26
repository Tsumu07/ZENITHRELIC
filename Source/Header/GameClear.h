#pragma once
#include "SceneBase.h"
#include "../Header/SkyBox.h"

class GameClear :public SceneBase
{
private:

    //---SkyBox関係---//
    SkyBox* m_skybox;
    int skyboxPShandle;
    int skyboxVShandle;

    int m_explainFontHandle;

    //---UI関係---//
    float SelectpictureR;
    float SelectpictureL;
    float SelectY;

    float LogoX;
    float LogoY;

    float GameClearUIY;
    int GameClearUI[6];

    float ContinueUI;

    float TitleUI;

    float ExitUI;

    int ContinueSelectUI;
    int TitleSelectUI;
    int ExitSelectUI;

    int GameClearLogo;
    int SelectPictureR;
    int SelectPictureL;

    //---キー入力---//
    bool Right;
    bool Left;
    bool Decide;

    //セレクトの制限
    //右
    float MaxRight;

    //左
    float MaxLeft;

    //---BGM---/
    int GameClearBGM;
    int ButtonMusic;

    bool InputJoycon;

    //---合計金額---//
    int m_price;

public:
    GameClear();   //コンストラクタ
    ~GameClear();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

};