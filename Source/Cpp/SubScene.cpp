#include "../Haeder/SubScene.h"

SubScene::SubScene()
:m_timer(0)
,m_isEnd(false)
{
}

SubScene::~SubScene()
{
}

void SubScene::Initaliza()
{
    m_timer = 180;
    m_isEnd = false;
}

void SubScene::Update()
{
    m_timer--;

    if (m_timer <= 0)
    {
        m_isEnd = true;
    }
}

void SubScene::Draw()
{
}

void SubScene::Finaliza()
{
}

bool SubScene::IsEnd() const
{
    return m_isEnd;
}