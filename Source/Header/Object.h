#pragma once
#include "DxLib.h"
#include <string>
#include <vector>

//オブジェクト
typedef struct
{
    char name[16];

    float PosiX;

    float PosiY;

    float PosiZ;

}Person;

//ドア
typedef struct
{
    char name[20];

    int PosiX;

    int PosiY;

    int PosiZ;

    float RotationY;

}GoalPerson;

//壁
typedef struct
{
    float x;
    float y;
    float z;

    // 壁の大きさ
    float sizeX;
    float sizeY;
    float sizeZ;

    // 壁の向き
    int orientation; // 0 = 左右, 1 = 上下 など
}WallPerson;

class FSM;

class Object
{
protected:
    Object *mpPrevOdject;   //前オブジェクトのポインタ
    Object *mpNextOdject;   //次オブジェクトのポインタ

    bool mbIsDeleteFlag;    //削除フラグ

    int mnTag;              //識別タグ

    FSM* m_fsm;//有限状態マシン

    //ポジション
    VECTOR m_pos;

    //複数あるオブジェクトのポジション
    std::vector<VECTOR> m_points;

    //向き
    VECTOR m_dir;

    VECTOR m_rot;

    //攻撃範囲のポジション
    VECTOR m_attack;

    //半径
    float m_radius;

    //スピード
    float m_speed;

    //体力
    float m_hp;

    //無敵時間
    float m_invincible;

    unsigned int m_layer;

    int m_team;

    bool Editorps;

public:
    Object();     //コンストラクタ
    ~Object();    //デストラクタ

    virtual void Initaliza() = 0;   //初期化
    virtual void Update() = 0;      //更新
    virtual void Draw() = 0;        //描画
    virtual void Finaliza() = 0;    //終了処理

    //前のオブジェクト情報を取得
    Object* GetPrevObject() { return mpPrevOdject; }

    //次のオブジェクト情報を取得
    Object* GetNextObject() { return mpNextOdject; }

    //前のオブジェクト
    void SetPrevObject(Object* object) { mpPrevOdject = object; }

    //次のオブジェクト
    void SetNextObject(Object* object) { mpNextOdject = object; }

    //削除フラグ設定
    void SetDeleteFlag(bool flag) { mbIsDeleteFlag = flag; }

    //削除フラグ取得
    bool IsDeleteFlag() { return mbIsDeleteFlag; }

    //タグの設定
    void SetTag(int tag) { mnTag = tag; }

    //タグの取得
    int GetTag(void) { return mnTag; }

    // ポジションの設定
    void SetPos(const VECTOR& position) { m_pos = position; }

    //複数のポジションの設定
    void SetPosRist(const VECTOR& position) { m_points.push_back(position); }

    //向きの設定
    void SetDir(const VECTOR& direction) { m_dir = direction; }

    //スピードの設定
    void SetSpeed(const float spd) { m_speed = spd; }

    void SetRot(const VECTOR& rotation) { m_rot = rotation; }

    //半径の設定
    void SetRadius(const float rad) { m_radius = rad; }

    //体力の設定
    void SetHp(const float hp) { m_hp = hp; }

    //無敵時間を設定
    void SetInvincible(const float invincible) { m_invincible = invincible; }

    //攻撃範囲の設定
    void SetAttack(const VECTOR& attack) { m_attack = attack; }

    //エディター用のシェーダーの設定
    void SetEditorps(bool Editorflag) { Editorps = Editorflag; }

    //ポジションの取得
    VECTOR GetPos(void) const { return m_pos; }

    //複数のポジションの取得
    const std::vector<VECTOR>& GetPositions(void) const { return m_points; }

    //向きの取得
    VECTOR GetDir(void) const { return m_dir; }

    VECTOR GetRot(void) const { return m_rot; }

    //スピードの取得
    float GetSpeed(void) const { return m_speed; }

    //半径の取得
    float GetRadius(void) const { return m_radius; }

    //体力の取得
    float GetHp(void) const { return m_hp; }

    //無敵時間の取得
    float GetInvincible(void) const { return m_invincible; }

    //攻撃範囲の取得
    VECTOR GetAttack(void) const { return m_attack; }

    //レイヤー番号の設定
    void SetLayer(const unsigned int layer) { m_layer = layer; }

    //レイヤー番号の取得
    unsigned int GetLayer(void) const { return m_layer; }

    //エディター用のシェーダーの取得
    bool GetEditorps(void) const { return Editorps; }

    //回復させる
    void AddHp(int recoveryamount) { m_hp += recoveryamount; }

    //ダメージ与える
    void Damage(int damage) { m_hp -= damage; }

    //死亡したか
    bool IsDead() { return m_hp <= 0; }

    //外部で作ったFSMのインスタンスをセットする
    void SetFSM(FSM* fsm);

    void SetTeam(int t) { m_team = t; }

    int GetTeam(void) const { return m_team; }

    virtual bool IsCylinder() const { return false; }

};