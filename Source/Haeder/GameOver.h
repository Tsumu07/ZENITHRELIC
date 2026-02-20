#pragma once
#include "SceneBase.h"
#include "../Haeder/SkyBox.h"

class GameOver :public SceneBase
{
private:

    //SkyBox関係
    SkyBox* m_skybox;
    int skyboxPShandle;
    int skyboxVShandle;

    //---UI関係---//
    float SelectpictureR;
    float SelectpictureL;
    float SelectY;

    float LogoX;
    float LogoY;

    float GameOverUIY;

    float RetryUI;

    float TitleUI;

    float ExitUI;

    int GameOverUI[6];

    int RetrySelectUI;
    int TitleSelectUI;
    int ExitSelectUI;

    //------------//

    //セレクトの制限
    //右
    float MaxRight;

    //左
    float MaxLeft;

    //--------//

    //BGM
    int GameOverBGM;
    int ButtonMusic;

    bool InputJoycon;

public:
    GameOver();   //コンストラクタ
    ~GameOver();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理


};