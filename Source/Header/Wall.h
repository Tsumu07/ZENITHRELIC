#pragma once
#include "Object.h"
#include "DxLib.h"
#include <vector>

struct WallBox;   // 前方宣言

class Wall : public Object
{
private:
    int hFront;
    int hSide;

    //ノーマルマップ
    int hNormalFront;
    int hNormalSide;

    //シェーダー
    int m_wallShader;

    float hx, hy, hz;  // 半サイズ（X, Y, Z）

    VERTEX3DSHADER vFront[4];
    VERTEX3DSHADER vBack[4];
    VERTEX3DSHADER vLeft[4];
    VERTEX3DSHADER vRight[4];
    VERTEX3DSHADER vTop[4];
    VERTEX3DSHADER vBottom[4];

    VECTOR boxMin;
    VECTOR boxMax;

    VECTOR EditorPosition;

    int drawFlag;

public:
    Wall(const char* texFront, const char* texSide, VECTOR center, float halfX, float halfY, float halfZ,
        const char* NormalFront,const char* NormalSide);
    ~Wall();

    void Initaliza() override;
    void Update() override;
    void Draw() override;
    void Finaliza() override;

    // エディタ用の位置を返す（保存処理などで使う）
    VECTOR GetEditorPosition() const { return EditorPosition; }

    //当たり判定
    std::vector<VERTEX3DSHADER> GetTriangles() const;

    WallBox GetAABB_XZ() const;


};

