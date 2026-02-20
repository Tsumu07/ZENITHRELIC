#pragma once

class SceneBase
{
public:
    SceneBase();//コンストラクタ
    ~SceneBase();//デストラクタ

    virtual void Initaliza(); //初期化
    virtual void Update();//更新
    virtual void Draw();//描画
    virtual void Finaliza();//終了処理
};