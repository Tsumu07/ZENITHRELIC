#include "../Haeder/FSMFactory.h"
#include "../Haeder/Player_state.h"
#include "../Haeder/Spider_State.h"
#include "../Haeder/GameManager.h"

using namespace std;

FSM* FSMFactory::Create(std::string name, Object* obj)
{
	FSM* fsm = nullptr;

	if (name == "Player")
	{
		fsm = new FSM();

		fsm->RegisterState(PLAYER_STATE_IDLE, new PSIdle());
		fsm->RegisterState(PLAYER_STATE_WALK, new PSWalk());
		fsm->RegisterState(PLAYER_STATE_ATTACK, new PSAttack());
		fsm->RegisterState(PLAYER_STATE_PICKITEM, new PSPicitem());
		fsm->RegisterState(PLAYER_STATE_DAMAGE, new PSDamege());
		fsm->RegisterState(PLAYER_STATE_DEATH, new PSDeath());
		fsm->SetCurrentState(PLAYER_STATE_IDLE, obj);
	}

	else if (name == "Spider")
	{			
		fsm = new FSM();

		fsm->RegisterState(Spider_STATE_MOVE_PATROL, new GSMovePatrol());
		fsm->RegisterState(Spider_STATE_MOVE_POINT, new GSMovePoint());
		fsm->RegisterState(Spider_STATE_CHASE, new GSChase());
		fsm->RegisterState(Spider_STATE_ATTACK, new GSAttack());
		fsm->RegisterState(Spider_STATE_RETURN, new GSReturn());
		fsm->RegisterState(Spider_STATE_DAMAGE, new GSDamege());
		fsm->RegisterState(Spider_STATE_DEATH, new GSDeath());
		fsm->SetCurrentState(Spider_STATE_MOVE_PATROL, obj);
	}

	return fsm;
}
