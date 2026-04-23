#include "Dxlib.h"
#include "../Header/GameOver.h"
#include "../Header/SceneBase.h"
#include "../Header/SceneManager.h"
#include "../Header/GameManager.h"
#include "../Header/CheckKey.h"
#include "../Header/ObujectManager.h"
#include "../Master.h"

//コンストラクタ
GameOver::GameOver()
:SceneBase()
,m_skybox()
,skyboxPShandle(-1)
,skyboxVShandle(-1)
,GameOverLogo_Handle(-1)
,SelectpictureR_Handle(-1)
,SelectpictureL_Handle(-1)
,SelectpictureR(0.0f)
,SelectpictureL(0.0f)
,SelectY(0.0f)
,LogoX(0.0f)
,LogoY(0.0f)
,GameOverUI()
,GameOverUIY(0.0f)
,RetryUI(0.0f)
,TitleUI(0.0f)
,ExitUI(0.0f)
,RetrySelectUI(-1)
,TitleSelectUI(-1)
,ExitSelectUI(-1)
,Right(false)
,Left(false)
,Decide(false)
,InputJoycon(false)
,MaxRight(0.0f)
,MaxLeft(0.0f)
,ButtonMusic(-1)
,GameOverBGM(-1)
{
}

//デストラクタ
GameOver::~GameOver()
{
}

//初期化
void GameOver::Initaliza()
{
    SetCameraPositionAndTarget_UpVecY
    (
        VGet(0.0f, 100.0f, -200.0f),
        VGet(0.0f, 100.0f, 0.0f)
    );

    //カメラのクリッピング距離を設定　どこまで写すのか
    SetCameraNearFar(1.0f, 30000.0f);

    /////////サウンドの読み込み/////////
    //BGN
    GameOverBGM = LoadSoundMem("Musics/GameOver.mp3");

    //ボタン
    ButtonMusic = LoadSoundMem("Musics/poka01.mp3");

    //BGM再生
    PlaySoundMem(GameOverBGM, DX_PLAYTYPE_LOOP);

    LoadDivGraph("Assets/GameOverUI.png", 6, 2, 3, 320, 108, GameOverUI);
    GameOverLogo_Handle = LoadGraph("Assets/GameOver.png");
    SelectpictureR_Handle = LoadGraph("Assets/SelectpictureR.png");
    SelectpictureL_Handle = LoadGraph("Assets/SelectpictureL.png");

    //一瞬の取得
    InputJoycon = false;

    //一番右
    MaxRight = 1180.0f;

    //一番左
    MaxLeft = 40.0f;

    //UI
    LogoX = 300.0f;
    LogoY = 100.0f;
    GameOverUIY = 700.0f;
    RetryUI = 180.0f;
    TitleUI = 750.0f;
    ExitUI = 1320.0f;
    SelectpictureL = 40.0f;
    SelectpictureR = 465.0f;
    SelectY = 640.0f;

    RetrySelectUI = 0;
    TitleSelectUI = 0;
    ExitSelectUI = 0;

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

    //SkyBox用頂点シェーダを読み込む
    skyboxVShandle = LoadVertexShader("SkyBoxVS.cso");

    //SkyBox用ピクセルシェーダーを読み込む
    skyboxPShandle = LoadPixelShader("SkyBoxPS.cso");

}

//更新
void GameOver::Update()
{
    //--------------------------------
    // UI初期化
    //--------------------------------
    RetrySelectUI = 0;
    TitleSelectUI = 0;
    ExitSelectUI = 0;

    //--------------------------------
    // 入力取得
    //--------------------------------
    DINPUT_JOYSTATE input;
    GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

    Right = (input.X >= 500.0f || CheckDownKey(KEY_INPUT_D));
    Left = (input.X <= -500.0f || CheckDownKey(KEY_INPUT_A));
    Decide = (CheckDownController(PAD_INPUT_2) || CheckDownKey(KEY_INPUT_SPACE));

    if (input.X == 0)
    {
        InputJoycon = false;
    }

    //--------------------------------
    // 左右移動
    //--------------------------------
    if (Right && !InputJoycon)
    {
        PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

        SelectpictureR += 570;
        SelectpictureL += 570;

        InputJoycon = true;
    }

    if (Left && !InputJoycon)
    {
        PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

        SelectpictureR -= 570;
        SelectpictureL -= 570;

        InputJoycon = true;
    }

    //--------------------------------
    // カーソルループ
    //--------------------------------
    if (SelectpictureL > MaxRight)
    {
        SelectpictureR = 465.0f;
        SelectpictureL = 40.0f;
    }

    if (SelectpictureL < MaxLeft)
    {
        SelectpictureR = 1605.0f;
        SelectpictureL = 1180.0f;
    }

    //--------------------------------
    // 決定入力
    //--------------------------------
    if (Decide)
    {
        PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

        if (SelectpictureL >= 35.0f && SelectpictureL <= 45.0f)
        {
            Master::mpSceneManager->ChangeScene(SceneName::GameScene);
        }

        else if (SelectpictureL >= 600.0f && SelectpictureL <= 610.0f)
        {
            Master::mpSceneManager->ChangeScene(SceneName::TitleScene);
        }

        else if (SelectpictureL >= 1170.0f && SelectpictureL <= 1180.0f)
        {
            Master::mpGameManager->EndGameLoop();
        }
    }

    //--------------------------------
    // UIカーソル
    //--------------------------------
    if (SelectpictureL >= 38.0f && SelectpictureL <= 45.0f)
    {
        RetrySelectUI = 1;
    }

    else if (SelectpictureL >= 600.0f && SelectpictureL <= 610.0f)
    {
        TitleSelectUI = 1;
    }

    else if (SelectpictureL >= 1170.0f && SelectpictureL <= 1180.0f)
    {
        ExitSelectUI = 1;
    }

    //--------------------------------
    // SkyBox更新
    //--------------------------------
    m_skybox->Update();

}

//描画
void GameOver::Draw()
{
    SetUseVertexShader(skyboxVShandle);

    // 使用するピクセルシェーダーをセット
    SetUsePixelShader(skyboxPShandle);

    m_skybox->Draw();

    //終わったら解除
    SetUseVertexShader(-1);
    SetUsePixelShader(-1);

    DrawGraph(LogoX, LogoY, GameOverLogo_Handle, true);
    DrawGraph(SelectpictureR, SelectY, SelectpictureR_Handle, true);
    DrawGraph(SelectpictureL, SelectY - 15, SelectpictureL_Handle, true);

    //UI
    DrawGraph(RetryUI, GameOverUIY, GameOverUI[0 + RetrySelectUI], true);
    DrawGraph(TitleUI, GameOverUIY, GameOverUI[2 + TitleSelectUI], true);
    DrawGraph(ExitUI, GameOverUIY, GameOverUI[4 + ExitSelectUI], true);

}

//終了処理
void GameOver::Finaliza()
{
    Master::mpObjectManager->Delete(m_skybox);
    m_skybox = nullptr;

    DeleteSoundMem(GameOverBGM);
    DeleteSoundMem(ButtonMusic);

    DeleteGraph(GameOverLogo_Handle);
    DeleteGraph(SelectpictureR_Handle);
    DeleteGraph(SelectpictureL_Handle);

    for (int i = 0; i < 6; i++)
    {
        DeleteGraph(GameOverUI[i]);
    }

}
