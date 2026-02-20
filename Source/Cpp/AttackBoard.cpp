#include "DxLib.h"
#include "../Haeder/AttackBoard.h"

//コンストラクタ
AttackBoard::AttackBoard(const char *filename) : Object(), mnAttackBoard(-1)
{
    //読み込み(近距離武器)
    //mnAttackBoard = LoadGraph("");
}

//デストラクタ
AttackBoard::~AttackBoard()
{
}

//初期化
void AttackBoard::Initaliza()
{
}

//更新
void AttackBoard::Update()
{
}
//描画
void AttackBoard::Draw()
{

}

//終了処理
void AttackBoard::Finaliza()
{
    DeleteGraph(mnAttackBoard);
}