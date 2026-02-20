#pragma once
#include "FSM.h"
#include "DxLib.h"
#include <string>
#include <vector>

//FSM‚Ì¶¬‚ğˆÏ÷‚·‚é
class FSMFactory
{
public:
	static FSM* Create(std::string name, Object* obj);
};
