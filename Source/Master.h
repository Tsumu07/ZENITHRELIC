#pragma once

class ObjectManager;
class Camera;
class GameManager;
class SceneManager;
class Stage;
class ResourceManager;

//ゲームを管理するクラス
//誰でもいじれる
class Master
{
public:

    static ObjectManager* mpObjectManager;
    static GameManager* mpGameManager;
    static Camera* mpCamera;
    static SceneManager* mpSceneManager;
    static ResourceManager* mpResourceManager;

    static void Initialize();
    static void Finalize();
};