#include "Dxlib.h"
#include "../Haeder/Game.h"
#include "../Haeder/SceneBase.h"
#include "../Haeder/SceneManager.h"
#include "../Haeder/StartSubScene.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Camera.h"
#include "../Haeder/Player.h"
#include "../Haeder/Player_UI.h"
#include "../Master.h"
#include "CheckKey.h"
#include <EffekseerForDXLib.h>

//コンストラクタ
Game::Game()
:m_skybox()
,m_player_ui()
,m_startsubscene()
,m_goalsubscene()
,m_shadowMap(-1)
,vshandle(-1)
,pshandle(-1)
,skyboxPShandle(-1)
,skyboxVShandle(-1)
,width(-1)
,height(-1)
,handle(-1)
,GameBGM(-1)
,InventorySE(-1)
,m_startSubSceneEnd(false)
{

}

//デストラクタ
Game::~Game()
{

}

//初期化
void Game::Initaliza()
{
    m_startSubSceneEnd = false;

    m_startsubscene = new StartSubScene();
    m_startsubscene->Initaliza();

    m_goalsubscene = nullptr;

    Master::mpGameManager->Initaliza();

    //スカイボックスのインスタンスを作成する
    {
        m_skybox = new SkyBox();
        m_skybox->Initaliza();
        m_skybox->SetLayer(1);
        m_skybox->SetTag(0);
        m_skybox->SetPos(VGet(0.0f, 0.0f, 0.0f));
        m_skybox->SetDir(VGet(1.0f, 0.0f, 0.0f));
        m_skybox->SetSpeed(0.0f);
        m_skybox->SetTeam(1);

    }

    //プレイヤーのUI
    {
        m_player_ui = new Player_UI();
        m_player_ui->Initaliza();
    }


    m_shadowMap = MakeShadowMap(8192, 8192);

    // シャドウマップが想定するライトの方向もセット
    SetShadowMapLightDirection(m_shadowMap, VNorm(VGet(1.0f, -1.0f, 1.0f)));

    ChangeLightTypeDir(VNorm(VGet(1.0f, -1.0f, 1.0f)));

    // シャドウマップに描画する範囲を設定
    SetShadowMapDrawArea(m_shadowMap, VGet(-8192.0f, 1000.0f, -8192.0f), VGet(8192.0f, -100.0f, 8192.0f));

    SetUseLighting(true);
    SetGlobalAmbientLight(GetColorF(0.7f, 0.7f, 0.7f, 1.0f));
    MATERIALPARAM material = {};
    material.Diffuse = GetColorF(1.0f, 1.0f, 1.0f, 1.0f);
    material.Ambient = GetColorF(0.6f, 0.6f, 0.6f, 1.0f);
    SetMaterialParam(material);

    //頂点シェーダーを読み込む
    vshandle = LoadVertexShader("DefaultVS.cso");

    //SkyBox用頂点シェーダを読み込む
    skyboxVShandle = LoadVertexShader("SkyBoxVS.cso");

    //ピクセルシェーダーを読み込む
    pshandle = LoadPixelShader("DefaultPS.cso");

    //SkyBox用ピクセルシェーダーを読み込む
    skyboxPShandle = LoadPixelShader("SkyBoxPS.cso");

    InventorySE = LoadSoundMem("Musics/OpenInventory.mp3");

    GameBGM = LoadSoundMem("Musics/Game.mp3");

    ChangeVolumeSoundMem(170, GameBGM);

    PlaySoundMem(GameBGM, DX_PLAYTYPE_LOOP);

}

//更新
void Game::Update()
{

    //ゴール
    Object* GetPlayer = Master::mpObjectManager->FindByTag(100);
    auto goal = dynamic_cast<Player*>(GetPlayer);


    if (m_startsubscene)
    {
        m_startsubscene->Update();

        if (m_startsubscene->IsEnd())
        {
            m_startsubscene->Finaliza();
            delete m_startsubscene;
            m_startsubscene = nullptr;
            m_startSubSceneEnd = true;
        }

        return; // 入力含め本編停止
    }

    if (m_goalsubscene)
    {
        m_goalsubscene->Update();
        return;
    }

    Master::mpGameManager->Update();
    m_skybox->Update();
    m_player_ui->Update();

    static int shotCount = 0;

    //アイテム画面
    if (CheckDownController(PAD_INPUT_3) != 0 || CheckDownKey(KEY_INPUT_E) != 0)
    {
        ChangeVolumeSoundMem(200, InventorySE);

        PlaySoundMem(InventorySE, DX_PLAYTYPE_BACK);

        GetDrawScreenSize(&width, &height);

        handle = MakeScreen(width, height);

        GetDrawScreenGraph(0, 0, width, height, handle);

        Master::mpSceneManager->SetLastGameScreen(handle);
        Master::mpSceneManager->OpenInventory();
    }

    //ゴールしたら
    if (goal->GetHitGoal() && m_goalsubscene == nullptr)
    {
        StopSoundMem(GameBGM);
        m_goalsubscene = new GoalSubScene();
        m_goalsubscene->Initaliza();
    }

}

//描画
void Game::Draw()
{    

    ShadowMap_DrawSetup(m_shadowMap);
    Master::mpGameManager->Draw();
    ShadowMap_DrawEnd();

    SetDrawScreen(DX_SCREEN_BACK);
    Master::mpObjectManager->RestoreViewMatrix();
    ClearDrawScreen();

    //シェーダーをセット
    SetUseVertexShader(vshandle);

    //影テクスチャをセット
    SetUseShadowMap(0, m_shadowMap);

    SetUsePixelShader(pshandle);

    //ゲーム描画
    Master::mpGameManager->Draw();

    SetUseVertexShader(skyboxVShandle);

    // 使用するピクセルシェーダーをセット
    SetUsePixelShader(skyboxPShandle);

    m_skybox->Draw();

    if (m_startsubscene)
    {
        m_startsubscene->Draw();

        return;
    }

    else
    {
        //UI
        m_player_ui->Draw();

    }

    if (m_goalsubscene)
    {
        m_goalsubscene->Draw();
    }


    // Effekseerエフェクトの描画
    DrawEffekseer3D();


    //終わったら解除
    SetUseVertexShader(-1);
    SetUsePixelShader(-1);
    SetUseShadowMap(0, -1);
    SetUseLighting(false);
    SetUseZBufferFlag(TRUE);
    SetWriteZBufferFlag(TRUE);
}

//終了処理
void Game::Finaliza()
{

    Master::mpGameManager->Finaliza();


    DeleteSoundMem(InventorySE);
    DeleteSoundMem(GameBGM);

}

bool Game::IsStartSubSceneEnd()
{
    return m_startSubSceneEnd;
}