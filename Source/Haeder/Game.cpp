#include "Dxlib.h"
#include "../Haeder/Game.h"
#include "../Haeder/SceneBase.h"
#include "../Haeder/SceneManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Camera.h"
#include "../Haeder/Player.h"
#include "../Haeder/Player_UI.h"
#include "../Master.h"
#include <EffekseerForDXLib.h>

//コンストラクタ
Game::Game()
:m_skybox()
,m_player_ui()
,m_shadowMap(-1)
,vshandle(-1)
,pshandle(-1)
,skyboxPShandle(-1)
,skyboxVShandle(-1)
{

}

//デストラクタ
Game::~Game()
{

}

//初期化
void Game::Initaliza()
{

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
        m_player_ui->SetLayer(1);
        m_player_ui->SetTag(10);
        m_player_ui->SetPos(VGet(0.0f, 0.0f, 0.0f));
        m_player_ui->SetDir(VGet(1.0f, 0.0f, 0.0f));
        m_player_ui->SetSpeed(0.0f);
        m_player_ui->SetTeam(1);

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

}

//更新
void Game::Update()
{

    Master::mpGameManager->Update();
    m_skybox->Update();
    m_player_ui->Update();

    static int shotCount = 0;

    ////スクショ
    //if (CheckHitPillar(Pillar_INPUT_E))
    //{
    //    char filename[64];
    //    sprintf_s(filename, "screenshot_%03d.png", shotCount++);
    //    SaveDrawScreen(0, 0, 1920, 1080, filename);
    //}
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

    //UI
    m_player_ui->Draw();

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

}