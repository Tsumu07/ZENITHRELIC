#include "../Haeder/Spider.h"
#include "../Haeder/Spider_state.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Pathfinding.h"
#include "../Haeder/Wall.h"
#include "../Master.h"
#include "DxLib.h"
#include <cmath>

Object* GetPlayerObject(Object* parent);
bool IsPlayerInSinght(Object* parent, float range, float angle);
std::vector<VECTOR> GetPatrolPointsFromTag(int tag);
static std::vector<ObstacleData> GetObstaclesFromTags(const std::vector<int>& tags);
std::vector<WallBox>GetWallBoxesFromTags(const std::vector<int>& tags);

struct  ReturnInfo
{
    VECTOR pos;
};

ReturnInfo g_ri;

//-------------------------------
//-------------------------------
//-----------行先の指定----------
void GSMovePatrol::OnEnter(Object* parent)
{
    Spider* spider = dynamic_cast<Spider*>(parent);
    if (spider)
    {
        //アニメーションをwalkに変更
        spider->ChangeAnimaitonSpider(SpiderAnimetion::SpiderIidel);
    }

    PointsRist = GetPatrolPointsFromTag(400);  //ポイントのポジションリスト
    stayTimes.assign(PointsRist.size(), 0.0f);      //滞在時間を0で初期化
    targetIndex = -1;                               //目的地
    randomIndex = -1;                               //ランダムの目的地
    stayThreshold = 1.0f;                           //プレイヤーがいたとみなす時間
    waitTimer = 0.0f;                               //待機タイマー
    waitThreshld = 20.0f;                           //ランダム移動までの待機

}

void GSMovePatrol::OnExit(Object* parent)
{
    waitTimer = 0.0f;
}

int GSMovePatrol::Update(Object* parent)
{
    //プレイヤーのGameObjetを取得
    Object* player = GetPlayerObject(parent);
    float deltaTime = 1.0f / 60.0f;

    //視界にプレイヤーが入ったら
    if (IsPlayerInSinght(parent, 550.0f, 0.907f))
    {
        //追跡状態へ移行する
        return Spider_STATE_CHASE;
    }

    //ゴーレムの行動目標がまだ決まっていない場合
    if (targetIndex == -1)
    {

        //各ポイントごとに判定
        for (int i = 0; i < PointsRist.size(); i++)
        {

            float distance = VSize(VSub(player->GetPos(), PointsRist[i]));

            //範囲内にプレイヤーがいたら滞在時間を加算
            if (distance < 200.0f)
            {
                stayTimes[i] += deltaTime;
            }

            //範囲外にプレイヤーがでたらリセット
            else
            {
                stayTimes[i] = 0.0f;
            }

            //時間を超えたらそのポイントを目標に設定
            if (stayTimes[i] >= stayThreshold)
            {
                targetIndex = i;
                stayTimes[i] = 0.0f;

                break;
            }

        }

    }

    // --- 優先ターゲットがある場合はそちらへ移動 ---
    else
    {
        goal = PointsRist[targetIndex];
        g_ri.pos = goal;

        //ポイントに向かう
        return Spider_STATE_MOVE_POINT;
    }

    // --- 優先ターゲットがないときはランダム巡回 ---
    if (randomIndex == -1)
    {
        waitTimer += 1.0f;

        if (waitTimer >= waitThreshld)
        {
            waitTimer = 0.0f;

            if (!PointsRist.empty())
            {
                randomIndex = GetRand(PointsRist.size() - 1);
            }
        }
    }

    else
    {
        //目的地までの距離を測る
        float distance = VSize(VSub(parent->GetPos(), PointsRist[randomIndex]));

        if (distance < 60.0f)
        {
            //到着 → 少し待って別の場所へ
            randomIndex = -1;
            waitTimer = 0.0f;
        }

        else
        {
            //ランダム巡回中にプレイヤーが監視ポイントに近づいたら
            // targetIndex が設定されて次のフレームで切り替わる
            goal = PointsRist[randomIndex];
            g_ri.pos = goal;
            return Spider_STATE_MOVE_POINT;
        }

    }

    return Spider_STATE_MOVE_PATROL;;
}

//-------------------------------
//-------------------------------
//-----------移動状態------------
void GSMovePoint::OnEnter(Object* parent)
{
    Spider* spider = dynamic_cast<Spider*>(parent);
    if (spider)
    {
        //アニメーションをwalkに変更
        spider->ChangeAnimaitonSpider(SpiderAnimetion::SpiderWalk);
    }

    patrolPoints = GetPatrolPointsFromTag(400);
    stayTimes.assign(patrolPoints.size(), 0.0f);
    stayThreshold = 1.0f;

    //ゴールをセット
    goal = g_ri.pos;
    m_path.clear();
    m_pathIndex = 0;
    m_repathTimer = 0.0f;

    //経路探索パラメータ設定
    step = 50.0f;
    agentRadius = 100.0f;
    repathInterval = 3.0f;
    arriveDist = 60.0f;
}

void GSMovePoint::OnExit(Object* parent)
{

    m_path.clear();
    m_pathIndex = 0;
    m_repathTimer = 0.0f;

}

int GSMovePoint::Update(Object* parent)
{

    parent->SetSpeed(3.0f);

    //ダメージを受ける
    Spider* spider = dynamic_cast<Spider*>(parent);

    if (spider->GetHitPlayer())
    {
        return Spider_STATE_DAMAGE;
    }

    // 優先度が高い判定（視界チェック）
    if (IsPlayerInSinght(parent, 550.0f, 0.907f))
    {
        return Spider_STATE_CHASE;
    }

    // --- 監視ポイント反応チェック ---
    {
        float deltaTime = 1.0f / 60.0f;

        for (int i = 0; i < patrolPoints.size(); i++)
        {
            Object* player = GetPlayerObject(parent);

            float distance = VSize(VSub(player->GetPos(), patrolPoints[i]));

            if (distance < 200.0f)
            {
                stayTimes[i] += deltaTime;
            }

            else
            {
                stayTimes[i] = 0.0f;
            }

            if (stayTimes[i] >= stayThreshold)
            {
                g_ri.pos = patrolPoints[i];  // 目的地をセット
                goal = g_ri.pos;
                stayTimes[i] = 0.0f;
            }
        }
    }

    VECTOR SpiderPos = parent->GetPos();

    // 経路を一定間隔で再探索
    m_repathTimer += 1.0f;

    if (m_repathTimer >= repathInterval || m_path.empty())
    {
        m_repathTimer = 0.0f;

        //タグから障害物ポイントを取得
        std::vector<ObstacleData> obstacles = GetObstaclesFromTags({ 700 });

        // タグから壁を取得(Wall オブジェクトのタグで指定
        std::vector<WallBox> walls = GetWallBoxesFromTags({ 1500, 2500 });

        // 新しい経路を格納するためのバッファ
        std::vector<VECTOR> newPath;

        // 現在位置 → 目標位置 まで、障害物を避けた最短経路を探索する
        bool found = AStarDynamic::FindPath(
            SpiderPos,
            goal,
            obstacles,
            walls,
            newPath,
            step,
            agentRadius,
            400
        );

        // 経路が見つかり、かつ2点以上ある場合
        if (found && newPath.size() > 1)
        {
            // 新しい経路を現在の経路として採用
            m_path = std::move(newPath);
            m_pathIndex = 1;
        }
    }

    // 経路追従処理
    // 経路上の次のポイントへ移動する
    if (m_pathIndex < m_path.size())
    {
        // 次の目的地点
        VECTOR target = m_path[m_pathIndex];

        //Yは0.0fに統一
        target.y = SpiderPos.y;

        VECTOR vDist = VSub(target, SpiderPos);

        // 現在位置から次の経路点までの距離
        float dist = VSize(vDist);

        if (dist < arriveDist)
        {
            // 近づいたら次の経路点へ進む
            m_pathIndex++;
        }

        else
        {
            // 目的地点の方向を向かせて前進させる
            VECTOR dir = VNorm(vDist);
            parent->SetDir(dir);
        }
    }

    else
    {
        // 経路が終わった場合は、ゴールに直接向かう
        VECTOR dir = VNorm(VSub(goal, SpiderPos));
        parent->SetDir(dir);
    }

    // 到着判定
    float distanceToGoal = VSize(VSub(goal, SpiderPos));

    if (distanceToGoal <= 30.0f)
    {
        // ゴールに到着したら停止して巡回モードに戻る
        parent->SetSpeed(0.0f);
        return Spider_STATE_MOVE_PATROL;
    }

    //ゲームオーバー
    if (parent->IsDead())
    {
        return Spider_STATE_DEATH;
    }

    //継続
    return Spider_STATE_MOVE_POINT;
}

//------------------------------
//------------------------------
//-----------追跡状態-----------
void GSChase::OnEnter(Object* parent)
{

    m_path.clear();
    m_pathIndex = 0;
    m_repathTimer = 0.0f;

    //経路探索パラメータ設定
    step = 100.0f;
    agentRadius = 70.0f;
    repathInterval = 1.0f;
    arriveDist = 100.0f;

    //攻撃範囲
    attack = 300.0f;

    //見失う距離
    playerlose = 850.0f;

}

void GSChase::OnExit(Object* parent)
{
    m_path.clear();
    m_pathIndex = 0;
    m_repathTimer = 0.0f;
}

int GSChase::Update(Object* parent)
{
    parent->SetSpeed(3.0f);

    //ゴーレムのポジション
    VECTOR SpiderPos = parent->GetPos();

    //プレイヤーのObjectを取得
    Object* player = GetPlayerObject(parent);

    //プレイヤーのポジション
    VECTOR playerPos = player->GetPos();

    //ダメージを受ける
    Spider* spider = dynamic_cast<Spider*>(parent);

    if (spider->GetHitPlayer())
    {
        return Spider_STATE_DAMAGE;
    }

    //ゲームオーバー
    if (parent->IsDead())
    {
        return Spider_STATE_DEATH;
    }


    //経路を一定間隔で再検索
    m_repathTimer += 1.0f;

    if (m_repathTimer >= repathInterval || m_path.empty())
    {
        m_repathTimer = 0.0f;

        //タグから障害物ポイントを取得
        std::vector<ObstacleData> obstacles = GetObstaclesFromTags({ 700 });

        // タグから壁を取得(Wall オブジェクトのタグで指定
        std::vector<WallBox> walls = GetWallBoxesFromTags({ 1500, 2500 });

        //新しい経路を格納するためのバッファ
        std::vector<VECTOR> newPath;

        // 現在位置 → 目標位置 まで、障害物を避けた最短経路を探索する
        bool found = AStarDynamic::FindPath(
            SpiderPos,
            playerPos,
            obstacles,
            walls,
            newPath,
            step,
            agentRadius,
            400
        );

        //経路が見つかり、かつ2点以上ある場合
        if (found && newPath.size() > 1)
        {
            //新しい経路を現在の経路として採用
            m_path = std::move(newPath);
            m_pathIndex = 1;
        }
    }

    // 経路追従処理
    // 経路上の次のポイントへ移動する
    if (m_pathIndex < m_path.size())
    {
        //次の目的地
        VECTOR target = m_path[m_pathIndex];

        //Yは0.0fに統一
        target.y = SpiderPos.y;

        VECTOR vDist = VSub(target, SpiderPos);

        //現在位置から次の経路点までの距離
        float dist = VSize(vDist);

        if (dist < arriveDist)
        {
            //近づいたら次の経路点へ進む
            m_pathIndex++;
        }

        else
        {
            //目的地の方向を向かせて前進させる
            VECTOR dir = VNorm(vDist);
            parent->SetDir(dir);
        }

    }

    else
    {
        //経路が終わった場合は、ゴールに直接向かう
        VECTOR dir = VNorm(VSub(playerPos, SpiderPos));
        parent->SetDir(dir);
    }

    VECTOR vDist = VSub(playerPos, SpiderPos);

    float distanceToGoal = VSize(vDist);

    //攻撃範囲
    if (distanceToGoal <= attack)
    {
        return Spider_STATE_ATTACK;
    }

    //見失う
    if (distanceToGoal > playerlose)
    {
        return Spider_STATE_RETURN;
    }


    //継続
    return Spider_STATE_CHASE;
}


//------------------------------
//------------------------------
//-----------攻撃状態-----------
void GSAttack::OnEnter(Object* parent)
{
    parent->SetSpeed(0.0f);

    //敵にキャストしてアニメーションを切り替え
    Spider* spider = dynamic_cast<Spider*>(parent);
    if (spider)
    {
        spider->ChangeAnimaitonSpider(SpiderAnimetion::SpiderAttack);
    }
}

void GSAttack::OnExit(Object* parent)
{
}

int GSAttack::Update(Object* parent)
{
    //敵にダイナミックキャスト
    Spider* spider = dynamic_cast<Spider*>(parent);

    // アニメーションが終了したかどうかを AnimetionFlag で判定する
    if (spider && !spider->IsAnimation())
    {
        //アニメーションが終了したら、歩き
        return Spider_STATE_CHASE;
    }

    //ゲームオーバー
    if (parent->IsDead())
    {
        return Spider_STATE_DEATH;
    }

    if (spider->GetHitPlayer())
    {
        return Spider_STATE_DAMAGE;
    }


    return Spider_STATE_ATTACK;
}

//------------------------------
//------------------------------
//----------帰還状態------------
void GSReturn::OnEnter(Object* parent)
{
    Spider* spider = dynamic_cast<Spider*>(parent);
    if (spider)
    {
        //アニメーションをwalkに変更
        spider->ChangeAnimaitonSpider(SpiderAnimetion::SpiderWalk);
    }


    ReturnpatrolPoints = GetPatrolPointsFromTag(400);
    nearestIdx = -1;
    nearestDist = FLT_MAX;


    //各ポイントごとに判定
    for (int i = 0; i < ReturnpatrolPoints.size(); i++)
    {
        float distance = VSize(VSub(ReturnpatrolPoints[i], parent->GetPos()));

        if (distance < nearestDist)
        {
            nearestDist = distance;
            nearestIdx = i;
        }
    }

}

void GSReturn::OnExit(Object* parent)
{
}

int GSReturn::Update(Object* parent)
{
    // 優先度が高い判定（視界チェック）
    if (IsPlayerInSinght(parent, 550.0f, 0.907f))
    {
        return Spider_STATE_CHASE;
    }

    //ゴールをセット
    if (nearestIdx != -1)
    {
        goal = ReturnpatrolPoints[nearestIdx];
        g_ri.pos = goal;

        return Spider_STATE_MOVE_POINT;
    }

    //ゲームオーバー
    if (parent->IsDead())
    {
        return Spider_STATE_DEATH;
    }

    Spider* spider = dynamic_cast<Spider*>(parent);

    if (spider->GetHitPlayer())
    {
        return Spider_STATE_DAMAGE;
    }

    return Spider_STATE_RETURN;//状態変化なし
}

//-------------------------------
//-------------------------------
//---------ダメージ状態----------
void GSDamege::OnEnter(Object* parent)
{
    parent->SetSpeed(0.0f);

    //敵にキャストしてアニメーションを切り替え
    Spider* spider = dynamic_cast<Spider*>(parent);
    if (spider)
    {
        spider->ChangeAnimaitonSpider(SpiderAnimetion::SpiderDamegi);
    }
}

void GSDamege::OnExit(Object* parent)
{

}

int GSDamege::Update(Object* parent)
{
    //ダメージを受ける
    Spider* spider = dynamic_cast<Spider*>(parent);

    if (spider && !spider->IsAnimation())
    {
        spider->SetHitPlayer(false);

        // アニメーションが終了したら、待機状態へ遷移
        return Spider_STATE_MOVE_PATROL;

    }

    //ゲームオーバー
    if (parent->IsDead())
    {
        return Spider_STATE_DEATH;
    }


    return Spider_STATE_DAMAGE;
}

//-------------------------------
//-------------------------------
//-----------死亡状態------------
void GSDeath::OnEnter(Object* parent)
{
    parent->SetSpeed(0.0f);

    //敵にキャストしてアニメーションを切り替え
    Spider* spider = dynamic_cast<Spider*>(parent);

    if (spider)
    {
        spider->ChangeAnimaitonSpider(SpiderAnimetion::SpiderDie);
    }
}

void GSDeath::OnExit(Object* parent)
{

}

int GSDeath::Update(Object* parent)
{
    return Spider_STATE_DEATH;
}


//タグからプレイヤーを取得
Object* GetPlayerObject(Object* parent)
{

    Object* playerobj = Master::mpObjectManager->FindByTag(100);

    if (playerobj != nullptr)
    {
        return playerobj;
    }

    return nullptr;
}

//プレイヤーが指定した視界にいるかどうかチェック
bool IsPlayerInSinght(Object* parent, float range, float angle)
{
    //プレイヤーとの差分ベクトルを作成
    Object* player = GetPlayerObject(parent);

    //プレイヤーとの差分
    VECTOR vDist = VSub(player->GetPos(), parent->GetPos());

    //ゴールに到達した→自分の位置とゴールの位置の差分ベクトルの大きさを調べる
    //一定以下ならゴール判定

    //差分ベクトルの大きさを調べる
    float distance = VSize(vDist);

    //指定したrange外に入ったら判定終了
    if (distance > range)
    {
        return false;
    }

    //自分の向きと差分ベクトルで内積を計算する
    float dot = VDot(parent->GetDir(), VNorm(vDist));

    //指定した角度の視界に入っていたら
    if (dot > angle)
    {
        return true;
    }

    return false;
}

//複数あるオブジェクトのポジションと半径の取得
// タグで指定されたPoint群から全ポジションと半径をまとめて取得
static std::vector<ObstacleData> GetObstaclesFromTags(const std::vector<int>& tags)
{
    std::vector<ObstacleData> obstacles;

    for (int tag : tags)
    {
        std::vector<Object*> objs = Master::mpObjectManager->FindsByTag(tag);

        for (auto obj : objs)
        {
            if (obj == nullptr)
                continue;

            // 各Objectが持つ全ポジションを取得
            const std::vector<VECTOR>& positions = obj->GetPositions();

            for (const auto& pos : positions)
            {
                ObstacleData data;
                data.pos = pos;                // 各位置
                data.radius = obj->GetRadius(); // 各オブジェクト固有の半径
                obstacles.push_back(data);
            }
        }
    }

    return obstacles;
}

//複数あるオブジェクトのポジションの取得
// タグで指定されたPoint群から全ポジションをまとめて取得
std::vector<VECTOR> GetPatrolPointsFromTag(int tag)
{
    std::vector<VECTOR> result;

    // タグでPoint群を検索
    std::vector<Object*> objs = Master::mpObjectManager->FindsByTag(tag);

    for (auto obj : objs)
    {
        if (obj == nullptr)
        {
            continue;
        }

        const std::vector<VECTOR>& positions = obj->GetPositions();
        result.insert(result.end(), positions.begin(), positions.end());
    }

    return result;
}

//壁専用
std::vector<WallBox>GetWallBoxesFromTags(const std::vector<int>& tags)
{
    std::vector<WallBox> result;

    for (int tag : tags)
    {
        std::vector<Object*> objs = Master::mpObjectManager->FindsByTag(tag);

        for (Object* obj : objs)
        {
            Wall* wall = dynamic_cast<Wall*>(obj);
            if (wall == nullptr)
            {
                continue;
            }

            result.push_back(wall->GetAABB_XZ());
        }
    }

    return result;

}