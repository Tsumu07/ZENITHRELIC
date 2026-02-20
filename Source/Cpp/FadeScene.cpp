#include "../Haeder/FadeScene.h"
#include "../Haeder/ResourceManeger.h"
#include "../Master.h"
#include "../Haeder/SceneManager.h"
#include "DxLib.h"

FadeScene::FadeScene()
:m_isFadeOut(false)
,m_fadeSpeed(0.01f)
,m_fadeValue(0.0f)
,m_isEnd(false)
,LoadShaderFade(-1)
,FadeSceneTexture(0)
,m_fadeMode(0)
{
}

FadeScene::FadeScene(bool fadeOut)
:m_isFadeOut(fadeOut)
,m_fadeSpeed(0.01f)
,m_fadeValue(0.0f)
,m_isEnd(false)
,LoadShaderFade(-1)
,FadeSceneTexture(0)
{
}

void FadeScene::Initaliza()
{   

    // フェード用シェーダー読み込み
    LoadShaderFade = LoadPixelShader("wipePS.cso");

    FadeSceneTexture = LoadGraph("トランジション/pipo-tr002.png");

    // 左上
    m_vertices[0].pos = VGet(0.0f, 0.0f, 0.0f);
    m_vertices[0].u = 0.0f;
    m_vertices[0].v = 0.0f;
    m_vertices[0].dif = GetColorU8(255, 255, 255, 255);
    m_vertices[0].rhw = 1.0f;


    // 右上
    m_vertices[1].pos = VGet(1920.0f, 0.0f, 0.0f);
    m_vertices[1].u = 1.0f;
    m_vertices[1].v = 0.0f;
    m_vertices[1].dif = GetColorU8(255, 255, 255, 255);
    m_vertices[1].rhw = 1.0f;

    // 左下
    m_vertices[2].pos = VGet(0.0f, 1080.0f, 0.0f);
    m_vertices[2].u = 0.0f;
    m_vertices[2].v = 1.0f;
    m_vertices[2].dif = GetColorU8(255, 255, 255, 255);
    m_vertices[2].rhw = 1.0f;

    // 右下
    m_vertices[3].pos = VGet(1920.0f, 1080.0f, 0.0f);
    m_vertices[3].u = 1.0f;
    m_vertices[3].v = 1.0f;
    m_vertices[3].dif = GetColorU8(255, 255, 255, 255);
    m_vertices[3].rhw = 1.0f;

    m_indices[0] = 0;
    m_indices[1] = 1;
    m_indices[2] = 2;
    m_indices[3] = 1;
    m_indices[4] = 3;
    m_indices[5] = 2;

    m_fadeValue = m_isFadeOut ? 0.0f : 1.0f;
    m_isEnd = false;
}

void FadeScene::Update()
{

    if (m_fadeMode == 0)
    {
        return;
    }

    //フェードイン
    if (m_fadeMode == 1)
    {
        m_fadeValue += m_fadeSpeed;

        if (m_fadeValue > 1.0f)
        {
            m_fadeValue = 1.0f;
            m_isEnd = true;
            m_fadeMode = 0;
        }
    }

    //フェードアウト
    else if (m_fadeMode == 2)
    {
        m_fadeValue -= m_fadeSpeed;

        if (m_fadeValue < 0.0f)
        {
            m_fadeValue = 0.0f;
            m_isEnd = true;
            m_fadeMode = 3;
        }
    }

}

void FadeScene::Draw()
{

    if (m_fadeMode == 0)
    {
        return;
    }

    //2D描画に完全固定
    SetDrawScreen(DX_SCREEN_BACK);

    SetUseZBufferFlag(FALSE);
    SetWriteZBufferFlag(FALSE);

    SetUseVertexShader(-1);
    SetUsePixelShader(LoadShaderFade);

    //フェードは必ず ALPHA ブレンド
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

    int fadeCB = Master::mpResourceManager->GetConstBuff("Dissolve");
    CB_DISSOLVE_PARAM* cb = (CB_DISSOLVE_PARAM*)GetBufferShaderConstantBuffer(fadeCB);
    cb->dissolveThreshold = m_fadeValue;
    cb->dissolveRange = 0.3f;
    UpdateShaderConstantBuffer(fadeCB);

    SetUseTextureToShader(0, FadeSceneTexture);

    DrawPolygonIndexed2DToShader(m_vertices, 4, m_indices, 2);

    SetUseTextureToShader(0, -1);
    SetUsePixelShader(-1);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    SetUseZBufferFlag(TRUE);
    SetWriteZBufferFlag(TRUE);
}

void FadeScene::Finaliza()
{
    if (LoadShaderFade != -1)
    {
        DeleteShader(LoadShaderFade);
        LoadShaderFade = -1;
    }

}

void FadeScene::SetFadeMode(int mode)
{
    m_fadeMode = mode;

    //フェードイン
    if (mode == 1)
    {
        m_fadeValue = 0.0f;
    }

    //フェードアウト
    else if (mode == 2)
    {
        m_fadeValue = 1.0f;
    }

}