#include "DxLib.h"
#include "../Haeder/MagicBoard.h"
#include "../Haeder/AttackBoard.h"

//コンストラクタ
MagicBoard::MagicBoard(const char *filename) : Object(),mnMagicBoard(-1)
{
    //読み込み(遠距離武器)
    mnMagicBoard = LoadGraph("Assets/flame.png");
}

//デストラクタ
MagicBoard::~MagicBoard()
{
}

//初期化
void MagicBoard::Initaliza()
{

}

//更新
void MagicBoard::Update()
{
}

//描画
void MagicBoard::Draw()
{

}

//終了処理
void MagicBoard::Finaliza()
{
    DeleteGraph(mnMagicBoard);

}