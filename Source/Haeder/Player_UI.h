#pragma once
#include "Object.h"

class Player_UI : public Object
{
private:

    int LoadShader;
    int Frame;
    int SlotHandle;

    float PlayerHp;
    float PlayerMaxHp;
    float PlayerHpOld;

    VERTEX2DSHADER m_vertices[4];

    WORD m_indices[6];

    Object* GetPlayer;

public:
    Player_UI();   //コンストラクタ
    ~Player_UI();  //デストラクタ

    void Initaliza(); //初期化
    void Update();    //更新
    void Draw();      //描画
    void Finaliza();  //終了処理

};