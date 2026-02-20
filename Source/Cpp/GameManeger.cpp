/*
　　　ゲームマネージャー
*/

//インクルードファイル
#include "DxLib.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManeger.h"
#include "../Haeder/Player.h"
#include "../Haeder/Camera.h"

const float LINE_AREA_AIZE = 10000.0f;  //!<ラインを描く範囲
const int   LINE_NUM = 50;              //

/**
*  @fn コンストラクタ
*/
GameManeger::GameManeger()
{
}

/**
*  @fn デストラクタ
*/
GameManeger::~GameManeger()
{
}

/**
*  @fn 初期化
*/
void GameManeger::Initaliza()
{
    mpObjectManager = new ObjectManager();

    //プレイヤーの初期化
    Player *player = new Player();
    player->Initaliza();

    //カメラの初期化
    Master::mpCamera->Initaliza(player);

    SetDrawScreen(DX_SCREEN_BACK);

}

/**
*  @fn 更新
*/
void GameManeger::Update()
{
    mpObjectManager->Update();

    Master::mpCamera->Update();

}

/**
*  @fn 描画
*/
void GameManeger::Draw()
{
    ClearDrawScreen();

    mpObjectManager->Draw();

    //　位置が分かるように地面にラインを描画する
    {
        VECTOR pos1;
        VECTOR pos2;

        //SetUseZBufferFlag(true);

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

    ScreenFlip();
}

/**
*  @fn 終了処理
*/
void GameManeger::Finaliza()
{
    delete mpObjectManager;

}