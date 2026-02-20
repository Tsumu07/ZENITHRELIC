#include "DxLib.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Object.h"
#include "../Haeder/Colliison.h"
#include "../Haeder/Line.h"
#include "../Haeder/Spider.h"
#include "../Haeder/Player.h"
#include "../Haeder/Wall.h"
#include "../Haeder/StageFrame.h"
#include "../Haeder/FSM.h"
#include "../Haeder/HitCapsule.h"
#include "../Master.h"
#include <math.h>
#include <string>


int Spider::Count = 1;

/**
* @fn　コンストラクタ
*/
Spider::Spider() : Object()
,mnSpiderModel(-1)
,mStateSpider(SpiderAnimetion::SpiderIidel)
,mvTargetMoveDirection(VGet(0.0f,0.0f,0.0f))
,mvPositionSter(VGet(0.0f, 0.0f, 0.0f))
,mvTargetMoveSpider(VGet(0.0f, 0.0f, 0.0f))
,dir(VGet(0.0f, 0.0f, 0.0f))
,pos(VGet(0.0f,0.0f,0.0f))
,nextPos(VGet(0.0f,0.0f,0.0f))
,SpiderBottom(VGet(0.0f,0.0f,0.0f))
,SpiderTop(VGet(0.0f,0.0f,0.0f))
,attackOffset(VGet(0.0f, 0.0f, 0.0f))
,attackPos(VGet(0.0f, 0.0f, 0.0f))
,moveVec(VGet(0.0f,0.0f,0.0f))
,SpiderAnimHandle()
,HitPlayer(false)
,AttackSpider(false)
,AnimetionFlag(false)
,AttackPlayer(false)
,m_isDeadStarted(false)
,mfAngle(0.0f)
,mnAnimetion1(-1)
,mnAnimetion2(-1)
,mfAnimCount1(0.0f)
,mfAnimCount2(0.0f)
,mfAnimBlendRate(1.0f)
,DeleteSpiderCount(0)
,SpiderVoise(-1)
,attackR(90.0f)
,speed(0.0f)
,SpiderR(0.0f)
,Invincible(0.0f)
{
}

/**
*  @fn デストラクタ
*/
Spider::~Spider()
{
}

/**
* @fn Initialize
*  @brief 初期化
*/
void Spider::Initaliza()
{
    //敵の読み込み
    mnSpiderModel = MV1LoadModel("Resource/Spider.x");

	//3Dモデルの大きさ(プレイヤー)
	MV1SetScale(mnSpiderModel, VGet(1.0f, 1.0f, 1.0f));

    //効果音の読み込み
    SpiderVoise = LoadSoundMem("Musics/se_voice_mushi04.mp3");

    //アニメーションで移動しているフレーム番号を検索する
    int moveAnimFrameIndex = MV1SearchFrame(mnSpiderModel, "root");

    //アニメーションで移動しているフレームを無効にする
    MV1SetFrameUserLocalMatrix(
        mnSpiderModel,
        moveAnimFrameIndex,
        MV1GetFrameLocalMatrix(mnSpiderModel, moveAnimFrameIndex)
    );

    //最初のアニメーション
    ChangeAnimaitonSpider(SpiderAnimetion::SpiderIidel);

    //追いかけるフラグ
    HitPlayer = false;

    //攻撃フラグ
    AttackSpider = false;

    m_isDeadStarted = false;
}

/**
* @fn Update
*  @brief 更新
*/
void Spider::Update()
{

     //クモの移動前
     mvPositionSter = GetPos();

     //FSMを動かす
     Object::Update();

     pos = GetPos();
     dir = GetDir();
     speed = GetSpeed();

     //次の移動先を計算
     moveVec = VScale(dir, speed);
     nextPos = VAdd(pos, moveVec);

     SpiderBottom = VAdd(nextPos, VGet(0.0f, 0.0f, 0.0f));

     SpiderTop = VAdd(nextPos, VGet(0.0f, 180.0f, 0.0f));

	 SpiderR = GetRadius();

     //攻撃範囲
     attackOffset = VScale(GetDir(), 150.0f);
     attackPos = VAdd(GetPos(), attackOffset);

     SetAttack(attackPos);

	 //--------オブジェクト群の取得--------//
	 //プレイヤー
     Object* GetPlayer = Master::mpObjectManager->FindByTag(100);
     auto player = dynamic_cast<Player*>(GetPlayer);

     VECTOR playerBottom = player->GetPos();
     VECTOR playerTop = VAdd(playerBottom, VGet(0.0f, 200.0f, 0.0f));
     float playerR = player->GetRadius();

     //攻撃の当たり判定
     if (mStateSpider == SpiderAnimetion::SpiderAttack)
     {
         AttackPlayer = Capsule::CheckColliisonToHitCapsule(
             GetAttack(),  //攻撃ポジション
             attackR,      //攻撃範囲
             playerBottom,
             playerTop,
             playerR
         );

         if (AttackPlayer && player->GetInvincible() == 0)
         {
             if (!player->IsDead())
             {
                 //ダメージを与える
                 player->Damage(60.0f);

                 player->SetHitEnemy(true);
             }
         }
     }

     //壁の当たり判定
     float radius = 65.0f;
     float height = 200.0f;
     VECTOR pos = GetPos();

     for (int i = 0; i < 2; i++)
     {
         bool hitLR = Capsule::ResolveWallCollision(radius, height, 1000, 1500, pos, moveVec);
         bool hitUD = Capsule::ResolveWallCollision(radius, height, 2000, 2500, pos, moveVec);

         if (!hitLR && !hitUD)
         {
             break;
         }
     }

     //無敵時間
     if (GetHitPlayer())
     {
         Invincible = 160.0f;
     }

     if (GetInvincible() > 0)
     {
         Invincible--;
     }

     if (Invincible <= 0)
     {
         Invincible = 0;

     }

     SetInvincible(Invincible);

     //クモを消す
     if (IsDead() && !m_isDeadStarted)
     {
         m_isDeadStarted = true;
         PlaySoundMem(SpiderVoise, DX_PLAYTYPE_BACK);
         DeleteSpiderCount = 120.0f;
     }

     if (m_isDeadStarted)
     {
         --DeleteSpiderCount;

         if (DeleteSpiderCount <= 0)
         {
             SetDeleteFlag(true);
         }
     }

	 // 移動中か、移動したい方向がある場合に処理を実行する
	 if (VSize(dir) > 0.001f) // dirはSetDirで正規化された移動方向
	 {
		 // dirを目標移動方向とする
		 mvTargetMoveDirection = dir;

		 float targetAngle;
		 float diffAngle;

		 // 角度を求められる (atan2f: (x, z) から Y軸回転角度を求める)
		 targetAngle = atan2f(mvTargetMoveDirection.x, mvTargetMoveDirection.z);

		 diffAngle = targetAngle - mfAngle;

		 // 角度の差を [-π, π] の範囲に修正する
		 if (diffAngle < -DX_PI_F)
		 {
			 diffAngle += DX_TWO_PI_F;
		 }
		 else if (diffAngle > DX_PI_F)
		 {
			 diffAngle -= DX_TWO_PI_F;
		 }

		 //角度の差を0に近づける
		 if (diffAngle > 0.0f)
		 {
			 diffAngle -= 0.5f;

			 if (diffAngle < 0.0f)
			 {
				 diffAngle = 0.0f;
			 }
		 }

		 else
		 {
			 diffAngle += 0.5f;
			 if (diffAngle > 0.0f)
			 {
				 diffAngle = 0.0f;
			 }

		 }

		 // 新しい角度の計算
		 mfAngle = targetAngle - diffAngle;

		 // MV1モデルにY軸回転をセット
		 MV1SetRotationXYZ(mnSpiderModel, VGet(0.0f, mfAngle + DX_PI_F, 0.0f));
	 }

    //アニメーション処理
    SpAnimetion();

    MV1SetPosition(mnSpiderModel, GetPos());


}

//アニメーションの切り替え処理
void Spider::ChangeAnimaitonSpider(SpiderAnimetion Spiderindex)
{
    //最初のアニメーションを保存
    mStateSpider = Spiderindex;


	//単発アニメーション(攻撃,ダメージ)が始まったらflagをtrue
	if (Spiderindex == SpiderAnimetion::SpiderAttack || Spiderindex == SpiderAnimetion::SpiderDamegi ||
		Spiderindex == SpiderAnimetion::SpiderDie)
	{
		AnimetionFlag = true;
	}

    //再生中のアニメーション２が有効状態だったらデッタチしておく
    if (mnAnimetion2 != -1)
    {
        MV1DetachAnim(mnSpiderModel, mnAnimetion2);
        mnAnimetion2 = -1;
    }

    //今まで再生されていた情報を２の方に保持しておく
    mnAnimetion2 = mnAnimetion1;
    mfAnimCount2 = mfAnimCount1;

    //今まで再生されていた情報を２の方に保持しておく
    mnAnimetion1 = MV1AttachAnim(mnSpiderModel, Spiderindex);

    mfAnimCount1 = 0.0f;

    //ブレンド率の初期化を設定
    // note: アニメーション２が有効でない場合はブレンドさせないで1.0にしておく
    mfAnimBlendRate = (mnAnimetion2 == -1 ? 1.0f : 0.0f);

}

//アニメーション再生処理
void Spider::SpAnimetion()
{
    //ブレンド率を加算していく
    if (mfAnimBlendRate < 1.0f)
    {
        mfAnimBlendRate += CHARA_ANIME_BLEND_SPEED;
        if (mfAnimBlendRate > 1.0f)
        {
            mfAnimBlendRate = 1.0f;
        }
    }

    float fAnimTotalTime;

    //アニメーション２の処理
    if (mnAnimetion1 != -1)
    {
        //総再生時間を取得
        fAnimTotalTime = MV1GetAttachAnimTotalTime(mnSpiderModel, mnAnimetion1);

        //再生時間を進める
        mfAnimCount1 += CHARA_PLAY_BLEND_SPEED;

        //ループさせる
        if (mfAnimCount1 >= fAnimTotalTime && mStateSpider != SpiderAnimetion::SpiderDie)
        {
            mfAnimCount1 = fmodf(mfAnimCount1, fAnimTotalTime);

			//単発アニメーション(攻撃,ダメージ)が始まったらflagをfalse
			if (mStateSpider == SpiderAnimetion::SpiderAttack || mStateSpider == SpiderAnimetion::SpiderDamegi ||
				mStateSpider == SpiderAnimetion::SpiderDie)
			{
				AnimetionFlag = false;
			}

        }

        //モデルの反映
        MV1SetAttachAnimTime(mnSpiderModel, mnAnimetion1, mfAnimCount1);

        //アニメーション反映率を設定
        MV1SetAttachAnimBlendRate(mnSpiderModel, mnAnimetion1, mfAnimBlendRate);

    }

    //アニメーション２の再生
    if (mnAnimetion2 != -1)
    {
        //総再生時間を取得
        fAnimTotalTime = MV1GetAttachAnimTotalTime(mnSpiderModel, mnAnimetion2);

        //再生時間を進める
        mfAnimCount2 += CHARA_PLAY_BLEND_SPEED;

        //ループさせる
        if (mfAnimCount2 >= fAnimTotalTime)
        {
            mfAnimCount2 = fmodf(mfAnimCount2, fAnimTotalTime);

        }

        //モデルの反映
        MV1SetAttachAnimTime(mnSpiderModel, mnAnimetion2, mfAnimCount2);

        //アニメーション反映率を設定
        MV1SetAttachAnimBlendRate(mnSpiderModel, mnAnimetion2, 1.0f - mfAnimBlendRate);
    }
}

/**
* @fn Draw
*  @brief 描画
*/
void Spider::Draw()
{

    //3Dモデルの描画クモ
    MV1DrawModel(mnSpiderModel);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

}

/**
* @fn Finaliza
*  @brief 終了処理
*/
void Spider::Finaliza()
{
    //3Dモデル削除
    MV1DeleteModel(mnSpiderModel);

}
