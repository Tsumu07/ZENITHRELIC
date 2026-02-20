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

    //BGM再生
    PlaySoundMem(TitleBGM, DX_PLAYTYPE_LOOP);

    LoadDivGraph("Assets/TitleUI.png", 8, 2, 4, 321, 108, TitleUI);
    LoadDivGraph("Assets/StageUI.png", 6, 2, 3, 356, 118, StageUI);

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
    GuideUIX = 0.0f;
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

    GameSelectUI = 0;
    SettingSelectUI = 0;
    ExitSelectUI = 0;

    NomalStageUI = 0;
    CreatedStageNo1UI = 0;
    CreatedStageNo2UI = 0;

    DINPUT_JOYSTATE input;

    // 入力状態を取得
    GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

    if (StageSelect == false)
    {
        if (input.X == 0)
        {
            InputJoycon = false;
        }

        if (CheckDownController(PAD_INPUT_6) != 0 || CheckDownKey(KEY_INPUT_E))
        {
            Master::mpSceneManager->ChangeScene(SceneName::ExplainScene);
        }

        if (CheckDownController(PAD_INPUT_2) != 0 || CheckDownKey(KEY_INPUT_Q))
        {
            //ゲーム画面
            if (SelectpictureL >= 35.0f && SelectpictureL <= 45.0f)
            {
                StageSelect = true;

            }

            //ステージエディター
            else if (SelectpictureL >= 600.0f && SelectpictureL <= 610.0f)
            {
                Master::mpSceneManager->ChangeScene(SceneName::StageScene);
            }

            //終了
            else if (SelectpictureL >= 1170.0f && SelectpictureL <= 1180.0f)
            {
                Master::mpGameManager->EndGameLoop();

            }
        }


        //右
        if (input.X >= 500.0f && InputJoycon == false || CheckDownKey(KEY_INPUT_D))
        {
            PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

            SelectpictureR += 570;
            SelectpictureL += 570;

            InputJoycon = true;

        }

        //一番右
        if (SelectpictureL > MaxRight)
        {           
            SelectpictureR = 465.0f;
            SelectpictureL = 40.0f;

        }

        //左
        if (input.X <= -500.0f && InputJoycon == false || CheckDownKey(KEY_INPUT_A))
        {
            PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);
            SelectpictureR -= 570;
            SelectpictureL -= 570;


            InputJoycon = true;

        }

        //一番左
        if (SelectpictureL < MaxLeft)
        {           
            SelectpictureR = 1605;
            SelectpictureL = 1180;

        }
    }

    if (StageSelect == true)
    {
        if (input.X == 0)
        {
            InputJoycon = false;
        }

        //右
        if (input.X >= 500.0f && InputJoycon == false || CheckDownKey(KEY_INPUT_D))
        {
            PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

            SelectpictureR += 570;
            SelectpictureL += 570;

            InputJoycon = true;
        }

        //一番右
        if (SelectpictureL > MaxRight)
        {            
            SelectpictureR = 465.0f;
            SelectpictureL = 40.0f;

        }

        //左
        if (input.X <= -500.0f && InputJoycon == false || CheckDownKey(KEY_INPUT_A))
        {
            PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);
            SelectpictureR -= 570;
            SelectpictureL -= 570;


            InputJoycon = true;

        }

        //一番左
        if (SelectpictureL < MaxLeft)
        {            
            SelectpictureR = 1605;
            SelectpictureL = 1180;

        }

        if (CheckDownController(PAD_INPUT_2) != 0 || CheckDownKey(KEY_INPUT_Q))
        {

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

            //保存されていなかったらそのまま
            int stage = g_Title.GetStageNumber();

            //オブジェクト分用意
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

        //警告表示時間
        if (WarnCount > 0)
        {
            WarnCount--;
        }

        if (WarnCount <= 0)
        {
            WarnCount = 0;

            WarnFlag = false;
        }

        //戻る
        if (CheckDownController(PAD_INPUT_1) != 0 || CheckDownKey(KEY_INPUT_SPACE))
        {
            StageSelect = false;
        }
    }

    //カーソル
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

        LoadGraphScreen(LogoX, LogoY, "Assets/Logo.png", true);

        LoadGraphScreen(SelectpictureR, SelectY, "Assets/SelectpictureR.png", true);

        LoadGraphScreen(SelectpictureL, SelectY - 15, "Assets/SelectpictureL.png", true);

        //UI
        DrawGraph(GameUI, TitleUIY, TitleUI[0 + GameSelectUI], true);
        DrawGraph(SettingUI, TitleUIY, TitleUI[2 + SettingSelectUI], true);
        DrawGraph(ExitUI, TitleUIY, TitleUI[4 + ExitSelectUI], true);
        LoadGraphScreen(GuideUIX, GuideUIY, "Assets/Guide.png", true);
        LoadGraphScreen(PlusMinusUIX, PlusMinusUIY, "Assets/PlusMinusUI.png", true);
    }

    else
    {   

        LoadGraphScreen(LogoX - 190, LogoY, "Assets/StageSelect.png", true);


        LoadGraphScreen(SelectpictureR + 35, SelectY, "Assets/SelectpictureR.png", true);

        LoadGraphScreen(SelectpictureL, SelectY - 15, "Assets/SelectpictureL.png", true);

        //UI
        //X軸は共通
        DrawGraph(GameUI, TitleUIY, StageUI[0 + NomalStageUI], true);
        DrawGraph(SettingUI, TitleUIY, StageUI[2 + CreatedStageNo1UI], true);
        DrawGraph(ExitUI, TitleUIY, StageUI[4 + CreatedStageNo2UI], true);
        LoadGraphScreen(GuideUIX, GuideUIY, "Assets/BackUI.png", true);
        LoadGraphScreen(PlusMinusUIX, PlusMinusUIY, "Assets/Button_B.png", true);
        LoadGraphScreen(PlusMinusUIX, PlusMinusUIY + 50, "Assets/space.png", true);

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

    //ClearDrawScreen();

    DeleteSoundMem(TitleBGM);

}
