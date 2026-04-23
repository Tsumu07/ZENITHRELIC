#pragma once
#include "Object.h"
#include <DxLib.h>

//アニメーションID
enum Animetion_Point
{
	Neutral_Point = 0,

	Length_Point,
};

class Point : public Object
{
private:
	int mnPointModelHandle; //読み込んだポイントのモデルハンドル

	int AnimHandle[2];   //アニメーション

	bool AnimetionFlag;  //アニメーション再生中か

	///////////////
	Animetion_Point mState;          //現在のアニメーション状態
	int mnAnimetion1;          //現在アニメーションしている番号
	int mnAnimetion2;          //１つ目のアニメーション番号
	float mfAnimCount1;        //現在アニメーションの再生カウンタ
	float mfAnimCount2;        //１つ前のアニメーション再生カウンタ
	float mfAnimBlendRate;     //アニメーションのブレンド率(0.0f～1.0f)

	const float CHARA_ANIME_BLEND_SPEED = 0.1f;
	const float CHARA_PLAY_BLEND_SPEED = 0.1f;

	float mFloatTime;   // 上下用時間
	float mBaseY;       // 基準Y座標

public:
	Point();  //コンストラクタ
	~Point(); //デストラクタ

	void Initaliza(); //初期化
	void Update();    //更新
	void Draw();      //画僧
	void Finaliza();  //終了処理

	//モデルの取得
	int mnPoint() { return mnPointModelHandle; }

	//----アニメーション関連----
	bool IsAnimating() const { return AnimetionFlag; }
	//アニメーション切り替え処理
	void ChangeAnimaiton(Animetion_Point index);
	//アニメーション処理
	void PlayAnimetion();
	//アニメーションの取得
	Animetion_Point GetAnimationState() const { return mState; }


};