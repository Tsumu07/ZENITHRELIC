#pragma once
#include "Object.h"

class AttackBoard : Object
{
public:
    AttackBoard(const char *filename);
    ~AttackBoard();

    void Initaliza() override;
    void Update()    override;
    void Draw()      override;
    void Finaliza()  override;


private:
    //‰æ‘œ“Ç‚İ‚İ(‹ß‹——£•Ší)
    int mnAttackBoard;
};