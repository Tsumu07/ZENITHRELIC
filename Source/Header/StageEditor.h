#ifndef STAGEEDITOR_H
#define STAGEEDITOR_H
#include "DxLib.h"
#pragma once

class ObjectManager;
class SceneManager;

//ステージエディターの画面の幅と高さ
#define SCREEN_WIDTH     (1280)
#define SCREEN_HEIGHT    (720)

//オブジェクトを移動させる際の基本速度
#define MOVE_BASE_SPEED  (12.5f)

//オブジェクトの拡大率を変化させる際の基本速度
#define SCALE_BASE_SPEED (0.025f)

//オブジェクトの向きを変化させる際の基本速度
#define ANGLE_BASE_SPEED (0.0436)

//オブジェクトを追加する際のカメラからの距離
#define ADD_UNIT_DISTANCE

//編集モード
typedef enum _EEditModel
{
    EEditModel_CharaEdit,            //キャラ編集モード
    EEditModel_ObjectEdit,           //オブジェクト編集モード
    EEditModel_EventEdit,            // イベント編集モード
    EEditModel_ClearConditionEdit,   // クリア条件編集モード

    EEditModel_Num                   //編集モードの数
}EEditModel;

// カメラの情報
typedef struct _SCameraData
{
    // 移動速度
    int         Speed;
    float       SpeedF;

    // 座標
    VECTOR      Position;

    // 向き( 水平角度と垂直角度 )
    float       HAngle;
    float       VAngle;

    // 正面方向のベクトル
    VECTOR      Direction;

    // カメラの左方向のベクトル( y軸成分は０にしたもの )
    VECTOR      Left;

    // カメラの正面方向のベクトル( y軸成分は０にしたもの )
    VECTOR      Front;
} SCameraData;

// マウスの情報
typedef struct _SMouseData
{
    // １フレーム前の座標
    int         BackX;
    int         BackY;

    // クリックされた瞬間のボタン入力情報
    int         EdgeInput;

    // クリックされた瞬間の座標
    int         ClickPosX;
    int         ClickPosY;

    // クリックされた瞬間の３Ｄ空間上の手前座標と奥座標
    VECTOR      ClickPosNear;
    VECTOR      ClickPosFar;
} SMouseData;

// ステージエディターの情報
typedef struct _SStageEditorData
{
    // 編集モード
    EEditModel   EditModel;

    // フレーム時間計測用変数
    LONGLONG    TimeTemp;

    // 現在のフレームで経過させる時間
    float       StepTime;

    // カメラ情報
    SCameraData Camera;

    // マウス情報
    SMouseData  Mouse;

    // 編集対象の明滅処理用カウンタ
    float       TargetColorCounter;

    // 編集対象の明滅色
    COLOR_F     BrinkColor;

    // 移動速度
    int         MoveSpeed;
    float       MoveSpeedF;

    // 角度変更速度
    int         AngleSpeed;
    float       AngleSpeedF;

    // 拡大率変更速度
    int         ScaleSpeed;
    float       ScaleSpeedF;

    // セーブ完了表示時間
    float       SaveCompDispTime;
} SStageEditorData;

extern SStageEditorData g_SEData;

// ステージエディターのメイン処理
//     戻り値 : 正常に処理が完了したかどうか
//              ( true : 正常に処理を完了した   false : エラーが発生した )
extern bool StageEditor_Main(void);

// ステージのデータを読み込む
//     戻り値 : ステージの読み込みが成功したか( true:成功した  false:失敗した )
extern bool LoadStage(
    // 読み込むステージの番号
    int StageNumber
);

// ステージのデータを保存する
//     戻り値 : セーブが成功したかどうか( true:成功した  false:失敗した )
extern bool SaveStage(void);

// カメラの注視点のセットアップを行う
extern void SetupTargetLookAtCamera(void);

#endif