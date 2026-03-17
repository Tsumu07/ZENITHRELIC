#pragma once
#include "SceneBase.h"
#include "../Haeder/SkyBox.h"

class GameOver :public SceneBase
{
private:

    //---SkyBox関係---//
    SkyBox* m_skybox;
    int skyboxPShandle;
    int skyboxVShandle;

    //---画像の読み込み---//
    int GameOverLogo_Handle;
    int SelectpictureR_Handle;
    int SelectpictureL_Handle;

    //---UI関係---//
    float SelectpictureR;
    float SelectpictureL;
    float SelectY;

    float LogoX;
    float LogoY;

    int GameOverUI[6];
    float GameOverUIY;

    float RetryUI;

    float TitleUI;

    float ExitUI;

    int RetrySelectUI;
    int TitleSelectUI;
    int ExitSelectUI;

    //---キー入力---//
    bool Right;
    bool Left;
    bool Decide;
    bool InputJoycon;

    //---セレクトの制限---//
    //右
    float MaxRight;

    //左
    float MaxLeft;

    //---BGM---/
    int GameOverBGM;
    int ButtonMusic;


public:
    GameOver();   //コンストラクタ
    ~GameOver();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理


};