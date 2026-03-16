#pragma once
#include "SceneBase.h"
#include "../Haeder/SkyBox.h"

class Explain :public SceneBase
{
private:

    //SkyBox関係
    SkyBox* m_skybox;
    int skyboxPShandle;
    int skyboxVShandle;

    //画像
    int Controller_Image;
    int Keyboard_Image;
    int SelectpictureR_Handle;
    int SelectpictureL_Handle;

    //UI
    int TitleUIX;
    int Explain_UIX;
    int Explain_UIY;
    int Explain_UI[6];

    int TitleSelect;
    int ExplainSelect;

    //キー入力
    bool right;
    bool left;
    bool enter;

    //カーソルの位置
    float SelectpictureL;
    float SelectpictureR;
    float SelectY;

    //BGM
    int ExplainBGM;
    int ButtonMusic;

    //切り替え
    bool ExplainFlag;

public:
    Explain();   //コンストラクタ
    ~Explain();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

};