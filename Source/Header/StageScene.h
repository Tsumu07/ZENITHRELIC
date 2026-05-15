#pragma once
#include "SceneBase.h"
#include <vector>

class Player;
class Wall;


class Stage :public SceneBase
{
private:


    //---画像の読み込み---//
    int StageGuide_Controller;
    int StageGuide_Keyboard;
    int Save_Handle;
    int Warn_Handle;
    int Cursor_Handle;

    //---場所---//
    VECTOR Position;
    VECTOR PositionOld;
    int    MoveFlag;
    float  Angle;
    float  CameraHAngle;
    float  CameraVAngle;
    VECTOR MoveVector;
    float  SinParam;
    float  CosParam;
    int vshandle;
    int pshandle;

    //---カーソルの現在地---//
    int SelectBoxX;
    int SelectBoxY;
    int SelectBoxUnderX;
    int SelectBoxUnderY;

    //---UI---//
    int EditorIcon[6];
    int StageeditorUI[4];
    float CursorX;
    float CursorY;
    int IconUIX;
    int IconUIY;

    //---キー入力---//
    bool CursorRight;
    bool CursorLeft;
    bool Decide;
    bool Rotation;
    bool Delete;

    bool MoveRight;
    bool MoveLeft;
    bool MoveUp;
    bool MoveDown;

    bool ComeraRight;
    bool ComeraLeft;
    bool ComeraUp;
    bool ComeraDown;

    bool Back;

    bool SaveJustOpened;

    //---選択の制限---//
    //右
    float MaxRight;

    //左
    float MaxLeft;

    //---プレイヤーの座標---//
    VECTOR PlayerSetPosition;

    //---プレイヤーのモデル---//
    int PlayerSetModel;

    //---クモの座標---//
    VECTOR SpiderSetPositon;

    //---クモのモデル---//
    int SpiderSetModel;
    std::vector<int> SpiderModelList;
    std::vector<VECTOR> SpiderModelPosition;

    //---ポイントの座標---//
    VECTOR PointSetPosition;

    //---ポイントのモデル---//
    int PointSetModel;
    std::vector<int> PointModelList;
    std::vector<VECTOR> PointModelPosition;

    //---柱の座標---//
    VECTOR ColumnSetPosition;

    //---柱のモデル---//
    int ColumnSetModel;
    std::vector<int> ColumnModelList;
    std::vector<VECTOR> ColumnModelPosition;

    //---ゴールの座標---//
    VECTOR GoalSetPosition;

    //---//ゴールのモデル---//
    int GoalSetModel;

    float GoalRo;

    //---横の壁の座標---//
    VECTOR Wall1Position;

    std::vector<Wall*> WallList;


    //---//縦の壁の座標---//
    VECTOR Wall2Position;

    std::vector<Wall*> WallList2;

    int LineX;
    int LineY;
    int Line[50];

    int Pad;
    //---回転している---//
    bool WallRo;

    //---移動上限---//
    //左
    const int WINDOW_LEFT = -3500.0f;
    const int WINDOW_RIGHT = 3500.0f;
    const int WINDOW_TOP = 3500.0f;
    const int WINDOW_UNDER = -3500.0f;

    //---選んだか---//
    bool PlayerSelect;
    bool WallSelect;
    bool Wall2Select;
    bool SpiderSelect;
    bool PointSelect;
    bool GoalSelect;
    bool ColumnSelect;
    bool KeepSelect;

    //---置いたフラグ---//
    bool PlayerSet;
    bool WallSet;
    bool Wall2Set;
    bool SpiderSet;
    bool PointSet;
    bool GoalSet;
    bool ColumnSet;

    //---警告フラグ---//
    bool PlayerWarn;
    bool ColumnWarn;
    bool GoalWarn;

    //---複数保存---//
    bool Save;

    //---保存選択---//
    int CursorSave;

    //---右---//
    float MaxRightSave;

    //---左---//
    float MaxLeftSave;

    //---セーブ番号---//
    int saveSlot;

    int SelectSave_No1;
    int SelectSave_No2;

    int SelectSave_No1X;
    int SelectSave_No2X;

    int SelsectSaveY;

    //---どれくらい表示するか---//
    int WarnCount;

    //---回転(ゴール)---//
    bool GoalRotation;

    //---コントローラの制御---//
    bool InputJoycon;

    // 頂点 ＝ VERTEX
    // 4頂点分のデータをセット
    VERTEX3D vertex[4];
    WORD index[6];

    //---BGM---//
    int ButtonMusic;
    int EditerBGM;
    int SetSE;
    int SaveSE;
    int SaveCompleted;
    int WarnSE;
    int DeleteSE;

public:
    Stage();   //コンストラクタ
    ~Stage();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

    int CreateObject(int model, std::vector<int>& list, std::vector<VECTOR>& posList, VECTOR pos);

};