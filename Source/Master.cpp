#include "DxLib.h"
#include "../Source/Master.h"
#include "Haeder/GameManager.h"
#include "Haeder/Camera.h"
#include "Haeder/SceneManager.h"
#include "Haeder/ObujectManager.h"
#include "Haeder/ResourceManeger.h"

GameManager* Master::mpGameManager = nullptr;
Camera* Master::mpCamera = nullptr;
SceneManager* Master::mpSceneManager = nullptr;
ObjectManager* Master::mpObjectManager = nullptr;
ResourceManager* Master::mpResourceManager = nullptr;

void Master::Initialize()
{
    mpGameManager = new GameManager();
    mpCamera = new Camera();
    mpSceneManager = new SceneManager();
    mpObjectManager = new ObjectManager();
    mpResourceManager = new ResourceManager();
}

void Master::Finalize()
{

    mpResourceManager = nullptr;
    mpObjectManager = nullptr;
    mpSceneManager = nullptr;
    mpCamera = nullptr;
    mpGameManager = nullptr;
}