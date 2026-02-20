#pragma once
#pragma once
#include"DxLib.h"
#include <map>
#include <list>
#include <vector>

#include "../Haeder/IState.h"

//障害物のデータ
typedef struct
{
	VECTOR pos;     // 障害物の位置
	float radius;   // 障害物の半径

}ObstacleData;

//状態のリスト
enum Spider_STATE
{
	Spider_STATE_MOVE_PATROL, //ポイントによる巡回
	Spider_STATE_MOVE_POINT,  //ポイントへ移動
	Spider_STATE_CHASE,       //追跡状態
	Spider_STATE_RETURN,      //帰還状態
	Spider_STATE_ATTACK,      //攻撃状態
	Spider_STATE_DAMAGE,      //ダメージ状態
	Spider_STATE_DEATH,       //死亡状態

	Spider_STATE_NUM

};


//ポイントによる巡回
class GSMovePatrol : public IState
{
private:
	VECTOR goal;                    //目的地
	std::vector<VECTOR> PointsRist; //監視ポイントリスト
	std::vector<float> stayTimes;   //各ポイントのプレイヤーの滞在時間
	float stayThreshold;            //ゴーレムが追いかけるまで
	int targetIndex;                //ゴーレムが向かうべきポイント
	int randomIndex;                //ランダム巡回ターゲット
	float waitTimer;                //ゴーレムの待機タイマー
	float waitThreshld;             //ランダム移動までの待機士官

public:
	GSMovePatrol() = default;
	~GSMovePatrol() = default;

	void OnEnter(Object* parent);
	void OnExit(Object* parent);
	int Update(Object* parent);

};

//ポイントに移動
class GSMovePoint : public IState
{
private:

	VECTOR goal;                //目的地
	std::vector<VECTOR> m_path; //経路点のリスト
	int m_pathIndex;            //どの経路を目指しているのか(インデックス)
	float m_repathTimer;        //再検索のタイマー
	std::vector<VECTOR> patrolPoints;
	std::vector<float> stayTimes;
	float stayThreshold;

	//経路探索パラメータ
	float step;           // 経路探索用のグリッド1マスの大きさ
	float agentRadius;    // ゴーレム自体の半径（障害物回避用）
	float repathInterval; // 経路を再計算するフレーム間隔
	float arriveDist;     // 経路点に「到達した」とみなす距離
public:
	GSMovePoint() = default;
	~GSMovePoint() = default;

	void OnEnter(Object* parent);
	void OnExit(Object* parent);
	int Update(Object* parent);
};

//追跡
class GSChase : public IState
{
private:
	std::vector<VECTOR> m_path;//経路点のリスト
	int m_pathIndex;		   //どの経路を目指しているのか(インデックス)
	float m_repathTimer;	   //再検索のタイマー


	//経路探索パラメータ
	float step;           // 経路探索用のグリッド1マスの大きさ
	float agentRadius;    // ゴーレム自体の半径（障害物回避用）
	float repathInterval; // 経路を再計算するフレーム間隔
	float safetyMargin;   //余裕を持たせる
	float arriveDist;     // 経路点に「到達した」とみなす距離

	float attack;         //攻撃範囲
	float playerlose;     //見失う距離

public:
	GSChase() = default;
	~GSChase() = default;

	void OnEnter(Object* parent);
	void OnExit(Object* parent);
	int Update(Object* parent);
};

//攻撃
class GSAttack : public IState
{
private:
public:
	GSAttack() = default;
	~GSAttack() = default;

	void OnEnter(Object* parent);
	void OnExit(Object* parent);
	int Update(Object* parent);

};

//帰還
class GSReturn : public IState
{
private:

	std::vector<VECTOR> ReturnpatrolPoints; //複数の監視ポイント
	VECTOR goal;	                        //目的地
	int nearestIdx;                         //一番近いポイントを探す
	float nearestDist;                      //一番近い距離の保存

public:
	GSReturn() = default;
	~GSReturn() = default;

	void OnEnter(Object* parent);
	void OnExit(Object* parent);
	int Update(Object* parent);
};

//ダメージを受ける
class GSDamege : public IState
{
public:
	GSDamege() = default;
	~GSDamege() = default;

	void OnEnter(Object* parent) override;
	void OnExit(Object* parent) override;
	int Update(Object* parent) override;
};

//死亡状態
class GSDeath : public IState
{
public:
	GSDeath() = default;
	~GSDeath() = default;

	void OnEnter(Object* parent) override;
	void OnExit(Object* parent) override;
	int Update(Object* parent) override;

};