#include "DxLib.h"
#include "../Haeder/Wall.h"
#include "../Haeder/Pathfinding.h"

static void CalcTBN4(VERTEX3DSHADER* vertices, VECTOR faceNormal)
{
    VECTOR Tangent = VGet(0, 0, 0);
    VECTOR Binormal = VGet(0, 0, 0);

    if (faceNormal.z > 0.9f)
    {
        // 正面
        Tangent = VGet(1.0f, 0.0f, 0.0f);
        Binormal = VGet(0.0f, -1.0f, 0.0f);
    }

    else if (faceNormal.z < -0.9f)
    {
        // 裏面
        Tangent = VGet(-1.0f, 0.0f, 0.0f);
        Binormal = VGet(0.0f, -1.0f, 0.0f);
    }

    // N.x が支配的な場合 (右側面 or 左側面)
    else if (faceNormal.x > 0.9f)
    {
        // 右側面
        Tangent = VGet(0.0f, 0.0f, -1.0f);
        Binormal = VGet(0.0f, -1.0f, 0.0f);
    }

    else if (faceNormal.x < -0.9f)
    {
        // 左側面
        Tangent = VGet(0.0f, 0.0f, 1.0f);
        Binormal = VGet(0.0f, -1.0f, 0.0f);
    }

    // N.y が支配的な場合 (上面 or 下面)
    else if (faceNormal.y > 0.9f)
    {
        // 上面
        Tangent = VGet(1.0f, 0.0f, 0.0f);
        Binormal = VGet(0.0f, 0.0f, 1.0f);
    }

    else if (faceNormal.y < -0.9f)
    {
        // 下面
        Tangent = VGet(1.0f, 0.0f, 0.0f);
        Binormal = VGet(0.0f, 0.0f, -1.0f);
    }

    // 頂点に設定
    for (int i = 0; i < 4; i++)
    {
        vertices[i].norm = faceNormal;
        vertices[i].tan = Tangent;
        vertices[i].binorm = Binormal;
    }
}

static void SetVertex(VERTEX3DSHADER& vertex, float posX, float posY, float posZ, float u, float v)
{
    vertex.pos = VGet(posX, posY, posZ);
    vertex.u = u;
    vertex.v = v;
    vertex.dif = GetColorU8(255, 255, 255, 255);
    vertex.spc = GetColorU8(0, 0, 0, 0);
    vertex.su = u;
    vertex.sv = v;

}

Wall::Wall(const char* texFront, const char* texSide, VECTOR center, float halfX, float halfY, float halfZ,
    const char* NormalFront, const char* NormalSide)
: Object()
,hFront(-1)
,hSide(-1)
,drawFlag(0)
{
    m_wallShader = LoadPixelShader("WallPS.cso");

    SetPosRist(center);

    EditorPosition = center;

    hx = halfX;
    hy = halfY;
    hz = halfZ;

    // テクスチャ読み込み
    hFront = LoadGraph(texFront);
    hSide = LoadGraph(texSide);
    
    hNormalFront = LoadGraph(NormalFront);
    hNormalSide = LoadGraph(NormalSide);

    float x1 = center.x - hx;
    float x2 = center.x + hx;

    float y1 = center.y;
    float y2 = center.y + hy * 2.0f;

    float z1 = center.z - hz;
    float z2 = center.z + hz;

    // -------- 正面（-Z）--------
    SetVertex(vFront[0], x1, y2, z1, 0, 0);
    SetVertex(vFront[1], x2, y2, z1, 1, 0);
    SetVertex(vFront[2], x1, y1, z1, 0, 1);
    SetVertex(vFront[3], x2, y1, z1, 1, 1);
    CalcTBN4(vFront, VGet(0.0f, 0.0f, -1.0f));

    // -------- 裏面（-Z）--------
    SetVertex(vBack[0], x2, y2, z2, 0, 0);
    SetVertex(vBack[1], x1, y2, z2, 1, 0);
    SetVertex(vBack[2], x2, y1, z2, 0, 1);
    SetVertex(vBack[3], x1, y1, z2, 1, 1);
    CalcTBN4(vBack, VGet(0.0f, 0.0f, 1.0f));

    // -------- 左（+X）--------
    SetVertex(vLeft[0], x2, y2, z1, 0, 0);
    SetVertex(vLeft[1], x2, y2, z2, 1, 0);
    SetVertex(vLeft[2], x2, y1, z1, 0, 1);
    SetVertex(vLeft[3], x2, y1, z2, 1, 1);
    CalcTBN4(vLeft, VGet(1.0f, 0.0f, 0.0f));

    // -------- 右（-X）--------
    SetVertex(vRight[0], x1, y2, z2, 0, 0);
    SetVertex(vRight[1], x1, y2, z1, 1, 0);
    SetVertex(vRight[2], x1, y1, z2, 0, 1);
    SetVertex(vRight[3], x1, y1, z1, 1, 1);
    CalcTBN4(vRight, VGet(-1.0f, 0.0f, 0.0f));

    // -------- 上（-Y）--------
    SetVertex(vTop[0], x1, y1, z1, 0, 0);
    SetVertex(vTop[1], x2, y1, z1, 1, 0);
    SetVertex(vTop[2], x1, y1, z2, 0, 1);
    SetVertex(vTop[3], x2, y1, z2, 1, 1);
    CalcTBN4(vTop, VGet(0.0f, -1.0f, 0.0f));

    // -------- 下（+Y）--------
    SetVertex(vBottom[0], x1, y2, z2, 0, 0);
    SetVertex(vBottom[1], x2, y2, z2, 1, 0);
    SetVertex(vBottom[2], x1, y2, z1, 0, 1);
    SetVertex(vBottom[3], x2, y2, z1, 1, 1);
    CalcTBN4(vBottom, VGet(0.0f, 1.0f, 0.0f));

    boxMin = VGet(x1, y1, z1);
    boxMax = VGet(x2, y2, z2);

}

Wall::~Wall()
{
}


void Wall::Initaliza()
{

}

void Wall::Update()
{
    drawFlag = 0;
}

void Wall::Draw()
{
    //影の認識
    if (drawFlag == 0)
    {

        WORD idx[6] = { 0,1,2, 3,2,1 };
        int PolygonVertexNum = 4;
        int PolygonNum = 2; // 4頂点で2枚のトライアングル

        VERTEX3D vTemp[4] = {};

        // --- 正面・裏面 ---
        for (int i = 0; i < 4; i++)
        {
            vTemp[i].pos = vFront[i].pos;
            vTemp[i].norm = vFront[i].norm;
            vTemp[i].u = vFront[i].u;
            vTemp[i].v = vFront[i].v;
            vTemp[i].dif = vFront[i].dif;
        }
        DrawPolygonIndexed3D(vTemp, PolygonVertexNum, idx, PolygonNum,hFront,FALSE);

        for (int i = 0; i < 4; i++)
        {
            vTemp[i].pos = vBack[i].pos;
            vTemp[i].norm = vBack[i].norm;
            vTemp[i].u = vBack[i].u;
            vTemp[i].v = vBack[i].v;
            vTemp[i].dif = vBack[i].dif;
        }
        DrawPolygonIndexed3D(vTemp, PolygonVertexNum, idx, PolygonNum,hFront,FALSE);

        // --- 側面・上下面 ---
        for (int i = 0; i < 4; i++)
        {
            vTemp[i].pos = vLeft[i].pos;
            vTemp[i].norm = vLeft[i].norm;
            vTemp[i].u = vLeft[i].u;
            vTemp[i].v = vLeft[i].v;
            vTemp[i].dif = vLeft[i].dif;
        }
        DrawPolygonIndexed3D(vTemp, PolygonVertexNum, idx, PolygonNum,hSide,FALSE);

        for (int i = 0; i < 4; i++)
        {
            vTemp[i].pos = vRight[i].pos;
            vTemp[i].norm = vRight[i].norm;
            vTemp[i].u = vRight[i].u;
            vTemp[i].v = vRight[i].v;
            vTemp[i].dif = vRight[i].dif;
        }
        DrawPolygonIndexed3D(vTemp, PolygonVertexNum, idx, PolygonNum,hSide,FALSE);

        for (int i = 0; i < 4; i++)
        {
            vTemp[i].pos = vTop[i].pos;
            vTemp[i].norm = vTop[i].norm;
            vTemp[i].u = vTop[i].u;
            vTemp[i].v = vTop[i].v;
            vTemp[i].dif = vTop[i].dif;
        }
        DrawPolygonIndexed3D(vTemp, PolygonVertexNum, idx, PolygonNum,hSide,FALSE);

        for (int i = 0; i < 4; i++)
        {
            vTemp[i].pos = vBottom[i].pos;
            vTemp[i].norm = vBottom[i].norm;
            vTemp[i].u = vBottom[i].u;
            vTemp[i].v = vBottom[i].v;
            vTemp[i].dif = vBottom[i].dif;
        }

        DrawPolygonIndexed3D(vTemp, PolygonVertexNum, idx, PolygonNum,hSide,FALSE);
        
    }

    //シェーダーを使っての描画
    else
    {
        SetUsePixelShader(m_wallShader);

        WORD idx[6] = { 0,1,2, 3,2,1 };
        int PolygonVertexNum = 4;
        int PolygonNum = 2; // 4頂点で2枚のトライアングル

        // --- 正面・裏面 ---
        //カラーテクスチャ
        SetUseTextureToShader(0, hFront);
        SetUseTextureToShader(1, hNormalFront);

        DrawPolygonIndexed3DToShader(vFront, PolygonVertexNum, idx, PolygonNum);
        DrawPolygonIndexed3DToShader(vBack, PolygonVertexNum, idx, PolygonNum);

        // --- 側面・上下面 ---
        SetUseTextureToShader(0, hSide);
        SetUseTextureToShader(1, hNormalSide);

        DrawPolygonIndexed3DToShader(vLeft, PolygonVertexNum, idx, PolygonNum);
        DrawPolygonIndexed3DToShader(vRight, PolygonVertexNum, idx, PolygonNum);
        DrawPolygonIndexed3DToShader(vTop, PolygonVertexNum, idx, PolygonNum);
        DrawPolygonIndexed3DToShader(vBottom, PolygonVertexNum, idx, PolygonNum);

        SetUseLighting(TRUE);

        SetUsePixelShader(-1);
    }

    drawFlag++;

}

void Wall::Finaliza()
{
    DeleteGraph(hFront);
    DeleteGraph(hSide);
    DeleteGraph(hNormalFront);
    DeleteGraph(hNormalSide);

}

std::vector<VERTEX3DSHADER> Wall::GetTriangles() const
{
    std::vector<VERTEX3DSHADER> triangles;

    auto addFaceTriangles = [&](const VERTEX3DSHADER v[4])
        {
            triangles.push_back(v[0]);
            triangles.push_back(v[1]);
            triangles.push_back(v[2]);

            triangles.push_back(v[3]);
            triangles.push_back(v[2]);
            triangles.push_back(v[1]);
        };

    // 上下の面は追加しない
    addFaceTriangles(vFront);
    addFaceTriangles(vBack);
    addFaceTriangles(vLeft);
    addFaceTriangles(vRight);

    return triangles;

}

WallBox Wall::GetAABB_XZ() const
{
    WallBox box;

    box.minX = boxMin.x;
    box.maxX = boxMax.x;
    box.minZ = boxMin.z;
    box.maxZ = boxMax.z;

    return box;
}

