#include "Dxlib.h"
#include "../Haeder/Title.h"
#include "../Haeder/SceneBase.h"
#include "../Haeder/SceneManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/CheckKey.h"
#include "../Haeder/ResourceManeger.h"
#include "../Haeder/ObujectManager.h"
#include "../Master.h"

// 実体を作成
Title g_Title;

//コンストラクタ
Title::Title()
:SceneBase()
,m_skybox()
,skyboxPShandle(0)
,skyboxVShandle(0)
,Logo_Handle(0)
,SelectpictureR_Handle(0)
,SelectpictureL_Handle(0)
,StageSelect_Handle(0)
,SelectpictureR(0.0f)
,SelectpictureL(0.0f)
,SelectY(0.0f)
,GameSelectUI(0)
,SettingSelectUI(0)
,ExitSelectUI(0)
,NomalStageUI(0)
,CreatedStageNo1UI(0)
,CreatedStageNo2UI(0)
,TitleUI()
,StageUI()
,LogoX(0.0f)
,LogoY(0.0f)
,TitleUIY(0.0f)
,MaxRight(0.0f)
,MaxLeft(0.0f)
,GameUI(0.0f)
,SettingUI(0.0f)
,ExitUI(0.0f)
,GuideUIX(0.0f)
,GuideUIY(0.0f)
,PlusMinusUIX(0.0f)
,PlusMinusUIY(0.0f)
,InputJoycon(false)
,StageSelect(false)
,ButtonMusic(0)
,TitleBGM(0)
,StageNumber(0)
,WarnCount(0.0f)
,WarnFlag(false)
,ExplainFlag(false)
,ExplainSelectUI(0)
,ExplainUI()
,BackFlag(false)
,BackSelectUI(0)
,BackUI()
{
}

//デストラクタ
Title::~Title()
{
}

//初期化
void Title::Initaliza()
{
    SetCameraPositionAndTarget_UpVecY
    (
        VGet(0.0f, 100.0f, -200.0f),
        VGet(0.0f, 100.0f, 0.0f)
    );

    //カメラのクリッピング距離を設定　どこまで写すのか
    SetCameraNearFar(1.0f, 30000.0f);

    /////////サウンドの読み込み/////////
    //BGM
    TitleBGM = LoadSoundMem("Musics/Title.mp3");

    //ボタン
    ButtonMusic = LoadSoundMem("Musics/poka01.mp3");

    ChangeVolumeSoundMem(170, TitleBGM);

    //BGM再生
    PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP);

    LoadDivGraph("Assets/TitleUI.png", 8, 2, 4, 321, 108, TitleUI);
    LoadDivGraph("Assets/StageUI.png", 6, 2, 3, 356, 118, StageUI);
    LoadDivGraph("Assets/Guide.png",2, 2, 1, 198, 69, ExplainUI);
    LoadDivGraph("Assets/BackUI.png",2, 2, 1, 181, 70, BackUI);

    Logo_Handle = LoadGraph("Assets/Logo.png");
    SelectpictureR_Handle = LoadGraph("Assets/SelectpictureR.png");
    SelectpictureL_Handle = LoadGraph("Assets/SelectpictureL.png");
    StageSelect_Handle = LoadGraph("Assets/StageSelect.png");

    //一番左
    MaxRight = 1180.0f;

    //一番右
    MaxLeft = 40.0f;

    //UI
    LogoX = 480.0f;
    LogoY = 100.0f;
    TitleUIY = 700.0f;
    GameUI = 180.0f;
    SettingUI = 750.0f;
    ExitUI = 1320.0f;
    SelectpictureL = 40.0f;
    SelectpictureR = 465.0f;
    SelectY = 640.0f;
    GuideUIX = 120.0f;
    GuideUIY = 950.0f;
    PlusMinusUIX = 170.0f;
    PlusMinusUIY = 910.0f;

    GameSelectUI = 0;
    SettingSelectUI = 0;
    ExitSelectUI = 0;

    //一瞬の取得
    InputJoycon = false;

    //ステージセレクト画面の表示
    StageSelect = false;

    ExplainFlag = false;

    BackFlag = false;

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
void Title::Update()
{
    //--------------------------------
    // UI初期化
    //--------------------------------
    GameSelectUI = 0;
    SettingSelectUI = 0;
    ExitSelectUI = 0;

    NomalStageUI = 0;
    CreatedStageNo1UI = 0;
    CreatedStageNo2UI = 0;

    ExplainSelectUI = 0;

    BackSelectUI = 0;

    //--------------------------------
    // 入力取得
    //--------------------------------
    DINPUT_JOYSTATE input;
    GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

    bool right = (input.X >= 500.0f || CheckDownKey(KEY_INPUT_D));
    bool left = (input.X <= -500.0f || CheckDownKey(KEY_INPUT_A));
    bool down = (input.Y >= 500.0f || CheckDownKey(KEY_INPUT_S));
    bool up = (input.Y <= -500.0f || CheckDownKey(KEY_INPUT_W));
    bool enter = (CheckDownController(PAD_INPUT_2) || CheckDownKey(KEY_INPUT_SPACE));

    if (input.X == 0)
    {
        InputJoycon = false;
    }

    //--------------------------------
    // タイトルメニュー
    //--------------------------------
    if (!StageSelect)
    {
        //説明カーソル
        if (!ExplainFlag && down)
        {
            ExplainFlag = true;
        }

        if (ExplainFlag && up)
        {
            ExplainFlag = false;

            SelectpictureL = 40.0f;
            SelectpictureR = 465.0f;
            SelectY = 640.0f;
        }

        //--------------------------------
        // 左右移動
        //--------------------------------
        if (!ExplainFlag)
        {
            if (right && !InputJoycon)
            {
                PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

                SelectpictureR += 570;
                SelectpictureL += 570;

                InputJoycon = true;
            }

            if (left && !InputJoycon)
            {
                PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

                SelectpictureR -= 570;
                SelectpictureL -= 570;

                InputJoycon = true;
            }
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
            SelectpictureR = 1605;
            SelectpictureL = 1180;
        }

        //--------------------------------
        // 決定入力
        //--------------------------------
        if (enter)
        {
            PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

            if (ExplainFlag)
            {
                Master::mpSceneManager->ChangeScene(SceneName::ExplainScene);
            }

            else if (SelectpictureL >= 35.0f && SelectpictureL <= 45.0f)
            {
                StageSelect = true;
            }

            else if (SelectpictureL >= 600.0f && SelectpictureL <= 610.0f)
            {
                Master::mpSceneManager->ChangeScene(SceneName::StageScene);
            }

            else if (SelectpictureL >= 1170.0f && SelectpictureL <= 1180.0f)
            {
                Master::mpGameManager->EndGameLoop();
            }
        }
    }

    //--------------------------------
    // ステージセレクト
    //--------------------------------
    else
    {
        //戻るカーソル
        if (!BackFlag && down)
        {
            BackFlag = true;
        }

        if (BackFlag && up)
        {
            BackFlag = false;

            SelectpictureL = 40.0f;
            SelectpictureR = 465.0f;
            SelectY = 640.0f;
        }


        //--------------------------------
        // 左右移動
        //--------------------------------
        if (!BackFlag)
        {
            if (right && !InputJoycon)
            {
                PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

                SelectpictureR += 570;
                SelectpictureL += 570;

                InputJoycon = true;
            }

            if (left && !InputJoycon)
            {
                PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

                SelectpictureR -= 570;
                SelectpictureL -= 570;

                InputJoycon = true;
            }
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
            SelectpictureR = 1605;
            SelectpictureL = 1180;
        }

        //--------------------------------
        // 決定
        //--------------------------------
        if (enter)
        {
            PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

            //--------------------------------
            // 戻る決定
            //--------------------------------
            if (BackFlag)
            {

                StageSelect = false;
                BackFlag = false;

                SelectpictureL = 40.0f;
                SelectpictureR = 465.0f;
                SelectY = 640.0f;

                return;
            }

            if (SelectpictureL >= 35.0f && SelectpictureL <= 45.0f)
            {
                g_Title.SetStageNumber(0);
            }

            else if (SelectpictureL >= 600.0f && SelectpictureL <= 610.0f)
            {
                g_Title.SetStageNumber(1);
            }

            else if (SelectpictureL >= 1170.0f && SelectpictureL <= 1180.0f)
            {
                g_Title.SetStageNumber(2);
            }

            int stage = GetStageNumber();

            char filenameplayer[64];
            sprintf_s(filenameplayer, "Player%d.bin", stage);

            FILE* playerfile;
            fopen_s(&playerfile, filenameplayer, "rb");

            if (playerfile == NULL)
            {
                WarnCount = 60.0f;
                WarnFlag = true;
            }

            else
            {
                Master::mpSceneManager->ChangeScene(SceneName::GameScene);
            }

        }

    }

    //--------------------------------
    // 警告タイマー
    //--------------------------------
    if (WarnCount > 0)
    {
        WarnCount--;
    }
    else
    {
        WarnFlag = false;
    }

    //--------------------------------
    // 説明カーソル表示
    //--------------------------------
    if (ExplainFlag)
    {
        ExplainSelectUI = 1;

        SelectpictureL = -25.0f;
        SelectpictureR = 285.0f;
        SelectY = 860.0f;
    }

    //--------------------------------
    // 戻るカーソル表示
    //--------------------------------
    if (BackFlag)
    {
        BackSelectUI = 1;

        SelectpictureL = -30.0f;
        SelectpictureR = 235.0f;
        SelectY = 860.0f;
    }

    //--------------------------------
    // UIカーソル
    //--------------------------------
    if (SelectpictureL >= 38.0f && SelectpictureL <= 45.0f)
    {
        GameSelectUI = 1;
        NomalStageUI = 1;
    }

    else if (SelectpictureL >= 600.0f && SelectpictureL <= 610.0f)
    {
        SettingSelectUI = 1;
        CreatedStageNo1UI = 1;
    }

    else if (SelectpictureL >= 1170.0f && SelectpictureL <= 1180.0f)
    {
        ExitSelectUI = 1;
        CreatedStageNo2UI = 1;
    }

    //--------------------------------
    // SkyBox更新
    //--------------------------------
    m_skybox->Update();
}

//描画
void Title::Draw()
{

    SetUseVertexShader(skyboxVShandle);

    // 使用するピクセルシェーダーをセット
    SetUsePixelShader(skyboxPShandle);

    m_skybox->Draw();

    //終わったら解除
    SetUseVertexShader(-1);
    SetUsePixelShader(-1);

    if (StageSelect == false)
    {    

        DrawGraph(LogoX, LogoY, Logo_Handle, true);

        DrawGraph(SelectpictureR, SelectY, SelectpictureR_Handle, true);

        DrawGraph(SelectpictureL, SelectY - 15, SelectpictureL_Handle, true);

        //UI
        DrawGraph(GameUI, TitleUIY, TitleUI[0 + GameSelectUI], true);
        DrawGraph(SettingUI, TitleUIY, TitleUI[2 + SettingSelectUI], true);
        DrawGraph(ExitUI, TitleUIY, TitleUI[4 + ExitSelectUI], true);
        DrawGraph(GuideUIX, GuideUIY, ExplainUI[0 + ExplainSelectUI], true);
    }

    else
    {   

        DrawGraph(LogoX - 190, LogoY, StageSelect_Handle, true);

        DrawGraph(SelectpictureR + 35, SelectY, SelectpictureR_Handle, true);

        DrawGraph(SelectpictureL, SelectY - 15, SelectpictureL_Handle, true);

        //UI
        //X軸は共通
        DrawGraph(GameUI, TitleUIY, StageUI[0 + NomalStageUI], true);
        DrawGraph(SettingUI, TitleUIY, StageUI[2 + CreatedStageNo1UI], true);
        DrawGraph(ExitUI, TitleUIY, StageUI[4 + CreatedStageNo2UI], true);
        DrawGraph(GuideUIX, GuideUIY, BackUI[0 + BackSelectUI], true);

    }

    if (WarnFlag == true)
    {
        LoadGraphScreen(600.0f, 180.0f, "Assets/Warn.png", true);

    }
}

//終了処理
void Title::Finaliza()
{   
    Master::mpObjectManager->Delete(m_skybox);
    m_skybox = nullptr;


    DeleteSoundMem(TitleBGM);
    DeleteSoundMem(ButtonMusic);

    //UI画像削除
    for (int i = 0; i < 7; i++)
    {
        DeleteGraph(TitleUI[i]);
    }

    for (int i = 0; i < 6; i++)
    {
        DeleteGraph(StageUI[i]);
    }

    for (int i = 0; i < 2; i++)
    {
        DeleteGraph(ExplainUI[i]);
        DeleteGraph(BackUI[i]);
    }

    DeleteGraph(Logo_Handle);
    DeleteGraph(SelectpictureR_Handle);
    DeleteGraph(SelectpictureL_Handle);
    DeleteGraph(StageSelect_Handle);

}
