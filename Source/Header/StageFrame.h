#pragma once
#include "Object.h"
#include "DxLib.h"
#include <vector>

class StageFrame : public Object
{
public:
    StageFrame(VECTOR position, VECTOR topLeft, VECTOR bottomRigh);
    ~StageFrame();

    void Initaliza() override;
    void Update() override;
    void Draw() override;
    void Finaliza() override;

    std::vector<VERTEX3D> GetVertex()
    {
        std::vector<VERTEX3D> result;
        result.push_back(mvertex[0]);
        result.push_back(mvertex[1]);
        result.push_back(mvertex[2]);
        result.push_back(mvertex[3]);
        return result;
    }


private:
    VERTEX3D mvertex[4];  //í∏ì_èÓïÒ

};
