#pragma once
#include "SceneBase.h"
#include "../Header/SkyBox.h"

class Explain :public SceneBase
{
private:

    //SkyBox関係
    SkyBox* m_skybox;
    int SkyboxPShandle;
    int SkyboxVShandle;

    //---画像の読み込み---//
    int Controller_Handle;
    int Keyboard_Handle;
    int SelectpictureR_Handle;
    int SelectpictureL_Handle;

    //---UI関係---//
    int TitleUIX;
    int ExplainUIX;
    int ExplainUIY;
    int ExplainUI[6];

    int TitleSelect;
    int ExplainSelect;
    int Explain_HandleX;
    int Explain_HandleY;

    //---カーソルの位置---//
    float SelectpictureL;
    float SelectpictureR;
    float SelectY;

    //---キー入力---//
    bool Right;
    bool Left;
    bool Decide;

    //---BGM---/
    int ExplainBGM;
    int ButtonMusic;

    //---切り替え---//
    bool ExplainFlag;

public:
    Explain();   //コンストラクタ
    ~Explain();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

};