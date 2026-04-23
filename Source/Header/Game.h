#pragma once
#include "SceneBase.h"
#include "../Header/SkyBox.h"
#include "../Header/Player_UI.h"
#include "../Header/StartSubScene.h"
#include "../Header/GoalSubScene.h"

class Game : public SceneBase
{
private:

    //---SkyBox関係---//
    SkyBox* m_skybox;
    int SkyboxPShandle;
    int SkyboxVShandle;

    Player_UI* m_player_ui;
    StartSubScene* m_startsubscene;
    GoalSubScene* m_goalsubscene;

    int m_shadowMap;
    int vshandle;
    int pshandle;

    //---Inventoryの背景---//
    int width;
    int height;
    int handle;

    bool m_startSubSceneEnd;

    //---BGM---/
    int GameBGM;
    int InventorySE;

    //---キー入力---//
    bool InventoryFlag;

public:
    Game();   //コンストラクタ
    ~Game();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

    bool IsStartSubSceneEnd();

};