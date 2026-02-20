#pragma once
#include "../Haeder/SceneBase.h"

class Menu : public SceneBase
{
public:
    Menu();   //コンストラクタ
    ~Menu();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理


private:
    //右の頂点
    float TriangleLeftX;
    float TriangleLeftY;

    //下の頂点
    float TriangleUnderX;
    float TriangleUnderY;

    //上の頂点
    float TriangleUpX;
    float TriangleUpY;

    //セレクトの制限
    //上
    float MaxUp;

    //下
    float MaxUnder;

    //文字を前に出す
    float StringGame;
    float StringTitle;
    float StringStagi;
    float StringEnd;

    //BGM
    int GameOverBGM;
    int ButtonMusic;

    bool InputJoycon;

};