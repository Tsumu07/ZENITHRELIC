#include "../Haeder/FSM.h"

FSM::FSM()
{
	stateMap.clear();
	currentState = 0;
}

FSM::~FSM()
{
	//mapに登録されている状態クラスのインスタンスをすべて開放する
	for (auto& pair : stateMap)
	{
		//状態クラスのインスタンスを開放する
		delete pair.second;
	}

	stateMap.clear();
}

void FSM::RegisterState(int id, IState* state)
{
	stateMap[id] = state;
}

void FSM::SetCurrentState(int id, Object* parent)
{
	//実行中の状態をセット
	currentState = id;

	//状態の初期化処理を呼ぶ
	stateMap[currentState]->OnEnter(parent);
}

void FSM::Update(Object* parent)
{
	int state = stateMap[currentState]->Update(parent);

	//現在実行中の状態とUpdateの戻り値が違った場合は状態を遷移させる
	if (currentState != state)
	{
		//現在実行中の状態を終了させる
		stateMap[currentState]->OnExit(parent);

		//実行中の状態を更新する
		currentState = state;

		//新しい状態を初期化する
		stateMap[currentState]->OnEnter(parent);

	}

}