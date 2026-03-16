#include "Dxlib.h"
#include "../Haeder/Explain.h"
#include "../Haeder/SceneBase.h"
#include "../Haeder/SceneManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/CheckKey.h"
#include "../Haeder/ObujectManager.h"
#include "../Master.h"

//コンストラクタ
Explain::Explain()
:m_skybox()
,skyboxPShandle(0)
,skyboxVShandle(0)
,Controller_Image(-1)
,Explain_UI()
,Keyboard_Image(-1)
,SelectpictureR_Handle(-1)
,SelectpictureL_Handle(-1)
,TitleUIX(0)
,Explain_UIX(-1)
,Explain_UIY(-1)
,TitleSelect(-1)
,ExplainSelect(-1)
,right(false)
,left(false)
,enter(false)
,SelectpictureL(0.0f)
,SelectpictureR(0.0f)
,SelectY(0.0f)
,ExplainBGM(-1)
,ButtonMusic(-1)
,ExplainFlag(false)
{
}

//デストラクタ
Explain::~Explain()
{
}

//初期化
void Explain::Initaliza()
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
    ExplainBGM = LoadSoundMem("Musics/Explain.mp3");

    //ボタン
    ButtonMusic = LoadSoundMem("Musics/poka01.mp3");

    //BGM再生
    PlaySoundMem(ExplainBGM, DX_PLAYTYPE_LOOP);

    LoadDivGraph("Assets/Explain_Title.png", 6, 2, 3, 181, 67, Explain_UI);
        
    Controller_Image = LoadGraph("Assets/Explain_Controller.png");

    Keyboard_Image = LoadGraph("Assets/Explain_Keyboard.png");

    SelectpictureR_Handle = LoadGraph("Assets/SelectpictureR.png");
    SelectpictureL_Handle = LoadGraph("Assets/SelectpictureL.png");

    TitleUIX = 120;
    Explain_UIY = 950;
    Explain_UIX = 1600;
    SelectpictureL = -25.0f;
    SelectpictureR = 275.0f;
    SelectY = 860.0f;

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
void Explain::Update()
{

    //--------------------------------
    // UI初期化
    //--------------------------------
    TitleSelect = 0;
    ExplainSelect = 0;

    //--------------------------------
    // 入力取得
    //--------------------------------
    DINPUT_JOYSTATE input;
    GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

    right = (input.X >= 500.0f || CheckDownKey(KEY_INPUT_D));
    left = (input.X <= -500.0f || CheckDownKey(KEY_INPUT_A));
    enter = (CheckDownController(PAD_INPUT_2) || CheckDownKey(KEY_INPUT_SPACE));

        //説明カーソル
    if (right)
    {
        PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

        SelectpictureL = 1460.0f;
        SelectpictureR = 1740.0f;

    }

    if (left)
    {
        PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

        SelectpictureL = -25.0f;
        SelectpictureR = 275.0f;

    }

    if (enter)
    {
        PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

        if (SelectpictureL >= -30.0f && SelectpictureL <= 0)
        {
            Master::mpSceneManager->ChangeScene(SceneName::TitleScene);
        }

        else
        {
            if (!ExplainFlag)
            {
                ExplainFlag = true;
            }

            else
            {
                ExplainFlag = false;
            }
        }
    }

    //--------------------------------
    // UIカーソル
    //--------------------------------
    if (SelectpictureL >= -30.0f && SelectpictureL <= 0)
    {
        TitleSelect = 1;
    }

    else
    {
        ExplainSelect = 1;
    }

    //--------------------------------
    // SkyBox更新
    //--------------------------------
    m_skybox->Update();

}

//描画
void Explain::Draw()
{
    SetUseVertexShader(skyboxVShandle);

    // 使用するピクセルシェーダーをセット
    SetUsePixelShader(skyboxPShandle);

    m_skybox->Draw();

    //終わったら解除
    SetUseVertexShader(-1);
    SetUsePixelShader(-1);

    if (!ExplainFlag)
    {
        DrawGraph(450, 150, Controller_Image, true);

        DrawGraph(Explain_UIX, Explain_UIY, Explain_UI[0 + ExplainSelect], true);
    }

    else
    {
        DrawGraph(450, 150, Keyboard_Image, true);

        DrawGraph(Explain_UIX, Explain_UIY, Explain_UI[4 + ExplainSelect], true);

    }

    DrawGraph(TitleUIX, Explain_UIY, Explain_UI[2 + TitleSelect], true);

    DrawGraph(SelectpictureL, SelectY - 15, SelectpictureL_Handle, true);

    DrawGraph(SelectpictureR, SelectY, SelectpictureR_Handle, true);


}

//終了処理
void Explain::Finaliza()
{

    Master::mpObjectManager->Delete(m_skybox);
    m_skybox = nullptr;

    DeleteSoundMem(ExplainBGM);

}
