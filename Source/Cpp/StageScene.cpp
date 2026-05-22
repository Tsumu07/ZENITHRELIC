#include "Dxlib.h"
#include "../Header/StageScene.h"
#include "../Header/SceneBase.h"
#include "../Header/SceneManager.h"
#include "../Header/GameManager.h"
#include "../Header/ResourceManeger.h"
#include "../Header/ObujectManager.h"
#include "../Header/CheckKey.h"
#include "../Header/Object.h"
#include "../Header/Player.h"
#include "../Header/Wall.h"
#include "../Master.h"
#include <math.h>
#include <string>

// 移動速度
const float MOVESPEED = 100.0f;

const float CAMERA_ANGLE_SPEED = 3.0f;

// カメラの注視点の高さ
const float CAMERA_LOOK_AT_HEIGHT = 400.0f;

// カメラと注視点の距離
const float CAMERA_LOOK_AT_DISTANCE = 1150.0f;

const float LINE_AREA_AIZE = 7000.0f;   //!<ラインを描く範囲
const int   LINE_NUM = 50;              //

//コンストラクタ
Stage::Stage()
:StageGuide_Controller(-1)
,StageGuide_Keyboard(-1)
,Save_Handle(-1)
,Warn_Handle(-1)
,Cursor_Handle(-1)
,Position(VGet(0.0f,0.0f,0.0f))
,PositionOld(VGet(0.0f,0.0f,0.0f))
,MoveFlag(-1)
,Angle(0.0f)
,CameraHAngle(0.0f)
,CameraVAngle(0.0f)
,MoveVector(VGet(0.0f,0.0f,0.0f))
,SinParam(0.0f)
,CosParam(0.0f)
,vshandle(-1)
,pshandle(-1)
,SelectBoxX(-1)
,SelectBoxY(-1)
,SelectBoxUnderX(-1)
,SelectBoxUnderY(-1)
,EditorIcon()
,StageeditorUI()
,CursorX(0.0f)
,CursorY(0.0f)
,IconUIX(-1)
,IconUIY(-1)
,CursorRight(false)
,CursorLeft(false)
,Decide(false)
,Rotation(false)
,Delete(false)
,MoveRight(false)
,MoveLeft(false)
,MoveUp(false)
,MoveDown(false)
,ComeraRight(false)
,ComeraLeft(false)
,ComeraUp(false)
,ComeraDown(false)
,Back(false)
,SaveJustOpened(false)
,MaxRight(0.0f)
,MaxLeft(0.0f)
,PlayerSetPosition(VGet(0.0f,0.0f,0.0f))
,PlayerSetModel(-1)
,SpiderSetPositon(VGet(0.0f,0.0f,0.0f))
,SpiderSetModel(-1)
,SpiderModelList()
,SpiderModelPosition()
,PointSetPosition(VGet(0.0f,0.0f,0.0f))
,PointSetModel(-1)
,PointModelList()
,PointModelPosition()
,ColumnSetPosition(VGet(0.0f,0.0f,0.0f))
,ColumnSetModel(-1)
,ColumnModelList()
,ColumnModelPosition()
,GoalSetPosition(VGet(0.0f,0.0f,0.0f))
,GoalSetModel(-1)
,GoalRo(0.0f)
,Wall1Position(VGet(0.0f,0.0f,0.0f))
,WallList()
,WallRo(false)
,Wall2Position(VGet(0.0f,0.0f,0.0f))
,WallList2()
,LineX(-1)
,LineY(-1)
,Line()
,Pad()
,PlayerSelect(false)
,WallSelect(false)
,Wall2Select(false)
,SpiderSelect(false)
,PointSelect(false)
,GoalSelect(false)
,ColumnSelect(false)
,KeepSelect(false)
,PlayerSet(false)
,WallSet(false)
,Wall2Set(false)
,SpiderSet(false)
,PointSet(false)
,GoalSet(false)
,ColumnSet(false)
,PlayerWarn(false)
,ColumnWarn(false)
,GoalWarn(false)
,Save(false)
,CursorSave(-1)
,MaxRightSave(0.0f)
,MaxLeftSave(0.0f)
,saveSlot(-1)
,SelectSave_No1(-1)
,SelectSave_No2(-1)
,SelectSave_No1X(-1)
,SelectSave_No2X(-1)
,SelsectSaveY(-1)
,WarnCount(-1)
,GoalRotation(false)
,InputJoycon(false)
,vertex()
,index()
,ButtonMusic(-1)
,EditerBGM(-1)
,SetSE(-1)
,SaveSE(-1)
,SaveCompleted(-1)
,WarnSE(-1)
,DeleteSE(-1)
{
}

//デストラクタ
Stage::~Stage()
{
}

//初期化
void Stage::Initaliza()
{

    //---画像の読み込み---//
    StageGuide_Controller = LoadGraph("Assets/StageGuide_Controller.png");
    StageGuide_Keyboard = LoadGraph("Assets/StageGuide_Keyboard.png");
    Save_Handle = LoadGraph("Assets/Save.png");
    Warn_Handle = LoadGraph("Assets/Warn.png");
    Cursor_Handle = LoadGraph("Assets/corsol.png");

    SetUseLighting(true);
    SetGlobalAmbientLight(GetColorF(0.0f, 0.0f, 0.0f, 1.0f));

    // 頂点シェーダーを読み込む
    vshandle = LoadVertexShader("cso/DefaultVS.cso");

    // ピクセルシェーダーを読み込む
    pshandle = LoadPixelShader("cso/WallPS.cso");

    //---サウンドの読み込み---//
    //BGM
    EditerBGM = LoadSoundMem("Musics/Title.mp3");

    //ボタン
    ButtonMusic = LoadSoundMem("Musics/Button.mp3");

    //置いた音
    SetSE = LoadSoundMem("Musics/Set.mp3");

    //セーブボタン
    SaveSE = LoadSoundMem("Musics/Save.mp3");

    //セーブ完了
    SaveCompleted = LoadSoundMem("Musics/SaveCompleted.mp3");

    //警告音 
    WarnSE = LoadSoundMem("Musics/Warning.mp3");

    //消す音
    DeleteSE = LoadSoundMem("Musics/Cancel.mp3");
    
    ChangeVolumeSoundMem(170, EditerBGM);

    //BGM再生
    PlaySoundMem(EditerBGM, DX_PLAYTYPE_LOOP);

    //カーソル
    CursorX = 0.0f;
    CursorY = 60.0f;

    //アイコン
    IconUIX = 140.0f;
    IconUIY = 50.0f;

    //右
    MaxRight = 1560.0f;

    //左
    MaxLeft = 0.0f;

    // カメラの向きを初期化
    CameraHAngle = 0.0f;
    CameraVAngle = 40.0f;

    // 向きを初期化
    Angle = 0.0f;

    // 中心
    Position = VGet(0.0f, 0.0f, 0.0f);

    // カメラのクリッピング距離を設定
    SetCameraNearFar(1.0f, 3500.0f);

    SetUseZBufferFlag(TRUE);
    SetWriteZBufferFlag(TRUE);

    //選んだか
     PlayerSelect = false;
     WallSelect = false;
     Wall2Select = false;
     SpiderSelect = false;
     PointSelect = false;
     ColumnSelect = false;

     //置いたか
     PlayerSet = false;
     WallSet = false;
     Wall2Set = false;
     SpiderSet = false;
     PointSet = false;
     ColumnSet = false;

     //回転(ドア)
     GoalRotation = false;

     //警告の表示
     PlayerWarn = false;
     ColumnWarn = false;
     GoalWarn = false;

     //---複数保存フラグ
     Save = false;

     CursorSave = 150.0f;

     //選択の制限
     //右
     MaxRightSave = 1050.0f;

     //左
     MaxLeftSave = 150.0f;

     //警告表示時間
     WarnCount = 0.0f;

     //コントローラの制御
     InputJoycon = false;

    SetBackgroundColor(150, 150, 150);

    SelectBoxX = 310.0f;
    SelectBoxUnderX = 329.0f;
    SelectBoxY = 230.0f;
    SelectBoxUnderY = 249.0f;

    LineX = 30.0f;
    LineY = 50.0f;

    //コントローラー
    Pad = DX_INPUT_PAD1;

    //---モデルの読み込み---//
    //プレイヤー
    PlayerSetModel = MV1LoadModel("Resource/Player.x");

    //クモ
    SpiderSetModel = MV1LoadModel("Resource/Spider.x");

    //ポイント
    PointSetModel = MV1LoadModel("Resource/Swarm09.x");

    //柱
    ColumnSetModel = MV1LoadModel("Resource/archway_pillar02.x");

    //ゴール
    GoalSetModel = MV1LoadModel("Resource/PortalSeven.x");

    MV1SetRotationXYZ(PlayerSetModel, VGet(0.0f, DX_PI_F, 0.0f));

    LoadDivGraph("Assets/stageIcon.png", 6, 6, 1, 141.3f, 133, EditorIcon);
    LoadDivGraph("Assets/StageeditorUI.png", 4, 2, 2, 355, 117, StageeditorUI);
    saveSlot = 0;

    SelectSave_No1 = 0;
    SelectSave_No2 = 0;

    SelectSave_No1X = 300.0f;
    SelectSave_No2X = 1200.0f;

    SelsectSaveY = 400.0f;
    
}

//更新
void Stage::Update()
{
    SetBackgroundColor(150, 150, 150);

    // 移動ベクトルを初期化
    MoveVector = VGet(0.0f, 0.0f, 0.0f);

    SelectSave_No1 = 0;
    SelectSave_No2 = 0;

    //カーソルの通った場所
    PositionOld = Position;

    //常にfalse
    PlayerSelect = false;
    SpiderSelect = false;
    PointSelect = false;
    GoalSelect = false;
    ColumnSelect = false;
    WallSelect = false;
    Wall2Select = false;
    KeepSelect = false;

    DINPUT_JOYSTATE input;

    //--------------------------------
    // 入力取得
    //--------------------------------
    GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
    //コントローラの制御
    if (input.Y == 0 && input.X == 0)
    {
        InputJoycon = false;
    }

    CursorRight = (CheckDownController(PAD_INPUT_6) || CheckDownKey(KEY_INPUT_E));
    CursorLeft = (CheckDownController(PAD_INPUT_5) || CheckDownKey(KEY_INPUT_Q));
    Decide = (CheckDownController(PAD_INPUT_2) || CheckDownKey(KEY_INPUT_SPACE));
    Rotation = (input.Z != 0 || CheckHitKey(KEY_INPUT_F));
    Delete = (CheckDownController(PAD_INPUT_4) != 0 || CheckDownKey(KEY_INPUT_LSHIFT));

    MoveRight = (input.X >= 500.0f || CheckDownKey(KEY_INPUT_D));
    MoveLeft = (input.X <= -500.0f || CheckDownKey(KEY_INPUT_A));
    MoveUp = (input.Y <= -500.0f || CheckDownKey(KEY_INPUT_W));
    MoveDown = (input.Y >= 500.0f || CheckDownKey(KEY_INPUT_S));

    ComeraRight = (input.Rx > 0 || CheckDownKey(KEY_INPUT_RIGHT));
    ComeraLeft = (input.Rx < 0 || CheckDownKey(KEY_INPUT_LEFT));
    ComeraUp = (input.Ry > 0 || CheckDownKey(KEY_INPUT_UP));
    ComeraDown = (input.Ry < 0 || CheckDownKey(KEY_INPUT_DOWN));
    Back = (CheckDownController(PAD_INPUT_1)|| CheckDownKey(KEY_INPUT_R));

    if (Save == false)
    {
        if (Back)
        {
            Master::mpSceneManager->ChangeScene(SceneName::TitleScene);
        }

        //右
        if (CursorRight)
        {
            PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

            CursorX += 260.0f;

            //一番右
            if (CursorX > MaxRight)
            {
                CursorX = MaxLeft;
            }

        }

        //左
        if (CursorLeft)
        {
            PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

            CursorX -= 260.0f;

            //一番左
            if (CursorX < MaxLeft)
            {
                CursorX = MaxRight;
            }
        }

        //プレイヤー
        if (CursorX >= 0.0f && CursorX < 260.0f)
        {
            PlayerSelect = true;
        }

        //クモ
        else if (CursorX >= 260.0f && CursorX < 520.0f)
        {
            SpiderSelect = true;
        }

        //柱
        else if (CursorX >= 520.0f && CursorX < 780.0f)
        {
            ColumnSelect = true;
        }

        //壁
        else if (CursorX >= 780.0f && CursorX < 1040.0f)
        {
            WallSelect = true;
        }

        //ポイント
        else if (CursorX >= 1040.0f && CursorX < 1300.0f)
        {
            PointSelect = true;
        }

        //ドア
        else if (CursorX >= 1300.0f && CursorX < 1560.0f)
        {
            GoalSelect = true;
        }

        //保存
        else if (CursorX >= 1560.0f && CursorX < 1820.0f)
        {
            KeepSelect = true;
        }

        //Bボタン(押された瞬間だけ)
        if (Decide)
        {
            //プレイヤー(ポジション)
            if (PlayerSelect == true)
            {
                //SE
                PlaySoundMem(SetSE, DX_PLAYTYPE_BACK);

                //カーソルの移動前の座標を取得
                PlayerSetPosition = PositionOld;

                MV1SetPosition(PlayerSetModel, PlayerSetPosition);

                MV1SetScale(PlayerSetModel, VGet(80.0f, 80.0f, 80.0f));

                //表示
                PlayerSet = true;

            }

            //クモ(ポジション)
            if (SpiderSelect == true)
            {
                //SE
                PlaySoundMem(SetSE, DX_PLAYTYPE_BACK);

                //カーソルの移動前の座標を取得
                SpiderSetPositon = PositionOld;

                CreateObject(SpiderSetModel, SpiderModelList, SpiderModelPosition, SpiderSetPositon);

                //表示
                SpiderSet = true;

            }

            //敵のポイント
            if (PointSelect == true)
            {
                //SE
                PlaySoundMem(SetSE, DX_PLAYTYPE_BACK);

                //カーソルの移動前の座標を取得
                PointSetPosition = PositionOld;

                CreateObject(PointSetModel, PointModelList, PointModelPosition, PointSetPosition);

                //表示
                PointSet = true;

            }

            //柱(ポジション)
            if (ColumnSelect == true)
            {
                //SE
                PlaySoundMem(SetSE, DX_PLAYTYPE_BACK);

                //カーソルの移動前の座標を取得
                ColumnSetPosition = PositionOld;

                CreateObject(ColumnSetModel, ColumnModelList, ColumnModelPosition, ColumnSetPosition);

                //表示
                ColumnSet = true;

            }

            //ゴール(ポジション)
            if (GoalSelect == true)
            {
                //SE
                PlaySoundMem(SetSE, DX_PLAYTYPE_BACK);

                //カーソルの移動前の座標を取得
                GoalSetPosition = PositionOld;

                MV1SetPosition(GoalSetModel, GoalSetPosition);

                //ゴール(回転)
                if (Rotation)
                {
                    MV1SetRotationXYZ(GoalSetModel, VGet(0.0f, 0.0f, 0.0f));

                    GoalRotation = false;
                }

                if (input.Z == 0)
                {
                    MV1SetRotationXYZ(GoalSetModel, VGet(0.0f, 4.757f, 0.0f));

                    GoalRotation = true;
                }

                //表示
                GoalSet = true;
            }

            //左右の壁
            if (WallSelect == true)
            {
                //SE
                PlaySoundMem(SetSE, DX_PLAYTYPE_BACK);

                if (Rotation)
                {
                    //座標
                    Wall1Position = Position;

                    //左右
                    Wall* wall1 = new Wall(
                        "Assets/Side.jpg",
                        "Assets/Wall.jpg",
                        Wall1Position,
                        30.0f,    // 半サイズ X（厚み）
                        150.0f,   // 半サイズ Y（高さ）
                        250.0f,    // 半サイズ Z（奥行き）
                        "Assets/NomalMap_Side.png",
                        "Assets/NormalMap_Wall.png"
                    );

                    wall1->SetTag(1500);

                    WallList.push_back(wall1);

                    //表示
                    WallSet = true;

                }

                else
                {    
                    //座標
                    Wall2Position = Position;

                    //上下
                    Wall* wall2 = new Wall(
                        "Assets/Wall.jpg",
                        "Assets/Side.jpg",
                        Wall2Position,
                        250.0f,   // 半X（横幅）
                        150.0f,   // 半Y（高さ）
                        30.0f,     // 半Z（厚み)
                        "Assets/NomalMap_Side.png",
                        "Assets/NormalMap_Wall.png"
                    );

                    wall2->SetTag(2500);

                    WallList2.push_back(wall2);

                    //表示
                    Wall2Set = true;

                }

            }

            //保存処理
            if (KeepSelect == true)
            {
                //最低限のオブジェクトを置かせる(プレイヤー,カギ,ドア)
                //置いていなければ保存せずに警告を表示する
                if (PlayerSet == false)
                {
                    PlaySoundMem(WarnSE, DX_PLAYTYPE_BACK);

                    PlayerWarn = true;

                    WarnCount = 180.0f;

                    return;
                }

                if (GoalSet == false)
                {
                    PlaySoundMem(WarnSE, DX_PLAYTYPE_BACK);

                    GoalWarn = true;

                    WarnCount = 180.0f;

                    return;
                }

                ////SE
                PlaySoundMem(SaveSE, DX_PLAYTYPE_BACK);
                Save = true;
                SaveJustOpened = true;
            }
        }
    }

    if (Save == true)
    {

        if (SaveJustOpened)
        {
            SaveJustOpened = false;
            return;
        }

        //閉じる
        if (Back)
        {
            Save = false;
        }

        //右
        if (MoveRight && !InputJoycon)
        {
            PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

            CursorSave += 900.0f;

            InputJoycon = true;

        }

        //一番右
        if (CursorSave > MaxRightSave)
        {
            CursorSave = MaxLeftSave;
        }

        ////左
        if (MoveLeft && !InputJoycon)
        {
            PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);
            CursorSave -= 900.0f;

            InputJoycon = true;

        }

        //一番左
        if (CursorSave < MaxLeftSave)
        {
            CursorSave = MaxRightSave;
        }

        if (CursorSave >= MaxLeftSave && CursorSave < MaxRightSave)
        {
            saveSlot = 1;
            SelectSave_No1 = 1;
        }

        else if (CursorSave >= MaxRightSave && CursorSave < MaxRightSave + 10)
        {
            saveSlot = 2;
            SelectSave_No2 = 1;
        }

        if (Decide)
        {
            //SE
            PlaySoundMem(SaveCompleted, DX_PLAYTYPE_BACK);


            //プレイヤーの情報
            //書き込み
            char filenameplayer[64];
            sprintf_s(filenameplayer, "Stage Information/Player%d.bin", saveSlot);

            FILE* playerfile;
            if (fopen_s(&playerfile, filenameplayer, "wb") != 0)
            {
                perror("ファイルオープンエラー");
                return;
            }

            Person player = { "Player\n", PlayerSetPosition.x, 0.0f, PlayerSetPosition.z };
            fwrite(&player, sizeof(Person), 1, playerfile);
            fclose(playerfile);

            //クモの情報
            //書き込み
            char filenameSpider[64];
            sprintf_s(filenameSpider, "Stage Information/Spider%d.bin", saveSlot);

            FILE* Spiderfile;
            fopen_s(&Spiderfile, filenameSpider, "wb");
            if (Spiderfile == NULL)
            {
                perror("ファイルオープンエラー");
                return;
            }

            for (int i = 0; i < SpiderModelList.size(); i++)
            {
                Person Spider = { "Spider\n",SpiderModelPosition.at(i).x,0.0f,SpiderModelPosition.at(i).z };
                fwrite(&Spider, sizeof(Person), 1, Spiderfile);
            }

            fclose(Spiderfile);

            //敵の巡回ポインタの情報
            //書き込み
            char filenamePoint[64];
            sprintf_s(filenamePoint, "Stage Information/Point%d.bin", saveSlot);

            FILE* Pointfile;
            fopen_s(&Pointfile, filenamePoint, "wb");
            if (Pointfile == NULL)
            {
                perror("ファイルオープンエラー");
                return;
            }

            for (int i = 0; i < PointModelList.size(); i++)
            {
                Person Pointer = { "Pointer\n",PointModelPosition.at(i).x,200.0f,PointModelPosition.at(i).z };
                fwrite(&Pointer, sizeof(Person), 1, Pointfile);
            }

            fclose(Pointfile);

            //壊せる柱の情報
            //書き込み
            char filenameColumn[64];
            sprintf_s(filenameColumn, "Stage Information/Column%d.bin", saveSlot);

            FILE* Columnfile;
            fopen_s(&Columnfile, filenameColumn, "wb");
            if (Columnfile == NULL)
            {
                perror("ファイルオープンエラー");
                return;
            }

            for (int i = 0; i < ColumnModelList.size(); i++)
            {
                Person Column = { "Column\n", ColumnModelPosition.at(i).x,3.0f,ColumnModelPosition.at(i).z };
                fwrite(&Column, sizeof(Person), 1, Columnfile);
            }

            fclose(Columnfile);

            //ゴールの情報
            //書き込み

            if (GoalRotation == true)
            {
                GoalRo = 4.757f;
            }

            else
            {
                GoalRo = 0.0f;
            }

            char filenamegoal[64];
            sprintf_s(filenamegoal, "Stage Information/Goal%d.bin", saveSlot);

            FILE* goalfile;
            if (fopen_s(&goalfile, filenamegoal, "wb") != 0)
            {
                perror("ファイルオープンエラー");
                return;
            }

            GoalPerson Goal = { "Goal\n", GoalSetPosition.x, 0.0f, GoalSetPosition.z ,GoalRo };
            fwrite(&Goal, sizeof(GoalPerson), 1, goalfile);
            fclose(goalfile);

            //縦長の障害物の情報
            //書き込み
            char filenamesidewall[64];
            sprintf_s(filenamesidewall, "Stage Information/Sidewall%d.bin", saveSlot);

            FILE* sidewallfile;
            fopen_s(&sidewallfile, filenamesidewall, "wb");
            if (sidewallfile == NULL)
            {
                perror("ファイルオープンエラー");
                return;
            }

            std::vector<Object*> obj5 = Master::mpObjectManager->FindsByTag(1500);

            for (int i = 0; i < obj5.size(); i++)
            {
                Wall* wall = dynamic_cast<Wall*>(obj5.at(i));

                WallPerson sidewall = { wall->GetEditorPosition().x,0.0f,wall->GetEditorPosition().z,30.0f,150.0f,250.0f,sidewall.orientation = 0 };

                fwrite(&sidewall, sizeof(WallPerson), 1, sidewallfile);
            }

            fclose(sidewallfile);

            //横幅の障害物
            //書き込み
            char filenameverticalwall[64];
            sprintf_s(filenameverticalwall, "Stage Information/Verticalwall%d.bin", saveSlot);

            FILE* verticalwallfile;
            fopen_s(&verticalwallfile, filenameverticalwall, "wb");
            if (verticalwallfile == NULL)
            {
                perror("ファイルオープンエラー");
                return;
            }

            std::vector<Object*> obj6 = Master::mpObjectManager->FindsByTag(2500);

            for (int i = 0; i < obj6.size(); i++)
            {
                Wall* wall2 = dynamic_cast<Wall*>(obj6.at(i));
                WallPerson verticalewall = { wall2->GetEditorPosition().x,0.0f,wall2->GetEditorPosition().z,250.0f, 150.0f, 30.0f ,verticalewall.orientation = 1 };
                fwrite(&verticalewall, sizeof(WallPerson), 1, verticalwallfile);
            }

            fclose(verticalwallfile);

        }
    }

    //警告表示時間
    if (WarnCount > 0)
    {
        --WarnCount;
    }

    if (WarnCount <= 0)
    {
        WarnCount = 0;

        PlayerWarn = false;

        ColumnWarn = false;

        GoalWarn = false;
    }

    //選択したものを一つ削除
    if (Delete)
    {
        //SE
        PlaySoundMem(DeleteSE, DX_PLAYTYPE_BACK);

        //クモの削除
        if (SpiderSelect == true)
        {
            if (SpiderModelList.size() > 0)
            {
                SpiderModelList.pop_back();
            }
        }

        //ポイントの削除
        if (PointSelect == true)
        {
            if (PointModelList.size() > 0)
            {
                PointModelList.pop_back();
            }
        }

        if (ColumnSelect == true)
        {
            if (ColumnModelList.size() > 0)
            {
                ColumnModelList.pop_back();
            }
        }

        //左右の壁の削除
        if (WallSelect == true)
        {
            if (Rotation)
            {                
                if (WallList.size() > 0)
                {
                    Wall* W = WallList.back();

                    W->SetDeleteFlag(true);

                    WallList.pop_back();
                }

            }

            else
            {
                if (WallList2.size() > 0)
                {
                    Wall* W = WallList2.back();

                    W->SetDeleteFlag(true);

                    WallList2.pop_back();
                }


            }

        }

    }

    // 移動しているかどうかのフラグを倒す
    MoveFlag = FALSE;

    //移動処理
    if (!Save)
    {
        //右
        if ( MoveRight && !InputJoycon )
        {
            Angle = -90.0f - CameraHAngle;
            MoveFlag = TRUE;
            MoveVector.x += MOVESPEED;
            InputJoycon = true;
        }

        //左
        if (MoveLeft && !InputJoycon)
        {
            Angle = 90.0f - CameraHAngle;
            MoveFlag = TRUE;
            MoveVector.x -= MOVESPEED;
            InputJoycon = true;

        }

        // 上
        if (MoveUp && !InputJoycon)
        {
            Angle = 180.0f - CameraHAngle;
            MoveFlag = TRUE;
            MoveVector.z += MOVESPEED;
            InputJoycon = true;

        }

        //下
        if (MoveDown && !InputJoycon )
        {
            Angle = 0.0f - CameraHAngle;
            MoveFlag = TRUE;
            MoveVector.z -= MOVESPEED;
            InputJoycon = true;

        }

    }

    //フレームアウト
    //右
    if (Position.x > WINDOW_RIGHT)
    {
        Position.x = WINDOW_RIGHT;
    }

    //左
    if (Position.x < WINDOW_LEFT)
    {
        Position.x = WINDOW_LEFT;
    }

    // 上
    if (Position.z > WINDOW_TOP)
    {
        Position.z = WINDOW_TOP;
    }

    //下
    if (Position.z < WINDOW_UNDER)
    {
        Position.z = WINDOW_UNDER;
    }

    // 移動した場合は、カメラの水平角度を考慮した方向に座標を移動する
    if (MoveFlag == TRUE)
    {
        VECTOR TempMoveVector;

        // カメラの角度に合わせて移動ベクトルを回転してから加算
        SinParam = sin(CameraHAngle / 180.0f * DX_PI_F);
        CosParam = cos(CameraHAngle / 180.0f * DX_PI_F);
        TempMoveVector.x = MoveVector.x * CosParam - MoveVector.z * SinParam;
        TempMoveVector.y = 0.0f;
        TempMoveVector.z = MoveVector.x * SinParam + MoveVector.z * CosParam;

        Position = VAdd(Position, TempMoveVector);
    }

    //右にカメラを動かす
    if (ComeraRight)
    {
        CameraHAngle += CAMERA_ANGLE_SPEED;

        if (CameraHAngle >= 180.0f)
        {
            CameraHAngle -= 360.0f;
        }
    }

    //左にカメラを動かす
    if (ComeraLeft)
    {
        CameraHAngle -= CAMERA_ANGLE_SPEED;

        if (CameraHAngle <= -180.0f)
        {
            CameraHAngle += 360.0f;
        }
    }

    //上にカメラを動かす
    if (ComeraUp)
    {
        CameraVAngle += CAMERA_ANGLE_SPEED;

        if (CameraVAngle >= 80.0f)
        {
            CameraVAngle = 80.0f;
        }
    }

    //下にカメラを動かす
    if (ComeraDown)
    {
        CameraVAngle -= CAMERA_ANGLE_SPEED;

        if (CameraVAngle <= 0.0f)
        {
            CameraVAngle = 0.0f;
        }
    }

    // カメラの位置と向きを設定
    {
        VECTOR TempPosition1;
        VECTOR TempPosition2;
        VECTOR CameraPosition;
        VECTOR CameraLookAtPosition;

        // 注視点はキャラクターモデルの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
        CameraLookAtPosition = Position;
        CameraLookAtPosition.y += CAMERA_LOOK_AT_HEIGHT;

        // カメラの位置はカメラの水平角度と垂直角度から算出

        // 最初に垂直角度を反映した位置を算出
        SinParam = sin(CameraVAngle / 180.0f * DX_PI_F);
        CosParam = cos(CameraVAngle / 180.0f * DX_PI_F);
        TempPosition1.x = 0.0f;
        TempPosition1.y = SinParam * CAMERA_LOOK_AT_DISTANCE;
        TempPosition1.z = -CosParam * CAMERA_LOOK_AT_DISTANCE;

        // 次に水平角度を反映した位置を算出
        SinParam = sin(CameraHAngle / 180.0f * DX_PI_F);
        CosParam = cos(CameraHAngle / 180.0f * DX_PI_F);
        TempPosition2.x = CosParam * TempPosition1.x - SinParam * TempPosition1.z;
        TempPosition2.y = TempPosition1.y;
        TempPosition2.z = SinParam * TempPosition1.x + CosParam * TempPosition1.z;

        // 算出した座標に注視点の位置を加算したものがカメラの位置
        CameraPosition = VAdd(TempPosition2, CameraLookAtPosition);

        // カメラの設定に反映する
        SetCameraPositionAndTarget_UpVecY(CameraPosition, CameraLookAtPosition);

        int cameraCB = Master::mpResourceManager->GetConstBuff("Camera");
        CB_LIGHT_CAMERA* cb = (CB_LIGHT_CAMERA*)GetBufferShaderConstantBuffer(cameraCB);
        cb->CameraPos.x = CameraPosition.x;
        cb->CameraPos.y = CameraPosition.y;
        cb->CameraPos.z = CameraPosition.z;
        cb->CameraPos.w = 1.0f;
        VECTOR lightDir = VNorm(VGet(1.0f, -1.0f, 1.0f));
        cb->LightDir.x = lightDir.x;
        cb->LightDir.y = lightDir.y;
        cb->LightDir.z = lightDir.z;
        cb->LightDir.w = 0.0f;
        UpdateShaderConstantBuffer(cameraCB);
    }
}

//描画
void Stage::Draw()
{

    //　位置が分かるように地面にラインを描画する
    {
        VECTOR pos1;
        VECTOR pos2;

        pos1 = VGet(-LINE_AREA_AIZE / 2.0f, 0.0f, -LINE_AREA_AIZE / 2.0f);
        pos2 = VGet(-LINE_AREA_AIZE / 2.0f, 0.0f, LINE_AREA_AIZE / 2.0f);

        for (int i = 0; i <= LINE_NUM; i++)
        {
            DrawLine3D(pos1, pos2, GetColor(255, 255, 255));
            pos1.x += LINE_AREA_AIZE / LINE_NUM;
            pos2.x += LINE_AREA_AIZE / LINE_NUM;
        }

        pos1 = VGet(-LINE_AREA_AIZE / 2.0f, 0.0f, -LINE_AREA_AIZE / 2.0f);
        pos2 = VGet(LINE_AREA_AIZE / 2.0f, 0.0f, -LINE_AREA_AIZE / 2.0f);

        for (int i = 0; i <= LINE_NUM; i++)
        {
            DrawLine3D(pos1, pos2, GetColor(255, 255, 255));
            pos1.z += LINE_AREA_AIZE / LINE_NUM;
            pos2.z += LINE_AREA_AIZE / LINE_NUM;
        }

    }

    Master::mpObjectManager->Draw();

    //プレイヤーの座標
    if (PlayerSet == true)
    {
        MV1DrawModel(PlayerSetModel);
    }

    //クモの座標
    if (SpiderSet == true)
    {
        for (int i = 0; i < SpiderModelList.size(); i++)
        {
            MV1DrawModel(SpiderModelList.at(i));
        }
    }

    //ポイント
    if (PointSet == true)
    {
        for (int i = 0; i < PointModelList.size(); i++)
        {
            MV1DrawModel(PointModelList.at(i));
        }
    }


    //柱
    if (ColumnSet == true)
    {
        for (int i = 0; i < ColumnModelList.size(); i++)
        {
            MV1DrawModel(ColumnModelList.at(i));
        }

    }

    //シェーダーをセット
    SetUseVertexShader(vshandle);

    //横の壁の座標
    if (WallSet == true)
    {
        for (Wall* w : WallList)
        {
            w->Draw();
        }
    }

    //縦の壁の座標
    if (Wall2Set == true)
    {
        for (Wall* w : WallList2)
        {
            w->Draw();
        }
    }

    SetUseVertexShader(-1);
    SetUsePixelShader(-1);

    //ドア
    if (GoalSet == true)
    {
        MV1DrawModel(GoalSetModel);
    }
    
    if (GetJoypadNum())
    {
        DrawGraph(20.0f, 350.0f, StageGuide_Controller, true);
    }

    else
    {
        DrawGraph(20.0f, 350.0f, StageGuide_Keyboard, true);
    }


    //アイコンの表示
    for (int i = 0; i < 6; i++)
    {
        DrawGraph(IconUIX + i * 260, IconUIY, EditorIcon[i], true);
    }

    DrawGraph(1700.0f, 70.0f, Save_Handle, true);

    //出す場所
    DrawSphere3D(Position, 30.0f, 8, GetColor(255, 0, 0), GetColor(255, 0, 0), true);

    //警告表示
    if (PlayerWarn == true)
    {  
        DrawGraph(650.0f, 180.0f, Warn_Handle, true);
    }

    if (GoalWarn == true)
    {
        DrawGraph(650.0f, 180.0f, Warn_Handle, true);
    }

    if (Save == true)
    {
        DrawGraph(SelectSave_No1X, SelsectSaveY, StageeditorUI[0 + SelectSave_No1], true);
        DrawGraph(SelectSave_No2X, SelsectSaveY, StageeditorUI[2 + SelectSave_No2], true);
        DrawGraph(CursorSave, SelsectSaveY, Cursor_Handle, true);
        
    }

    DrawGraph(CursorX, CursorY, Cursor_Handle, true);

}

//終了処理
void Stage::Finaliza()
{
    DeleteGraph(StageGuide_Controller);
    DeleteGraph(StageGuide_Keyboard);
    DeleteGraph(Save_Handle);
    DeleteGraph(Warn_Handle);
    DeleteGraph(Cursor_Handle);

    DeleteSoundMem(EditerBGM);
    DeleteSoundMem(ButtonMusic);
    DeleteSoundMem(SetSE);
    DeleteSoundMem(SaveSE);
    DeleteSoundMem(SaveCompleted);
    DeleteSoundMem(WarnSE);
    DeleteSoundMem(DeleteSE);

    MV1DeleteModel(PlayerSetModel);
    MV1DeleteModel(SpiderSetModel);
    MV1DeleteModel(PointSetModel);
    MV1DeleteModel(ColumnSetModel);
    MV1DeleteModel(GoalSetModel);

    Master::mpObjectManager->SetDeleteFlagAll();
}

int Stage::CreateObject(int model, std::vector<int>& list, std::vector<VECTOR>& posList, VECTOR pos)
{
    int handle = MV1DuplicateModel(model);
    list.push_back(handle);
    posList.push_back(pos);

    MV1SetPosition(handle, pos);

    if (ColumnSelect)
    {
        MV1SetScale(handle, VGet(0.5f, 0.5f, 0.5f));

    }
    return handle;
}
