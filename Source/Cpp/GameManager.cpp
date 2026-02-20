#include "DxLib.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Player.h"
#include "../Haeder/Spider.h"
#include "../Haeder/Camera.h"
#include "../Haeder/HpItem.h"
#include "../Haeder/Column.h"
#include "../Haeder/Wall.h"
#include "../Haeder/Goal.h"
#include "../Haeder/StageFrame.h"
#include "../Haeder/LoadingScreen.h"
#include "../Haeder/Title.h"
#include "../Haeder/Point.h"
#include "../Haeder/Field.h"
#include "../Haeder/Spider_state.h"
#include "../Haeder/FSMFactory.h"
#include "../Haeder/ResourceManeger.h"
#include "../Haeder/Game.h"
#include "../Master.h"
#include "../Haeder/Player_UI.h"
#include "EffekseerForDXLib.h"


//コンストラクタ
GameManager::GameManager()
{

    end = false;

    GameLoop = true;

}


//デストラクタ

GameManager::~GameManager()
{

}


//初期化

void GameManager::Initaliza()
{

    end = false;

    Effekseer_Init(8000);

    // フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
    // Effekseerを使用する場合は必ず設定する。
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DXライブラリのデバイスロストした時のコールバックを設定する。
    // ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
    // ただし、DirectX11を使用する場合は実行する必要はない。
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    Master::mpResourceManager->LoadEffectFromFile("Effect/Light.efkefc", 5.0f);

    if (Master::mpObjectManager == nullptr)
    {
        Master::mpObjectManager = new ObjectManager();
    }

    SetUseASyncLoadFlag(TRUE);

    //フィールド
    Field* field;
    field = new Field();
    field->Initaliza();
    field->SetLayer(0);
    field->SetTag(3000);
    field->SetPos(VGet(0.0f, 0.0f, 0.0f));
    field->SetDir(VGet(1.0f, 0.0f, 0.0f));
    field->SetSpeed(0.0f);
    field->SetTeam(0);

    SetUseASyncLoadFlag(FALSE);

    // 同じCPP内の別の場所から読み取る
    int stage = g_Title.GetStageNumber();

    //オブジェクト分用意
    char filenameplayer[64];
    sprintf_s(filenameplayer, "Player%d.bin", stage);

    FILE *playerfile;
    fopen_s(&playerfile, filenameplayer, "rb");
    if (playerfile == NULL) 
    {
        perror("ファイルオープンエラー");
        return;
    }

    Person person;
    fread(&person, sizeof(Person), 1, playerfile);

    // プレイヤー生成
    Player *player = new Player();
    player->Initaliza();
    player->SetPos(VGet(person.PosiX, person.PosiY, person.PosiZ));
    player->SetRadius(80.0f);
    player->SetTag(100);
    player->SetLayer(2);
    player->SetHp(420);
    player->SetInvincible(0.0f);
    player->SetTeam(1);
    //オブジェクトリストの追加
    Master::mpObjectManager->AddObjectList(player);

    player->SetFSM(FSMFactory::Create("Player", player));

    fclose(playerfile);

    ////ポイントの情報
    char filenamepoint[64];
    sprintf_s(filenamepoint, "Point%d.bin", stage);

    FILE* filepoint;
    fopen_s(&filepoint, filenamepoint, "rb");

    if (filepoint == NULL)
    {
        perror("ファイルオープンエラー");
        return;
    }

    while (!feof(filepoint))
    {
        Person point;

        int succese = fread(&point, sizeof(Person), 1, filepoint);

        if (succese == 0)
        {
            break;
        }

        //ポイントの初期化
        Point* points = new Point();
        points->Initaliza();
        points->SetPos(VGet(point.PosiX,200.0f, point.PosiZ));
        //敵にポジションリストを渡す
        points->SetPosRist(VGet(point.PosiX, point.PosiY, point.PosiZ));
        points->SetRadius(64.0f);
        points->SetTag(400);
        points->SetLayer(1);
        points->SetTeam(1);
        Master::mpObjectManager->AddObjectList(points);

    }

    fclose(filepoint);

    //柱の情報
    char filenameColumn[64];
    sprintf_s(filenameColumn, "Column%d.bin", stage);

    FILE* Columnfile;
    ////読み込み
    fopen_s(&Columnfile, filenameColumn, "rb");
    if (Columnfile == NULL) {
        perror("ファイルオープンエラー");
        return;
    }

    while (!feof(Columnfile))
    {
        Person pill;

        int succese = fread(&pill, sizeof(Person), 1, Columnfile);

        if (succese == 0)
        {
            break;
        }

        //柱の初期化
        Column* Columns = new Column();
        Columns->Initaliza();
        Columns->SetPos(VGet(pill.PosiX, pill.PosiY, pill.PosiZ));
        Columns->SetPosRist(VGet(pill.PosiX, pill.PosiY, pill.PosiZ));
        Columns->SetRadius(64.0f);
        Columns->SetTag(700);
        Columns->SetHp(40);
        Columns->SetLayer(3);
        Columns->SetTeam(1);
        Master::mpObjectManager->AddObjectList(Columns);

    }

    fclose(Columnfile);

    //壁の情報
    char filenamesidewall[64];
    sprintf_s(filenamesidewall, "Sidewall%d.bin", stage);

    FILE* filesidewall;
    fopen_s(&filesidewall, filenamesidewall, "rb");

    if (filesidewall == NULL)
    {
        perror("ファイルオープンエラー");
        return;
    }

    while (!feof(filesidewall))
    {
        WallPerson sidewall;

        int succese = fread(&sidewall, sizeof(WallPerson), 1, filesidewall);

        if (succese == 0)
        {
            break;
        }

        //初期化
        Wall* wall = new Wall(
            "Assets/sideWall.jpg",
            "Assets/newWall.jpg",
            VGet(sidewall.x, 0.0f, sidewall.z),
            sidewall.sizeX, sidewall.sizeY, sidewall.sizeZ,
            "Assets/Side.png",
            "Assets/NormalMap_No3.png"
        );

        wall->SetRadius(140.0f);
        wall->SetTag(1500);
        wall->SetLayer(2);
        wall->SetTeam(1);
        Master::mpObjectManager->AddObjectList(wall);

    }

    fclose(filesidewall);

    //横
    char filenameverticalwall[64];
    sprintf_s(filenameverticalwall, "Verticalwall%d.bin", stage);

    FILE* fileverticalwall;
    fopen_s(&fileverticalwall, filenameverticalwall, "rb");

    if (fileverticalwall == NULL)
    {
        perror("ファイルオープンエラー");
        return;
    }

    while (!feof(fileverticalwall))
    {
        WallPerson  verticalwall;

        int succese = fread(&verticalwall, sizeof(WallPerson), 1, fileverticalwall);

        if (succese == 0)
        {
            break;
        }

        //初期化
        Wall* wall2 = new Wall(
            "Assets/newWall.jpg",
            "Assets/sideWall.jpg",
            VGet(verticalwall.x, 0.0, verticalwall.z),
            verticalwall.sizeX, verticalwall.sizeY, verticalwall.sizeZ,
            "Assets/NormalMap_No3.png",
            "Assets/Side.png"
            );

        wall2->SetRadius(140.0f);
        wall2->SetTag(2500);
        wall2->SetLayer(2);
        wall2->SetTeam(1);
        Master::mpObjectManager->AddObjectList(wall2);
    }

    fclose(fileverticalwall);

    //ゴーレムの情報
    char filenameSpider[64];
    sprintf_s(filenameSpider, "Spider%d.bin", stage);

    FILE *fileSpider;
    fopen_s(&fileSpider, filenameSpider, "rb");

    if (fileSpider == NULL) {
        perror("ファイルオープンエラー");
        return;
    }

    while (!feof(fileSpider))
    {
        Person Spiders;

        int succese = fread(&Spiders, sizeof(Person), 1, fileSpider);

        if (succese == 0)
        {
            break;
        }

         //ゴーレムの初期化
         Spider *spider = new Spider();
         spider->Initaliza();
         spider->SetPos(VGet(Spiders.PosiX, Spiders.PosiY, Spiders.PosiZ));
         spider->SetTag(200);
         spider->SetHp(250);
         spider->SetRadius(70);
         spider->SetFSM(FSMFactory::Create("Spider", spider));
         spider->SetLayer(1);
         spider->SetTeam(1);
         spider->SetInvincible(0.0f);
         Master::mpObjectManager->AddObjectList(spider);

    }

    fclose(fileSpider);

    //ゴールの情報
    char filenamegoal[64];
    sprintf_s(filenamegoal, "Goal%d.bin", stage);

    FILE* goalfile;

    fopen_s(&goalfile, filenamegoal, "rb");
    if (goalfile == NULL)
    {
        perror("ファイルオープンエラー");
        return;
    }

    GoalPerson Goalperson;
    fread(&Goalperson, sizeof(Goalperson), 1, goalfile);

    //ゴール生成
    Goal* goal = new Goal();
    goal->Initaliza();
    goal->SetPos(VGet(Goalperson.PosiX, Goalperson.PosiY, Goalperson.PosiZ));
    goal->SetRotation(0.0f, Goalperson.RotationY, 0.0f);
    goal->SetTag(800);
    goal->SetRadius(80.0f);
    goal->SetLayer(1);
    goal->SetTeam(1);
    //オブジェクトリストの追加
    Master::mpObjectManager->AddObjectList(goal);

    fclose(goalfile);
    
    ////カメラの初期化
    Master::mpCamera->Initaliza(player);


//壁
//左右の壁
//枠用
////////////////////////////////////////////

    //枠
    const float MAP_SIZE = 7000.0f;
    const float HALF = MAP_SIZE * 0.5f;
    const float WALL_SIZE = 450.0f;
    int WALL_COUNT = static_cast<int>(ceil(MAP_SIZE / WALL_SIZE));

    float zPos = HALF + WALL_SIZE - 300;
    float xPos = HALF - WALL_SIZE + 400;
    for (int i = 0; i < WALL_COUNT; i++)
    {
        // 右
        StageFrame* right = new StageFrame(
            VGet(+HALF, 0.0f, zPos),
            VGet(0.0f, 300.0f, -WALL_SIZE),
            VGet(0.0f, 0.0f, 0.0f)
        );
        right->SetTag(1000);

        // 左
        StageFrame* left = new StageFrame(
            VGet(-HALF, 0.0f, zPos),
            VGet(0.0f, 300.0f, -WALL_SIZE),
            VGet(0.0f, 0.0f, 0.0f)
        );
        left->SetTag(1000);

        zPos -= WALL_SIZE;
    }

    ///////////////////////////////////////////////
    //////上下の壁
    ///////////////////////////////////////////////
    for (int i = 0; i < WALL_COUNT; i++)
    {
        // 上
        StageFrame* up = new StageFrame(
            VGet(xPos, 0.0f, +HALF),
            VGet(-WALL_SIZE, 300.0f, 0.0f),
            VGet(0.0f, 0.0f, 0.0f)
        );
        up->SetTag(2000);

        // 下
        StageFrame* down = new StageFrame(
            VGet(xPos, 0.0f, -HALF),
            VGet(-WALL_SIZE, 300.0f, 0.0f),
            VGet(0.0f, 0.0f, 0.0f)
        );
        down->SetTag(2000);

        xPos -= WALL_SIZE;
    }

    SetDrawScreen(DX_SCREEN_BACK);

}

//更新
void GameManager::Update()
{

    Master::mpCamera->Update();

    // カメラの情報を Effekseer に渡す（DXライブラリと同期）
    Effekseer_Sync3DSetting();

    // Effekseer の毎フレーム更新（必ず呼ぶ）
    UpdateEffekseer3D();

    // 座標更新
    for (auto obj : Master::mpObjectManager->GetObjectList())
    {
        obj->SetPos(VAdd(obj->GetPos(), VScale(obj->GetDir(), obj->GetSpeed())));
    }


    Master::mpObjectManager->Update();

}

//描画
void GameManager::Draw()
{
    
    Master::mpObjectManager->Draw();
    
}


//終了処理
void GameManager::Finaliza()
{    
    // Effekseer終了処理
    Effkseer_End();

    Master::mpObjectManager->SetDeleteFlagAll();

}

