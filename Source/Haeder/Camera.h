#pragma once

#include "DxLib.h"

//前方宣言
class Player;

//カメラ　クラス
class Camera
{
private:
    float mfHorizontalAngle;  //水平方向アングル
    float mfVerticalAngle;    //垂直方向アングル

    VECTOR mvPositon;         //カメラの位置
    VECTOR mvLookAtPositon;   //カメラの注意点

    Player *mpPlayer;         //プレイヤーのポインタ

    const float ANGLE_SPEED = 3.0f;

    //コントローラー
    int Pad;
    DINPUT_JOYSTATE input;


public:
    Camera();
    ~Camera();

    void Initaliza(Player* player);
    void Update();

    //横アングルの向き
    float GetHorizontalAngle() { return mfHorizontalAngle;}
    //縦アングルの向き
    float GetVerticalAmgle() { return mfVerticalAngle;}

    VECTOR GetPosition() { return mvPositon; }
    VECTOR GetLookAtPosition() { return mvLookAtPositon; }

};