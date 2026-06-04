#include "DxLib.h"
#include "../Source/Master.h"
#include "Header/GameManager.h"
#include "Header/Camera.h"
#include "Header/SceneManager.h"
#include "Header/ObujectManager.h"
#include "Header/ResourceManager.h"
#include "Header/ItemManager.h"

std::unique_ptr<GameManager> Master::mpGameManager;
std::unique_ptr<Camera> Master::mpCamera;
std::unique_ptr<SceneManager> Master::mpSceneManager;
std::unique_ptr<ObjectManager> Master::mpObjectManager;
std::unique_ptr<ResourceManager> Master::mpResourceManager;
std::unique_ptr<ItemManeger> Master::mpItemManeger;

void Master::Initialize()
{
    mpGameManager = std::make_unique<GameManager>();
    mpCamera = std::make_unique<Camera>();
    mpSceneManager = std::make_unique<SceneManager>();
    mpObjectManager = std::make_unique<ObjectManager>();
    mpResourceManager = std::make_unique<ResourceManager>();
    mpItemManeger = std::make_unique<ItemManeger>();
}

void Master::Finalize()
{

    mpObjectManager.reset();
    mpSceneManager.reset();
    mpCamera.reset();
    mpGameManager.reset();

    mpResourceManager.reset();
    mpItemManeger.reset();
}