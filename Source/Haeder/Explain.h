#pragma once
#include "SceneBase.h"

class Explain :public SceneBase
{
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

    bool InputJoycon;

    //BGM
    int ExplainBGM;

public:
    Explain();   //コンストラクタ
    ~Explain();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理



};