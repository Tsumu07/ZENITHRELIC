#pragma once
#include "DxLib.h"

class SubScene
{
protected:
    int m_timer;
    bool m_isEnd;

public:
    SubScene();
    virtual ~SubScene();

    virtual void Initaliza();
    virtual void Update();
    virtual void Draw();
    virtual void Finaliza();

    bool IsEnd() const;

};