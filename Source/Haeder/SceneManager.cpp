#include "Dxlib.h"
#include "../Haeder/SceneManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/Title.h"
#include "../Haeder/Config.h"
#include "../Haeder/GameClear.h"
#include "../Haeder/GameOver.h"
#include "../Haeder/Menu.h"
#include "../Haeder/Game.h"
#include "../Haeder/StageScene.h"
#include "../Haeder/Explain.h"
#include "../Haeder/LoadingScreen.h"
#include "../Haeder/InventoryScene.h"
#include "../Haeder/FadeScene.h"

//コンストラクタ
SceneManager::SceneManager()
:mpScene(nullptr)
,mpMenuScene(nullptr)
,mpWipeScene(nullptr)
,m_nextScene(SceneNone)
,m_currentScene(SceneNone)
,m_isSceneChanging(false)
,IsMenuSceneEnd(false)
{
}

//デストラクタ
SceneManager::~SceneManager()
{
}

//初期化
void SceneManager::Initaliza()
{
    //初期シーン設定
    mpScene = new Title();
    mpScene->Initaliza();

    m_isSceneChanging = false;
    m_currentScene = TitleScene;

    // フェードイン開始
    mpWipeScene = new FadeScene();
    mpWipeScene->Initaliza();
    mpWipeScene->SetFadeMode(1);

}

//シーン切り替え処理
void SceneManager::ChangeScene(SceneName Scene)
{

    if (m_isSceneChanging)
    {
        return;
    }

    m_nextScene = Scene;
    m_isSceneChanging = true;

    // フェードアウト開始
    mpWipeScene->SetFadeMode(2);
}


//更新
void SceneManager::Update()
{
    // フェード中
    if (mpWipeScene->GetFadeMode() != 0)
    {
        mpWipeScene->Update();

        // FadeOut 完了
        if (mpWipeScene->GetFadeMode() == 3 && m_isSceneChanging)
        {
            // 旧シーン破棄
            if (mpScene)
            {
                mpScene->Finaliza();
                delete mpScene;
                mpScene = nullptr;
            }

            // 次シーン生成
            switch (m_nextScene)
            {
            case TitleScene:
                mpScene = new Title();
                break;
            case StageScene:
                mpScene = new Stage();
                break;
            case ExplainScene:
                mpScene = new Explain();
                break;
            case GameScene:
                mpScene = new Game();
                break;
            case GameOverScene:
                mpScene = new GameOver();
                break;
            case GameClearScene:
                mpScene = new GameClear();
                break;
            default: break;
            }

            if (mpScene)
            {
                mpScene->Initaliza();
                m_currentScene = m_nextScene;
            }

            mpWipeScene->SetFadeMode(1);//フェードイン
            m_isSceneChanging = false;
        }

    }

    // 通常更新
    if (mpScene)
    {
        mpScene->Update();
    }

}

//描画
void SceneManager::Draw()
{
    ClearDrawScreen();

    if (mpScene)
    {

        mpScene->Draw();
    }

    // フェードは最前面
    if (mpWipeScene->GetFadeMode() != 0)
    {
        mpWipeScene->Draw();
    }

    ScreenFlip();
}

void SceneManager::CreateMenu()
{
    mpMenuScene = new Menu();

    mpMenuScene->Initaliza();

}

void SceneManager::UpdateMenuScene()
{
    if (mpMenuScene != nullptr)
    {
        mpMenuScene->Update();
    }
}

void SceneManager::DrawMenuScene()
{
    if (mpMenuScene != nullptr)
    {
        mpMenuScene->Draw();
    }

}

void SceneManager::DeleteMenuScene()
{
    if (mpMenuScene != nullptr)
    {
        delete mpMenuScene;

        mpMenuScene = nullptr;
    }

}

void SceneManager::OpenInventory()
{
    // 既存のメニューがあるなら破棄
    DeleteMenuScene();

    // InventoryScene をメニューシーンとして開く
    mpMenuScene = new Inventory();

    mpMenuScene->Initaliza();

}

void SceneManager::CloseInventory()
{
    DeleteMenuScene();
    IsMenuSceneEnd = false;
}

//終了処理
void SceneManager::Finaliza()
{
   
}

