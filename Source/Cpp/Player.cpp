#include "DxLib.h"
#include "../Haeder/Player.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Object.h"
#include "../Haeder/HitCapsule.h"
#include "../Haeder/HpItem.h"
#include "../Haeder/Column.h"
#include "../Haeder/Goal.h"
#include "../Haeder/CheckKey.h"
#include "../Haeder/SceneManager.h"
#include "../Haeder/StageFrame.h"
#include "../Haeder/Wall.h"
#include "../Haeder/Spider.h"
#include "../Haeder/ItemManeger.h"
#include "../Haeder/EquippedItems.h"
#include "../Master.h"
#include <cassert>

Player::Player()
:Object()
,mnModelHandle(-1)
,mnWeponHandle(-1)
,mState(Animetion::Neutral)
,AnimHandle()
,mnAnimetion1(-1)
,mnAnimetion2(-1)
,mfAnimCount1(0.0f)
,mfAnimCount2(0.0f)
,mfAnimBlendRate(1.0f)
,AnimetionFlag(false)
,pos(VGet(0.0f,0.0f,0.0f))
,dir(VGet(0.0f,0.0f,0.0f))
,speed(0.0f)
,mvPlayerold(VGet(0.0f,0.0f,0.0f))
,attackOffset(VGet(0.0f,0.0f,0.0f))
,attackPos(VGet(0.0f,0.0f,0.0f))
,attackR(60.0f)
,moveVec(VGet(0.0f,0.0f,0.0f))
,nextPos(VGet(0.0f, 0.0f, 0.0f))
,playerBottom(VGet(0.0f, 0.0f, 0.0f))
,playerTop(VGet(0.0f, 0.0f, 0.0f))
, mvTargetMoveDirection(VGet(0.0f,0.0f,0.0f))
,playerR(80.0f)
,HitPillar(false)
,AttackPillar(false)
,HitSpider(false)
,HitGoal(false)
,Invincible(0)
,SelectItem(false)
,m_inventory(nullptr)
,m_equipped(nullptr)
,AttackSpider(false)
,HitEnemy(false)
,mfAngle(0.0f)
{
}

Player::~Player()
{
	delete m_inventory;
	delete m_equipped;
}

void Player::Initaliza()
{

	//3Dモデルの読み込み
	mnModelHandle = MV1LoadModel("Resource/Player.x");

	//武器の読み込み
	mnWeponHandle = MV1LoadModel("Resource/stick.x");

	//3Dモデルの大きさ(プレイヤー)
	MV1SetScale(mnModelHandle, VGet(80.0f, 80.0f, 80.0f));

	//3Dモデルの向き
	MV1SetRotationXYZ(mnModelHandle, VGet(0.0f, DX_PI_F, 0.0f));

	//アニメーションで移動しでいるフレームの番号を検索する
	int moveAnimFrameIndex = MV1SearchFrame(mnModelHandle, "root");

	//アニメーションで移動をしているフレームを無効にする
	MV1SetFrameUserLocalMatrix(
		mnModelHandle,
		moveAnimFrameIndex,
		MV1GetFrameLocalMatrix(mnModelHandle, moveAnimFrameIndex)
	);

	//アニメーションのみのファイル読み込み
	AnimHandle[Animetion::Neutral] = MV1LoadModel("Resource/Anime/Idle.x");
	AnimHandle[Animetion::Attack] = MV1LoadModel("Resource/Anime/AttackPlayer.x");
	AnimHandle[Animetion::MagicAttack] = MV1LoadModel("Resource/Anime/AttackMagic.x");
	AnimHandle[Animetion::Walk] = MV1LoadModel("Resource/Anime/Walkmv1.x");
	AnimHandle[Animetion::Run] = MV1LoadModel("Resource/Anime/Run.x");
	AnimHandle[Animetion::Stalsed] = MV1LoadModel("Resource/Anime/Stalsed.x");
	AnimHandle[Animetion::PickItem] = MV1LoadModel("Resource/Anime/PickUp.x");
	AnimHandle[Animetion::Dame] = MV1LoadModel("Resource/Anime/GetHit.x");
	AnimHandle[Animetion::Die] = MV1LoadModel("Resource/Anime/Die.x");

	//アイテム
	m_inventory = new ItemManeger();
	m_equipped = new EquippedItems();

}


void Player::Update()
{	

	//プレイヤーの移動前座標
	mvPlayerold = GetPos();

	//FSMを動かす
	Object::Update();

	//プレイヤーの情報を取得
	pos = GetPos();
	dir = GetDir();
	speed = GetSpeed();

	//次の移動先を計算
	moveVec = VScale(dir, speed);
	nextPos = VAdd(pos, moveVec);

	//攻撃範囲
	attackOffset = VScale(GetDir(), 100.0f); // 100前方
	attackPos = VAdd(GetPos(), attackOffset);

	//攻撃範囲の設定
	SetAttack(attackPos);

	//--------プレイヤーのカプセル情報--------//
	//下端
	playerBottom = VAdd(nextPos, VGet(0.0f, 0.0f, 0.0f));
	//上端
	playerTop = VAdd(nextPos, VGet(0.0f, 180.0f, 0.0f));
	

	//--------オブジェクト群の取得--------//
	//柱
	auto pillars = Master::mpObjectManager->FindsByTag(700);

	//ゴーレム
	auto Spiders = Master::mpObjectManager->FindsByTag(200);

	//ゴール
	Object* GetGoal = Master::mpObjectManager->FindByTag(800);
	auto goal = dynamic_cast<Goal*>(GetGoal);

    // 柱（縦カプセル）
	for (int i = 0; i < pillars.size(); i++)
	{
		Column* column = dynamic_cast<Column*>(pillars.at(i));

		if (!column)
		{
			continue;
		}

		VECTOR pillarBottom = column->GetPos();
		VECTOR pillarTop = VAdd(pillarBottom, VGet(0.0f, 200.0f, 0.0f));
		float  pillarR = column->GetRadius();

		//当たり判定
		HitPillar = Capsule::CheckCapsuleToHitCapsule(
			playerBottom, playerTop, playerR,
			pillarBottom, pillarTop, pillarR
		);

		if (HitPillar)
		{
			//-----押し返し処理-----//
			// プレイヤーと柱の中心を求める
			VECTOR playerCenter = VAdd(playerBottom, VScale(VSub(playerTop, playerBottom), 0.5f));
			VECTOR pillarCenter = VAdd(pillarBottom, VScale(VSub(pillarTop, pillarBottom), 0.5f));

			// 押し返す方向
			VECTOR pushDir = VSub(playerCenter, pillarCenter);
			pushDir.y = 0.0f;
			float len = VSize(pushDir);

			// めり込み距離
			float overlap = (playerR + pillarR) - len;

			if (overlap > 0.0f && len > 0.001f)
			{
				pushDir = VNorm(pushDir);
				pos = VAdd(pos, VScale(pushDir, overlap));
				SetPos(pos);
			}
		}

		//攻撃の当たり判定
		if (mState == Animetion::Attack)
		{
			AttackPillar = Capsule::CheckColliisonToHitCapsule(
				GetAttack(),   //攻撃ポジション
				attackR,       //攻撃範囲
				pillarBottom,
				pillarTop,
				pillarR
			);

			if (AttackPillar)
			{
				if (!column->IsDead())
				{
					column->Damage(20);

					//当たった時のエフェクトを追加
				}
			}

		}

	}

	//ゴーレムの当たり判定(本体)
	for (int i = 0; i < Spiders.size(); i++)
	{
		Spider* spider = dynamic_cast<Spider*>(Spiders.at(i));

		if (!spider)
		{
			continue;
		}

		//ゴーレム(本体)
		VECTOR SpiderBottom = spider->GetPos();
		VECTOR SpiderTop = VAdd(spider->GetPos(), VGet(0.0f, 200.0f, 0.0f));
		float  SpiderR = spider->GetRadius();

		//当たり判定
		HitSpider = Capsule::CheckCapsuleToHitCapsule(
			playerBottom, playerTop, playerR,
			SpiderBottom, SpiderTop, SpiderR
		);

		if (HitSpider && GetInvincible() == 0)
		{
			if (IsDead())
			{
				//ダメージを受ける
				Damage(60.0f);

				SetHitEnemy(true);
			}

		}

		//ゴーレムへ攻撃
		if (mState == Animetion::Attack)
		{
			AttackSpider = Capsule::CheckColliisonToHitCapsule(
				GetAttack(),  //攻撃ポジション
				attackR,      //攻撃範囲
				SpiderBottom,
				SpiderTop,
				SpiderR
			);

			if (AttackSpider && spider->GetInvincible() == 0)
			{
				if (!spider->IsDead())
				{
					//ダメージを与える
					spider->Damage(100.0f);

					spider->SetHitPlayer(true);
				}
			}
		}

	}

	//無敵時間
	if (GetHitEnemy())
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

	//ゴール判定
	if (GetGoal != nullptr)
	{
		//ゴールの当たり判定
		HitGoal = Capsule::CheckColliisonToHitCapsule(
			goal->GetPos(),
			goal->GetRadius(),
			playerBottom, playerTop, playerR
		);

		//ゴールについていたら
		if (HitGoal)
		{
			Master::mpSceneManager->ChangeScene(SceneName::GameClearScene);

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

	//ポジションを設定
	SetPos(pos);

	//-------アイテム関連-------//
	EquippedItems* equip = GetEquippedItems();
	ItemManeger* inv = GetInventory();

	if (CheckDownController(PAD_INPUT_5) != 0 || CheckDownKey(KEY_INPUT_Z))
	{
		ItemBase* item = equip->GetItem(0);

		if (item)
		{
			item->UseItem(this);            // 効果発動
			inv->RemoveItemByPointer(item); // アイテムを消費する
			equip->ClearSlot(0);            // スロットを空にする

		}
	}

	if (CheckDownController(PAD_INPUT_6) != 0 || CheckDownKey(KEY_INPUT_X))
	{
		ItemBase* item = equip->GetItem(1);

		if (item)
		{
			item->UseItem(this);            // 効果発動
			inv->RemoveItemByPointer(item); // アイテムを消費する
			equip->ClearSlot(1);            // スロットを空にする

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
		MV1SetRotationXYZ(mnModelHandle, VGet(0.0f, mfAngle + DX_PI_F, 0.0f));
	}

	//アニメーション処理
	PlayAnimetion();
	//武器を持たせる処理
	SetModelFramePosition("index_01_r", mnWeponHandle);

	MV1SetPosition(mnModelHandle, GetPos());

	//アイテム画面
	if (CheckDownController(PAD_INPUT_3) != 0 || CheckDownKey(KEY_INPUT_E) != 0)
	{
		Master::mpSceneManager->OpenInventory();

	}

	//死ぬ処理
	if (mState == Animetion::Die)
	{
		Master::mpSceneManager->ChangeScene(SceneName::GameOverScene);
	}

	return;
}

//モデルに武器を持たせる
void Player::SetModelFramePosition(const char* FrameName, int SetModelHandle)
{
	MATRIX FrameMatrix;
	int FrameIndex;

	FrameName = "index_03_r";

	SetModelHandle = mnWeponHandle;

	// フレーム名からフレーム番号を取得する
	FrameIndex = MV1SearchFrame(mnModelHandle, FrameName);

	//フレームの現在のワールドでの状態を示す行列を取得する
	FrameMatrix = MV1GetFrameLocalWorldMatrix(mnModelHandle, FrameIndex);

	//アタッチするモデルの行列をアタッチ先となるモデルのフレームの行列と同じにする
	auto mat = MMult(MGetRotAxis(VGet(0.0f, 0.0f, 1.0f), DX_PI_F / 4.0f), MGetScale(VGet(1.0f, 1.0f, 1.0f)));
	MV1SetMatrix(SetModelHandle, MMult(mat, FrameMatrix));
}

//アニメーション切り替え処理
void Player::ChangeAnimaiton(Animetion index)
{
	//現在のアニメーション状態を保存
	mState = index;

	//単発アニメーション（攻撃、ダメージ、アイテム拾い）が始まったらflagをtrue
	if (index == Animetion::Attack || index == Animetion::MagicAttack ||
		index == Animetion::PickItem || index == Animetion::Dame)
	{
		AnimetionFlag = true;
	}

	//再生中のアニメーション２が有効状態だったらデッタチしておく
	if (mnAnimetion2 != -1)
	{
		MV1DetachAnim(mnModelHandle, mnAnimetion2);
		mnAnimetion2 = -1;
	}

	//今まで再生されていた情報を２の方に保持しておく
	mnAnimetion2 = mnAnimetion1;
	mfAnimCount2 = mfAnimCount1;

	// 新しいアニメーションをアタッチして、アタッチ番号を保持しておく
	mnAnimetion1 = MV1AttachAnim(mnModelHandle, 0, AnimHandle[index]);

	mfAnimCount1 = 0.0f;

	//ブレンド率の初期化を設定
	// note: アニメーション２が有効でない場合はブレンドさせないで1.0にしておく
	mfAnimBlendRate = (mnAnimetion2 == -1 ? 1.0f : 0.0f);
}

//アニメーション再生処理
void Player::PlayAnimetion()
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

	//アニメーション2の処理
	if (mnAnimetion1 != -1)
	{
		//総再生時間を取得
		fAnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mnAnimetion1);

		//再生時間を進める
		mfAnimCount1 += CHARA_PLAY_BLEND_SPEED;

		//ループさせる
		if (mfAnimCount1 >= fAnimTotalTime && mState != Animetion::Die)
		{
			//
			mfAnimCount1 = fmodf(mfAnimCount1, fAnimTotalTime);
			//

	        // 単発アニメーション(攻撃、ダメージ、アイテム拾い)が終わったらflagをfalse
			if (mState == Animetion::Attack || mState == Animetion::MagicAttack ||
				mState == Animetion::PickItem || mState == Animetion::Dame)
			{
				AnimetionFlag = false;
			}

		}

		//モデルの反映
		MV1SetAttachAnimTime(mnModelHandle, mnAnimetion1, mfAnimCount1);

		//アニメーション反映率を設定
		MV1SetAttachAnimBlendRate(mnModelHandle, mnAnimetion1, mfAnimBlendRate);

	}

	//アニメーション2の処理
	if (mnAnimetion2 != -1)
	{
		//総再生時間を取得
		fAnimTotalTime = MV1GetAttachAnimTotalTime(mnModelHandle, mnAnimetion2);

		//再生時間を進める
		mfAnimCount2 += CHARA_PLAY_BLEND_SPEED;

		//ループさせる
		if (mfAnimCount2 >= fAnimTotalTime)
		{
			///
			mfAnimCount2 = fmodf(mfAnimCount2, fAnimTotalTime);
			///

		}

		//モデルの反映
		MV1SetAttachAnimTime(mnModelHandle, mnAnimetion2, mfAnimCount2);

		//アニメーション反映率を設定
		MV1SetAttachAnimBlendRate(mnModelHandle, mnAnimetion2, 1.0f - mfAnimBlendRate);

	}

}

void Player::Draw()
{
	MV1DrawModel(mnModelHandle);
	MV1DrawModel(mnWeponHandle);

}

void Player::Finaliza()
{
	MV1DeleteModel(mnModelHandle);
	MV1DeleteModel(mnWeponHandle);
}

