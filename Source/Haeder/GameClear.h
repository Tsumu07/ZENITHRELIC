#pragma once
#include "SceneBase.h"
#include "../Haeder/SkyBox.h"

class GameClear :public SceneBase
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

    float GameClearUIY;

    float ContinueUI;

    float TitleUI;

    float ExitUI;

    int GameClearUI[6];

    int ContinueSelectUI;
    int TitleSelectUI;
    int ExitSelectUI;

    int GameClearLogo;
    int SelectPictureR;
    int SelectPictureL;

    //------------//

    //セレクトの制限
    //右
    float MaxRight;

    //左
    float MaxLeft;

    //--------//

    //BGM
    int GameClearBGM;
    int ButtonMusic;

    bool InputJoycon;

    //合計金額
    int m_price;

public:
    GameClear();   //コンストラクタ
    ~GameClear();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

};