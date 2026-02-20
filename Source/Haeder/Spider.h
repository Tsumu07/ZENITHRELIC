#pragma once
#include "../Haeder/Object.h"

//アニメーション
enum SpiderAnimetion
{
    SpiderDie = 0,
    SpiderDamegi = 1,
    SpiderAttack = 3,
    SpiderWalk = 4,
    SpiderIidel = 5,

    SpiderLength,
};

struct CollisionInfoSpider
{
    VECTOR normal;
    float overlap;
    bool isHit = false;
};

class Spider :public Object
{
private:

    //クモのモデル読み込み
    int mnSpiderModel;

    //向き
    float mfAngle;

    // 目標とする移動方向を保持するための変数
    VECTOR mvTargetMoveDirection;

    //クモの移動前の座標
    VECTOR mvPositionSter;

    //移動するべき方向ベクトル
    VECTOR mvTargetMoveSpider;

    //攻撃フラグ
    bool AttackSpider;

    //アニメーション
    int SpiderAnimHandle[6];

    bool AnimetionFlag;  //アニメーション再生中か

    SpiderAnimetion mStateSpider;          //現在のアニメーション状態
    int mnAnimetion1;                      //現在アニメーションしている番号
    int mnAnimetion2;                      //１つ目のアニメーション番号
    float mfAnimCount1;                    //現在アニメーションの再生カウンタ
    float mfAnimCount2;                    //１つ前のアニメーション再生カウンタ
    float mfAnimBlendRate;                 //アニメーションのブレンド率(0.0f～1.0f)

    const float CHARA_ANIME_BLEND_SPEED = 0.1f;
    const float CHARA_PLAY_BLEND_SPEED = 0.5f;

    //消えるカウントダウン
    float DeleteSpiderCount;

    //クモの断末魔
    int SpiderVoise;

    //プレイヤーに当たったら
    bool HitPlayer;

    //死亡フラグ
    bool m_isDeadStarted;

public:
    Spider();   //コンストラクタ
    ~Spider();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

    VECTOR moveVecGO = VGet(0.0f, 0.0f, 0.0f);

    int mnSpider() { return mnSpiderModel; }  //モデルの取得

    //----アニメーション関連----
    bool IsAnimation() const { return AnimetionFlag; }
    void ChangeAnimaitonSpider(SpiderAnimetion Spiderindex);      //アニメーション切り替え処理
    void SpAnimetion();                                           //アニメーション処理
    SpiderAnimetion GetAnimationState() const { return mStateSpider; }

    static int Count;

    //次の移動先
    VECTOR moveVec;
    VECTOR nextPos;

    // プレイヤー情報を取得
    VECTOR pos;                 // 現在位置
    VECTOR dir;                 // SetDirで設定された移動方向（正規化済み）
    float  speed;               // SetSpeedで設定された移動速度

    //攻撃範囲
    VECTOR attackOffset;
    VECTOR attackPos;
    float attackR;

    //カプセル情報
    VECTOR SpiderBottom;
    VECTOR SpiderTop;
    float  SpiderR;

    //当たり判定
    bool AttackPlayer;

    //無敵時間
    float Invincible;

    //敵に当たったフラグの設定
    void SetHitPlayer(bool flag) { HitPlayer = flag; }

    //敵に当たったフラグの取得
    bool GetHitPlayer() const { return HitPlayer; }

};