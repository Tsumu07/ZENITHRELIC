#include "DxLib.h"
#include "../Source/Master.h"
#include "Header/GameManager.h"
#include "Header/Camera.h"
#include "Header/SceneManager.h"
#include "Header/ObujectManager.h"
#include "Header/ResourceManeger.h"
#include "Header/ItemManeger.h"

GameManager* Master::mpGameManager = nullptr;
Camera* Master::mpCamera = nullptr;
SceneManager* Master::mpSceneManager = nullptr;
ObjectManager* Master::mpObjectManager = nullptr;
ResourceManager* Master::mpResourceManager = nullptr;
ItemManeger* Master::mpItemManeger = nullptr;

void Master::Initialize()
{
    mpGameManager = new GameManager();
    mpCamera = new Camera();
    mpSceneManager = new SceneManager();
    mpObjectManager = new ObjectManager();
    mpResourceManager = new ResourceManager();
    mpItemManeger = new ItemManeger();
}

void Master::Finalize()
{

    mpResourceManager = nullptr;
    mpObjectManager = nullptr;
    mpSceneManager = nullptr;
    mpCamera = nullptr;
    mpGameManager = nullptr;
    mpItemManeger = nullptr;
    mpGameManager = nullptr;
}