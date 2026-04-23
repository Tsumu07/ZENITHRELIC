#pragma once
#include "Object.h"

class Camera;

class MagicBoard : Object
{
public:
    MagicBoard(const char *filename);
    ~MagicBoard();

    void Initaliza() override;
    void Update()    override;
    void Draw()      override;
    void Finaliza()  override;

    ////’Ç]‘ÎÛ‚Ìİ’è
    void Settarget(Camera *camera)
    {
        mpCamera = camera;
    }

private:
    //‰æ‘œ“Ç‚İ‚İ(‰“‹——£•Ší)
    int mnMagicBoard;
    //’Ç]‘ÎÛ
    Camera *mpCamera;
};