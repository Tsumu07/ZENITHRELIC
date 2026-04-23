#include "../Header/Player_state.h"
#include "../Header/GameManager.h"
#include "../Header/ObujectManager.h"
#include "../Header/Camera.h"
#include "../Header/Player.h"
#include "../Master.h"
#include "../Header/CheckKey.h"
#include "DxLib.h"
#include <cmath>


//-------------------------------
//-------------------------------
//-----------待機状態------------
void PSIdle::OnEnter(Object* parent)
{
	parent->SetSpeed(0.0f);

	Player* player = dynamic_cast<Player*>(parent);

	if (player)
	{
		player->ChangeAnimaiton(Animetion::Neutral);
	}

}

void PSIdle::OnExit(Object* parent)
{

}

int PSIdle::Update(Object* parent)
{

	//--------------------------------
    // 入力取得
    //--------------------------------
	DINPUT_JOYSTATE input;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	//---移動---//
	Right = (input.X >= 500.0f || CheckHitKey(KEY_INPUT_D));
	Left = (input.X <= -500.0f || CheckHitKey(KEY_INPUT_A));
	Up = (input.Y <= -500.0f || CheckHitKey(KEY_INPUT_W));
	Down = (input.Y >= 500.0f || CheckHitKey(KEY_INPUT_S));

	Move = Right | Left | Down | Up;

	//---攻撃---//
	Attack = (CheckDownController(PAD_INPUT_2) != 0 || CheckHitKey(KEY_INPUT_SPACE));

	//---拾う---//
	PickItem = (CheckDownController(PAD_INPUT_1) != 0 || CheckHitKey(KEY_INPUT_R));

	if (Move)
	{
		return PLAYER_STATE_WALK;
	}

	if (Attack)
	{
		return PLAYER_STATE_ATTACK;
	}

	if (PickItem)
	{
		return PLAYER_STATE_PICKITEM;
	}

	//ダメージを受ける
	Player* player = dynamic_cast<Player*>(parent);

	if (player->GetHitEnemy())
	{
		return PLAYER_STATE_DAMAGE;
	}

	//ゲームオーバー
	if (parent->GetHp() <= 0)
	{
		return PLAYER_STATE_DEATH;
	}

	return PLAYER_STATE_IDLE;
}

//-------------------------------
//-------------------------------
//-----------歩き状態------------
void PSWalk::OnEnter(Object* parent)
{
	//アニメーションをwalkに変更
	Player* player = dynamic_cast<Player*>(parent);
	if (player)
	{
		//アニメーションをwalkに変更
		player->ChangeAnimaiton(Animetion::Walk); // MV1版に置き換え
	}
}

void PSWalk::OnExit(Object* parent)
{
}

int PSWalk::Update(Object* parent)
{
	VECTOR dir = VGet(0.0f, 0.0f, 0.0f);

	//--------------------------------
    // 入力取得
    //--------------------------------
	DINPUT_JOYSTATE input;
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);

	//---移動---//
	Right = (input.X >= 500.0f || CheckHitKey(KEY_INPUT_D));
	Left = (input.X <= -500.0f || CheckHitKey(KEY_INPUT_A));
	Up = (input.Y <= -500.0f || CheckHitKey(KEY_INPUT_W));
	Down = (input.Y >= 500.0f || CheckHitKey(KEY_INPUT_S));

	Move = Right | Left | Down | Up;

	//---攻撃---//
	Attack = (CheckDownController(PAD_INPUT_2) != 0 || CheckHitKey(KEY_INPUT_SPACE));

	//---拾う---//
	PickItem = (CheckDownController(PAD_INPUT_1) != 0 || CheckHitKey(KEY_INPUT_R));

	if (Right)
	{
		dir.x = 1;
	}

	if (Left)
	{
		dir.x = -1;
	}

	if (Up)
	{
		dir.z = 1;
	}

	if (Down)
	{
		dir.z = -1;
	}

	// プレイヤーの移動方向を正規化してセット
	if (VSize(dir) > 0.1f)
	{
		parent->SetSpeed(15.0f);
		dir = VNorm(dir);

		//カメラのY軸回転角度を取得する
		float camera_r = Master::mpCamera->GetHorizontalAngle() * DX_PI_F / 180.0f;

		//カメラのY軸回転角度を移動方向に加算する
		float roty = atan2(dir.z, -dir.x) + (DX_PI / 2) + camera_r;

		// 移動方向を作成する
	    // プレイヤーの入力方向をカメラ角度に合わせて回転
		float cosY = cosf(camera_r);
		float sinY = sinf(camera_r);

		VECTOR moveDir;
		moveDir.x = dir.x * cosY - dir.z * sinY;
		moveDir.z = dir.x * sinY + dir.z * cosY;
		moveDir.y = 0.0f;

		parent->SetDir(VNorm(moveDir));
		parent->SetRot(VGet(0.0f, atan2f(moveDir.x, moveDir.z), 0.0f));
	}

	// 入力がなければIdle状態へ遷移する
	if (Move == 0)
	{
		return PLAYER_STATE_IDLE;
	}

	//Qキーが押されたらAttack状態へ遷移する
	if (Attack)
	{
		return PLAYER_STATE_ATTACK;
	}

	if (PickItem)
	{
		return PLAYER_STATE_PICKITEM;
	}

	//ダメージを受ける
	Player* player = dynamic_cast<Player*>(parent);

	if (player->GetHitEnemy())
	{
		return PLAYER_STATE_DAMAGE;
	}

	//ゲームオーバー
	if (parent->GetHp() <= 0)
	{
		return PLAYER_STATE_DEATH;
	}


	return PLAYER_STATE_WALK;
}

//-------------------------------
//-------------------------------
//-----------攻撃状態------------
void PSAttack::OnEnter(Object* parent)
{
	parent->SetSpeed(0.0f);

	// Playerにキャストしてアニメーションを切り替え
	Player* player = dynamic_cast<Player*>(parent);
	if (player)
	{
		player->ChangeAnimaiton(Animetion::Attack);
	}
}

void PSAttack::OnExit(Object* parent)
{
}

int PSAttack::Update(Object* parent)
{
	// Playerにダウンキャスト
	Player* player = dynamic_cast<Player*>(parent);

	// アニメーションが終了したかどうかを AnimetionFlag で判定する
	if (player && !player->IsAnimating())
	{
		// アニメーションが終了したら、待機状態へ遷移
		return PLAYER_STATE_IDLE;
	}

	return PLAYER_STATE_ATTACK;
}

//-------------------------------
//-------------------------------
//-----------拾う状態------------
void PSPicitem::OnEnter(Object* parent)
{
	parent->SetSpeed(0.0f);

	// Playerにキャストしてアニメーションを切り替え
	Player* player = dynamic_cast<Player*>(parent);
	if (player)
	{
		player->ChangeAnimaiton(Animetion::PickItem);
	}
}

void PSPicitem::OnExit(Object* parent)
{

}

int PSPicitem::Update(Object* parent)
{
	// Playerにダウンキャスト
	Player* player = dynamic_cast<Player*>(parent);

	// アニメーションが終了したかどうかを AnimetionFlag で判定する
	if (player && !player->IsAnimating())
	{
		// アニメーションが終了したら、待機状態へ遷移
		return PLAYER_STATE_IDLE;
	}

	return PLAYER_STATE_PICKITEM;
}

//-------------------------------
//-------------------------------
//---------ダメージ状態----------
void PSDamege::OnEnter(Object* parent)
{
	parent->SetSpeed(0.0f);

	// Playerにキャストしてアニメーションを切り替え
	Player* player = dynamic_cast<Player*>(parent);
	if (player)
	{
		player->ChangeAnimaiton(Animetion::Dame);
	}

}

void PSDamege::OnExit(Object* parent)
{

}

int PSDamege::Update(Object* parent)
{
	// Playerにダウンキャスト
	Player* player = dynamic_cast<Player*>(parent);

	// アニメーションが終了したかどうかを AnimetionFlag で判定する
	if (player && !player->IsAnimating())
	{
		player->SetHitEnemy(false);

		// アニメーションが終了したら、待機状態へ遷移
		return PLAYER_STATE_IDLE;
	}

	return PLAYER_STATE_DAMAGE;
}

//-------------------------------
//-------------------------------
//-----------死亡状態------------
void PSDeath::OnEnter(Object* parent)
{
	parent->SetSpeed(0.0f);

	// Playerにキャストしてアニメーションを切り替え
	Player* player = dynamic_cast<Player*>(parent);
	if (player)
	{
		player->ChangeAnimaiton(Animetion::Die);
	}

}

void PSDeath::OnExit(Object* parent)
{

}

int PSDeath::Update(Object* parent)
{
	return PLAYER_STATE_DEATH;
}
