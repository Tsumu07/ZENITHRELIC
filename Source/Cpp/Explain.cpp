#include "Dxlib.h"
#include "../Haeder/Explain.h"
#include "../Haeder/SceneBase.h"
#include "../Haeder/SceneManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/CheckKey.h"
#include "../Master.h"

//コンストラクタ
Explain::Explain()
:TriangleLeftX(0.0f)
,TriangleLeftY(0.0f)
,TriangleUnderX(0.0f)
,TriangleUnderY(0.0f)
,TriangleUpX(0.0f)
,TriangleUpY(0.0f)
,MaxUp(0.0f)
,MaxUnder(0.0f)
,InputJoycon(false)
, ExplainBGM(-1)
{
}

//デストラクタ
Explain::~Explain()
{
}

//初期化
void Explain::Initaliza()
{
    /////////サウンドの読み込み/////////
    //BGM
    ExplainBGM = LoadSoundMem("Musics/Explain.mp3");

    //BGM再生
    PlaySoundMem(ExplainBGM, DX_PLAYTYPE_LOOP);

    SetBackgroundColor(0, 0, 100);

}

//更新
void Explain::Update()
{
    if (CheckDownController(PAD_INPUT_2) != 0 || CheckDownKey(KEY_INPUT_SPACE))
    {
        Master::mpSceneManager->ChangeScene(SceneName::TitleScene);

    }
}

//描画
void Explain::Draw()
{
    LoadGraphScreen(450.0f, 200.0f, "Assets/操作説明.png", true);

}

//終了処理
void Explain::Finaliza()
{
    //ClearDrawScreen();

    DeleteSoundMem(ExplainBGM);

}
