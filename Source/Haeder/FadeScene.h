#pragma once
#include "../Haeder/SceneBase.h"
#include "DxLib.h"
#include <vector>

class FadeScene : public SceneBase
{
private:
    float m_fadeValue;      // 0～1
    float m_fadeSpeed;
    bool  m_isFadeOut;
    bool  m_isEnd;
    int m_fadeMode;

    int LoadShaderFade;

    int FadeSceneTexture;

    VERTEX2DSHADER m_vertices[4];

    WORD m_indices[6];

public:

    FadeScene();
    FadeScene(bool fadeOut);

    //初期化
    void Initaliza();

    //更新
    void Update();

    //描画
    void Draw();

    //終了
    void Finaliza();

    bool IsEnd() const { return m_isEnd; }

    bool IsFadeOut() const { return m_isFadeOut; }

    float GetFadeValue() const { return m_fadeValue; }

    //FadeMode
    //0:無し（待機中）
    //1:フェードイン中
    //2:フェードアウト中
    //3:フェードアウト終了
    void SetFadeMode(int mode);
    int GetFadeMode(void) { return m_fadeMode; }
    void SetFadeSpeed(float speed) { m_fadeSpeed = speed; }

};