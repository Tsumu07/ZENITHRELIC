#include "Dxlib.h"
#include "../Haeder/Menu.h"
#include "../Haeder/SceneBase.h"
#include "../Haeder/SceneManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/CheckKey.h"
#include "../Haeder/Object.h"
#include "../Haeder/StageScene.h"
#include "../Master.h"

//コンストラクタ
Menu::Menu()
:TriangleLeftX(0.0f)
,TriangleLeftY(0.0f)
,TriangleUnderX(0.0f)
,TriangleUnderY(0.0f)
,TriangleUpX(0.0f)
,TriangleUpY(0.0f)
,MaxUp(0.0f)
,MaxUnder(0.0f)
,StringGame(0.0f)
,StringTitle(0.0f)
,StringStagi(0.0f)
,StringEnd(0.0f)
,GameOverBGM(-1)
,ButtonMusic(-1)
,InputJoycon(false)
{
}

//デストラクタ
Menu::~Menu()
{
}

//初期化
void Menu::Initaliza()
{
    //サウンドの読み込み    
 //BGN

    //ボタン
    ButtonMusic = LoadSoundMem("Musics/poka01.mp3");

    SetBackgroundColor(0, 0, 0);

    //右の頂点
    TriangleLeftX = 420.0f;
    TriangleLeftY = 380.0f;

    //下の頂点
    TriangleUnderX = 390.0f;
    TriangleUnderY = 400.0f;

    //上の頂点
    TriangleUpX = 390.0f;
    TriangleUpY = 360.0f;

    //一番上
    MaxUp = 350.0f;

    //一番下
    MaxUnder = 560.0f;

    // 文字
    StringGame = 480.0f;
    StringTitle = 480.0f;
    StringStagi = 480.0f;
    StringEnd = 480.0f;

    //一瞬の取得
    InputJoycon = false;



}

//更新
void Menu::Update()
{
    StringGame = 480.0f;
    StringTitle = 480.0f;
    StringStagi = 480.0f;
    StringEnd = 480.0f;

    DINPUT_JOYSTATE input;

    //入力状態を取得
    GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

    if (CheckDownController(PAD_INPUT_2) != 0 || CheckDownKey(KEY_INPUT_Q))
    {
        //続きから
        if (TriangleLeftY >= 380.0f && TriangleLeftY < 420.0f)
        {
            Master::mpSceneManager->SetMenuSceneEnd(true);


            return;
        }

        //最初から
        if (TriangleLeftY >= 430.0f && TriangleLeftY < 470.0f)
        {
            Master::mpSceneManager->ChangeScene(SceneName::GameScene);
        }

        //作り直し
        if (TriangleLeftY >= 480.0f && TriangleLeftY < 520.0f)
        {
            Master::mpSceneManager->ChangeScene(SceneName::StageScene);
        }

        //タイトル
        if (TriangleLeftY >= 530.0f && TriangleLeftY < 570.0f)
        {           
            Master::mpSceneManager->ChangeScene(SceneName::TitleScene);
        }

    }

    if (input.Y == 0)
    {
        InputJoycon = false;
    }

    // 上
    if (input.Y <= -500.0f && InputJoycon == false || CheckDownKey(KEY_INPUT_W))
    {
        PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

        //右の頂点
        TriangleLeftY -= 50.0f;

        //下の頂点
        TriangleUnderY -= 50.0f;

        //上の頂点
        TriangleUpY -= 50.0f;

        InputJoycon = true;

    }

    //一番上
    if (TriangleUnderY <= MaxUp)
    {
        TriangleLeftY = 530.0f;
        TriangleUnderY = 550.0f;
        TriangleUpY = 510.0f;
    }

    //下
    if (input.Y >= 500.0f && InputJoycon == false  || CheckDownKey(KEY_INPUT_S))
    {
        PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

        //右の頂点
        TriangleLeftY += 50.0f;

        //下の頂点
        TriangleUnderY += 50.0f;

        //上の頂点
        TriangleUpY += 50.0f;

        InputJoycon = true;

    }

    // 一番下
    if (TriangleUnderY >= MaxUnder)
    {
        TriangleLeftY = 380.0f;
        TriangleUnderY = 400.0f;
        TriangleUpY = 360.0f;
    }

    //文字を動かす
    //ゲーム画面
    if (TriangleLeftY >= 380.0f && TriangleLeftY < 430.0f)
    {
        StringGame = 460;
    }

    //最初から
    if (TriangleLeftY >= 430.0f && TriangleLeftY < 480.0f)
    {
        StringTitle = 460;
    }

    //作り直し
    if (TriangleLeftY >= 480.0f && TriangleLeftY < 520.0f)
    {
        StringStagi = 460;
    }

    //タイトル
    if (TriangleLeftY >= 530.0f && TriangleLeftY < 570.0f)
    {
        StringEnd = 460;
    }


}

//描画
void Menu::Draw()
{
    DrawString(470, 100, "メニュー画面", GetColor(255, 255, 255));
    DrawString(470, 250, "Press the B", GetColor(255, 255, 255));

    DrawString(StringGame, 370, "続きから", GetColor(255, 255, 255));
    DrawString(StringTitle, 420, "最初から", GetColor(255, 255, 255));
    DrawString(StringStagi, 470, "作り直し", GetColor(255, 255, 255));
    DrawString(StringEnd, 520, "タイトル", GetColor(255, 255, 255));

    //右の頂点,                        下の頂点,                    上の頂点
    DrawTriangle(TriangleLeftX, TriangleLeftY, TriangleUnderX, TriangleUnderY, TriangleUpX, TriangleUpY, GetColor(255, 255, 255), FALSE);

    DrawBox(350.0f, 570.0f, 700.0f, 350.0f, GetColor(255, 255, 255), FALSE);

}

//終了処理
void Menu::Finaliza()
{
    //ClearDrawScreen();

}
