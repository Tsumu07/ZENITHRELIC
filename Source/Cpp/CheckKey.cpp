#include "../Haeder/CheckKey.h"
#include "DxLib.h"

//DXLibに存在しないので自作
//Key用のキーバッファ
namespace CheckKey
{
	int ControlleBuffer[256]; // 押した瞬間(コントローラ)
	
	int downBuffer[256];	 // CheckDownKey用のキーバッファ
	int upBuffer[256];		 // CheckUpKey用のキーバッファ

	
};

//コントローラー専用　押した瞬間
int CheckDownController(int KeyCode)
{

	// 戻り値用の変数を用意
	int result = 0;

	int ControllerState = GetJoypadInputState(DX_INPUT_PAD1);
	
	//前回キーが押されておらず、かつ、現在キーが押されていたら「キーを押した瞬間」とする
	if (CheckKey::ControlleBuffer[KeyCode / 16] == 0 && ControllerState & KeyCode)
	{
		result = 1;
	}

	//16進数なので割る
	CheckKey::ControlleBuffer[KeyCode / 16] = ControllerState & KeyCode;

	return result;

}

// 0 キーは押されていない／1 キーを押した瞬間
//キーボード専用
int CheckDownKey(int KeyCode)
{
	// 戻り値用の変数を用意
	int result = 0;

	// 指定キーの現在の状態を取得
	int KeyState = CheckHitKey(KeyCode);

	// 前回キーが押されておらず、かつ、現在キーが押されていたら「キーを押した瞬間」とする
	if (CheckKey::downBuffer[KeyCode] == 0 && KeyState == 1)
	{
		result = 1;
	}

	// 現在のキー状態をバッファに格納
	CheckKey::downBuffer[KeyCode] = KeyState;

	return result;
}

// 指定されたキーが離された瞬間だけ 1 を返す関数
int CheckUpKey(int KeyCode)
{
	// 戻り値用の変数を用意
	int result = 0;

	// 指定キーの現在の状態を取得
	int KeyState = CheckHitKey(KeyCode);

	// 前回キーが押されており、かつ、現在キーが押されていなかったら「キーを離した瞬間」とする
	if (CheckKey::upBuffer[KeyCode] == 1 && KeyState == 0)
	{
		result = 1;
	}

	// 現在のキー状態をバッファに格納
	CheckKey::upBuffer[KeyCode] = KeyState;

	return result;
}
