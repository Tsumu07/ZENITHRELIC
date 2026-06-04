#include "../Header/ObujectManager.h"
#include "../Header/Object.h"
#include "../Header/GameManager.h"
#include "../Header/FSM.h"
#include "../Master.h"
#include <cassert>

//コンストラクタ
Object::Object()
: mpNextOdject(nullptr)
, mpPrevOdject(nullptr)
,mbIsDeleteFlag(false)
,mnTag(-1)
,m_fsm()
,m_pos(VGet(0.0f,0.0f,0.0f))
,m_dir(VGet(0.0f,0.0f,0.0f))
,m_rot(VGet(0.0f,0.0f,0.0f))
,m_attack(VGet(0.0f,0.0f,0.0f))
,m_radius(0.0f)
,m_speed(0.0)
,m_hp(0.0f)
,m_invincible(0.0f)
,m_layer(-1)
,m_team(-1)
,Editorps(false)
{
    //オブジェクトが生成された時点で、オブジェクト管理に追加しておく
    //thisは自分をさす
    Master::GetObjectManager()->Add(this);

}

//デストラクタ

Object::~Object()
{
    delete m_fsm;
    m_fsm = nullptr;
}

void Object::Update()
{
    if (m_fsm)
    {
        m_fsm->Update(this);
    }
}

void Object::SetFSM(FSM* fsm)
{
    assert(fsm);//デバッグ時のfsmのNULLチェック

    m_fsm = fsm;

}
