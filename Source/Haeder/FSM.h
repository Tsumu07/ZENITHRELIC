#pragma once
#include <map>
#include "../Haeder/IState.h"

class FSM
{
private:
	//  map<enum STATE 状態クラスのインスタンス>
	//  登録した状態のリスト
	std::map<int, IState*> stateMap;

	//現在実行中の状態
	int currentState;

public:
	FSM();
	virtual ~FSM();

	//状態をmapに登録
	void RegisterState(int id, IState* state);

	//実行中状態をセット
	void SetCurrentState(int id, Object* parent);

	void Update(Object* parent);
};