#pragma once
#include "Object.h"
#include "../Haeder/FSM.h"
#include "../Haeder/BoxModel.h"
#include "../Haeder/Player_UI.h"
#include <vector>

class ItemManeger;
class EquippedItems;
class Player_gause;

//アニメーションID
enum Animetion
{
    Neutral = 0,
    Attack = 1,
    MagicAttack = 2,
    Walk = 3,
    Run = 4,
    Stalsed = 5,
    PickItem = 6,
    Dame = 7,
    Die = 8,

    Length,
};

struct CollisionInfo
{
    VECTOR normal;
    float overlap;
    bool isHit = false;
};

class Player : public Object
{
private:

    ItemManeger* m_inventory;
    EquippedItems* m_equipped;

    int mnModelHandle;   //読み込んだモデルのハンドル
    int mnWeponHandle;   //武器のモデルハンドル
    int AnimHandle[9];   //アニメーション

    bool AnimetionFlag;  //アニメーション再生中か

    ///////////////
    Animetion mState;          //現在のアニメーション状態
    int mnAnimetion1;          //現在アニメーションしている番号
    int mnAnimetion2;          //１つ目のアニメーション番号
    float mfAnimCount1;        //現在アニメーションの再生カウンタ
    float mfAnimCount2;        //１つ前のアニメーション再生カウンタ
    float mfAnimBlendRate;     //アニメーションのブレンド率(0.0f～1.0f)

    const float CHARA_ANIME_BLEND_SPEED = 0.1f;
    const float CHARA_PLAY_BLEND_SPEED = 0.5f;
    ///////////////

    // プレイヤーの現在のY軸回転角度（ラジアン）を保持
    float mfAngle; 

    // 目標とする移動方向を保持するための変数
    VECTOR mvTargetMoveDirection;

    //敵に当たったら
    bool HitEnemy;


public:
    Player();   //コンストラクタ
    ~Player();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

    //次の移動先
    VECTOR moveVec;
    VECTOR nextPos;

    // プレイヤー情報を取得
    VECTOR pos;                 // 現在位置
    VECTOR dir;                 // SetDirで設定された移動方向（正規化済み）
    float  speed;               // SetSpeedで設定された移動速度

    //移動前の座標
    VECTOR mvPlayerold;

    //攻撃範囲
    VECTOR attackOffset;
    VECTOR attackPos;
    float attackR;

    // プレイヤーのカプセル情報
    VECTOR playerBottom;
    VECTOR playerTop;
    float  playerR;

    //当たり判定
    bool HitPillar;
    bool AttackPillar;
    bool HitSpider;
    bool AttackSpider;
    bool HitGoal;

    //無敵時間
    int Invincible;

    //敵に当たったフラグの設定
    void SetHitEnemy(bool flag) { HitEnemy = flag; }

    //敵に当たったフラグの取得
    bool GetHitEnemy() const { return HitEnemy; }

    //アイテム選択
    bool SelectItem;

    //----アニメーション関連----
    bool IsAnimating() const { return AnimetionFlag; }
    //アニメーション切り替え処理
    void ChangeAnimaiton(Animetion index);  
    //アニメーション処理
    void PlayAnimetion();                       
    //アニメーションの取得
    Animetion GetAnimationState() const { return mState; }

    //武器
    void SetModelFramePosition(const char* FrameName, int SetModelHandle);

    ItemManeger* GetInventory() { return m_inventory; }
    EquippedItems* GetEquippedItems() { return m_equipped; }
};