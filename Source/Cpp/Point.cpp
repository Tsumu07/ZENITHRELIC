#include "DxLib.h"
#include "../Haeder/Point.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/Object.h"
#include <math.h>

//コンストラクタ
Point::Point()
:Object()
,mnPointModelHandle(-1)
,mState(Animetion_Point::Neutral_Point)
, mnAnimetion1(-1)
, mnAnimetion2(-1)
, mfAnimCount1(0.0f)
, mfAnimCount2(0.0f)
, mfAnimBlendRate(0.0f)
, AnimetionFlag(false)
, mFloatTime(0.0f)
, mBaseY(GetPos().y)
, AnimHandle()
{

}

//デストラクタ
Point::~Point()
{

}

//初期化
void Point::Initaliza()
{
	//モデルの読み込み
	mnPointModelHandle = MV1LoadModel("Resource/Swarm09.x");

	int moveAnimFrameIndex = MV1SearchFrame(mnPointModelHandle, "root");

	//アニメーションで移動をしているフレームを無効にする
	MV1SetFrameUserLocalMatrix(
		mnPointModelHandle,
		moveAnimFrameIndex,
		MV1GetFrameLocalMatrix(mnPointModelHandle, moveAnimFrameIndex)
	);

	AnimHandle[Animetion_Point::Neutral_Point] = MV1LoadModel("Resource/PointEnemy/Swarm09_Idle.x");

	ChangeAnimaiton(Animetion_Point::Neutral_Point);

}

//更新
void Point::Update()
{
	mBaseY = GetPos().y;

    // 動く速さ
	mFloatTime += 0.05f;   

	VECTOR pos = GetPos();

	//振れ幅3.0f
	pos.y = mBaseY + sinf(mFloatTime) * 3.0f;

	SetPos(pos);

	MV1SetPosition(mnPointModelHandle, GetPos());

	//アニメーション処理
	PlayAnimetion();

}

//アニメーション切り替え処理
void Point::ChangeAnimaiton(Animetion_Point index)
{
	//現在のアニメーション状態を保存
	mState = index;

	//再生中のアニメーション２が有効状態だったらデッタチしておく
	if (mnAnimetion2 != -1)
	{
		MV1DetachAnim(mnPointModelHandle, mnAnimetion2);
		mnAnimetion2 = -1;
	}

	//今まで再生されていた情報を２の方に保持しておく
	mnAnimetion2 = mnAnimetion1;
	mfAnimCount2 = mfAnimCount1;

	// 新しいアニメーションをアタッチして、アタッチ番号を保持しておく
	mnAnimetion1 = MV1AttachAnim(mnPointModelHandle, 0, AnimHandle[index]);

	mfAnimCount1 = 0.0f;

	//ブレンド率の初期化を設定
	// note: アニメーション２が有効でない場合はブレンドさせないで1.0にしておく
	mfAnimBlendRate = (mnAnimetion2 == -1 ? 1.0f : 0.0f);
}

//アニメーション再生処理
void Point::PlayAnimetion()
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
		fAnimTotalTime = MV1GetAttachAnimTotalTime(mnPointModelHandle, mnAnimetion1);

		//再生時間を進める
		mfAnimCount1 += CHARA_PLAY_BLEND_SPEED;

		//ループさせる
		if (mfAnimCount1 >= fAnimTotalTime)
		{
			//
			mfAnimCount1 = fmodf(mfAnimCount1, fAnimTotalTime);
			//

		}

		//モデルの反映
		MV1SetAttachAnimTime(mnPointModelHandle, mnAnimetion1, mfAnimCount1);

		//アニメーション反映率を設定
		MV1SetAttachAnimBlendRate(mnPointModelHandle, mnAnimetion1, mfAnimBlendRate);

	}

	//アニメーション2の処理
	if (mnAnimetion2 != -1)
	{
		//総再生時間を取得
		fAnimTotalTime = MV1GetAttachAnimTotalTime(mnPointModelHandle, mnAnimetion2);

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
		MV1SetAttachAnimTime(mnPointModelHandle, mnAnimetion2, mfAnimCount2);

		//アニメーション反映率を設定
		MV1SetAttachAnimBlendRate(mnPointModelHandle, mnAnimetion2, 1.0f - mfAnimBlendRate);

	}

}

//画僧
void Point::Draw()
{
	MV1DrawModel(mnPointModelHandle);
}

//終了処理
void Point::Finaliza()
{
	//3Dモデル削除
	MV1DeleteModel(mnPointModelHandle);

}
