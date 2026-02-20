#pragma once

#include "../Haeder/Object.h"

//インターフェース
class IState
{
public:
	IState() = default;
	virtual ~IState() = default;

	//自分の状態に変わるときに動かす（自分の状態の初期化をする関数）
	virtual void OnEnter(Object* parent) = 0;

	//自分の状態から変わるときに動かす（自分の状態の終了処理をする関数）
	virtual void OnExit(Object* parent) = 0;

	//状態の更新
	virtual int Update(Object* parent) = 0;

};