#pragma once
#include "SceneBase.h"
#include "../Haeder/SkyBox.h"
#include "../Haeder/Player_UI.h"
#include "../Haeder/StartSubScene.h"
#include "../Haeder/GoalSubScene.h"

class Game : public SceneBase
{
private:
    SkyBox* m_skybox;
    Player_UI* m_player_ui;
    StartSubScene* m_startsubscene;
    GoalSubScene* m_goalsubscene;

    int m_shadowMap;
    int vshandle;
    int pshandle;
    int skyboxPShandle;
    int skyboxVShandle;

    //Inventoryの背景
    int width;
    int height;
    int handle;

    bool m_startSubSceneEnd;

    //SE
    int GameBGM;


public:
    Game();   //コンストラクタ
    ~Game();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

    bool IsStartSubSceneEnd();

};