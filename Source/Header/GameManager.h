#pragma once

#include "DxLib.h"
#include <vector>

class GameManager
{
private:

    bool GameLoop;


public:
    GameManager(); //コンストラクタ
    ~GameManager(); //デストラクタ

    void Initaliza();  //初期化処理
    void Finaliza();   //終了処理
    void Update();     //更新処理
    void Draw();       //描画処理

    bool end;


    bool isGameLoop() { return GameLoop; }

    void EndGameLoop() { GameLoop = 0; }

};
