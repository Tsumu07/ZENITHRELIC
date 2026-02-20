#pragma once
#include "SceneBase.h"
#include "../Haeder/SkyBox.h"
#include "../Haeder/Player_UI.h"

class Game :public SceneBase
{
private:
    SkyBox* m_skybox;
    Player_UI* m_player_ui;

    int m_shadowMap;
    int vshandle;
    int pshandle;
    int skyboxPShandle;
    int skyboxVShandle;

public:
    Game();   //コンストラクタ
    ~Game();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理


};