#pragma once
#include "DxLib.h"
#include <map>
#include <list>
#include <vector>

#include "../Haeder/IState.h"

//状態のリスト
enum PLAYER_STATE
{
	PLAYER_STATE_IDLE,        //待機状態
	PLAYER_STATE_WALK,        //歩く
	PLAYER_STATE_RUN,         //走る
	PLAYER_STATE_ATTACK,      //攻撃
	PLAYER_STATE_SWORDATTACK, //剣の攻撃
	PLAYER_STATE_PICKITEM,    //拾う
	PLAYER_STATE_DAMAGE,      //ダメージを受ける
	PLAYER_STATE_DEATH,       //ゲームオーバー

	PLAYER_STATE_NUM

};

//待機状態
class PSIdle : public IState
{
private:
	VECTOR attackOffset;
	VECTOR attackPos;

public:
	PSIdle() = default;
	~PSIdle() = default;

	void OnEnter(Object* parent) override;
	void OnExit(Object* parent) override;
	int Update(Object* parent) override;
};

//歩く
class PSWalk : public IState
{
private:
	VECTOR attackOffset;
	VECTOR attackPos;

public:
	PSWalk() = default;
	~PSWalk() = default;

	void OnEnter(Object* parent) override;
	void OnExit(Object* parent) override;
	int Update(Object* parent) override;

};

//走る
//壊す
class PSAttack : public IState
{
public:
	PSAttack() = default;
	~PSAttack() = default;

	void OnEnter(Object* parent) override;
	void OnExit(Object* parent) override;
	int Update(Object* parent) override;

};

//拾う
class PSPicitem : public IState
{
public:
	PSPicitem() = default;
	~PSPicitem() = default;

	void OnEnter(Object* parent) override;
	void OnExit(Object* parent) override;
	int Update(Object* parent) override;
};

//ダメージを受ける
class PSDamege : public IState
{
public:
	PSDamege() = default;
	~PSDamege() = default;

	void OnEnter(Object* parent) override;
	void OnExit(Object* parent) override;
	int Update(Object* parent) override;
};

//ゲームオーバー
class PSDeath : public IState
{
public:
	PSDeath() = default;
	~PSDeath() = default;

	void OnEnter(Object* parent) override;
	void OnExit(Object* parent) override;
	int Update(Object* parent) override;
};
