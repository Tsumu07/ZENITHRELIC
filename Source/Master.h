#pragma once
#include <memory>

class ObjectManager;
class Camera;
class GameManager;
class SceneManager;
class Stage;
class ResourceManager;
class ItemManeger;

//ゲームを管理するクラス
//誰でもいじれる
class Master
{
private:

    static std::unique_ptr<GameManager> mpGameManager;
    static std::unique_ptr<Camera> mpCamera;
    static std::unique_ptr<SceneManager> mpSceneManager;
    static std::unique_ptr<ObjectManager> mpObjectManager;
    static std::unique_ptr<ResourceManager> mpResourceManager;
    static std::unique_ptr<ItemManeger> mpItemManeger;

public:

    static void Initialize();
    static void Finalize();

    static GameManager* GetGameManager()
    {
        return mpGameManager.get();
    }

    static Camera* GetCamera()
    {
        return mpCamera.get();
    }

    static SceneManager* GetSceneManager()
    {
        return mpSceneManager.get();
    }

    static ObjectManager* GetObjectManager()
    {
        return mpObjectManager.get();
    }

    static ResourceManager* GetResourceManager()
    {
        return mpResourceManager.get();
    }

    static ItemManeger* GetItemManeger()
    {
        return mpItemManeger.get();
    }


};