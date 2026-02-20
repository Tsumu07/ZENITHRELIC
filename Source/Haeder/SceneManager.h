#pragma once
#include "SceneBase.h"
#include "FadeScene.h"

enum SceneName
{
    TitleScene = 0,
    StageScene = 1,
    ExplainScene = 2,

    GameScene = 3,
    InventoryScene = 4,
    ConfigScene = 5,
    GameOverScene = 6,
    GameClearScene = 7,

    SceneNone
};

class SceneManager
{
private:

    //通常シーン
    SceneBase* mpScene;

    //メニュー画面など
    SceneBase* mpMenuScene;

    //フェードイン、フェードアウト
    FadeScene* mpWipeScene;
    
    SceneName m_nextScene;   // 次に行くシーン

    SceneName m_currentScene;

    bool m_isSceneChanging;  // フェード中か？

    bool IsMenuSceneEnd;

public:
    SceneManager();   //コンストラクタ
    ~SceneManager();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

    //シーン移行
    void ChangeScene(SceneName Scene);

    SceneName GetCurrentScene() const { return m_currentScene; }

    void OpenInventory();

    void CloseInventory();

    void CreateMenu();

    bool IsMenuScene() { return mpMenuScene != nullptr; }

    bool MenuSceneEnd() { return IsMenuSceneEnd; }

    void UpdateMenuScene();

    void DrawMenuScene();

    void SetMenuSceneEnd(bool isMenuSceneEnd) { IsMenuSceneEnd = isMenuSceneEnd; }

    void DeleteMenuScene();

};