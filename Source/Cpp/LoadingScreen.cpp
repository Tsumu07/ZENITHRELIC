#include "DxLib.h"
#include "../Haeder/LoadingScreen.h"
#include "../Haeder/SceneBase.h"
#include "../Haeder/SceneManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/CheckKey.h"
#include "../Haeder/Object.h"
#include "../Haeder/StageScene.h"

//コンストラクタ
LoadingScreen::LoadingScreen()
{
}

//デストラクタ
LoadingScreen::~LoadingScreen()
{
}

//初期化
void LoadingScreen::Initaliza()
{
}

//更新
void LoadingScreen::Update()
{
    if (Master::mpGameManager->end == true)
    {
         Master::mpSceneManager->ChangeScene(SceneName::GameScene);
    }

    if (Master::mpGameManager->end == false)
    {
       
        LoadingNow = true;

    }

}

//描画
void LoadingScreen::Draw()
{

    if (LoadingNow == true)
    {
      DrawString(370, 300, "読み込み中・・・", GetColor(255, 255, 255));

    }

}

//終了処理
void LoadingScreen::Finaliza()
{
}