#include "DxLib.h"
#include "Header/GameManager.h"
#include "Header/ObujectManager.h"
#include "Header//Camera.h"
#include "Header//CheckKey.h"
#include "Header//SceneManager.h"
#include "Header//Player.h"
#include "Header//StageFrame.h"
#include "Header//ResourceManager.h"
#include "Master.h"
#include <string>
#include <EffekseerForDXLib.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	//ChangeWindowMode(false);
	ChangeWindowMode(true);

	SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_MAXIMUM);

	SetGraphMode(1920, 1080, 32);

	SetUseLarge3DPositionSupport(TRUE);

	// DXライブラリ初期化処理
	if(DxLib_Init() == -1)
	{
		return -1;		// エラーが起きたら直ちに終了
	}

	Master::Initialize();

	//シーンマネージャーの初期化
	Master::GetSceneManager()->Initaliza();

	// 定数バッファの作成とセットアップ
	//シェーダーに受け渡す
	//カメラ
	Master::GetResourceManager()->CreateConstbuff("Camera", sizeof(CB_LIGHT_CAMERA));
	Master::GetResourceManager()->SetConstbuffPS("Camera", 4);

	//skybox
	Master::GetResourceManager()->CreateConstbuff("Rotation", sizeof(CB_ROTATION));
	Master::GetResourceManager()->SetConstbuffPS("Rotation", 5);

	////フェードイン、フェードアウト
	Master::GetResourceManager()->CreateConstbuff("Dissolve", sizeof(CB_DISSOLVE_PARAM));
	Master::GetResourceManager()->SetConstbuffPS("Dissolve", 6);

	//ゲージ
	Master::GetResourceManager()->CreateConstbuff("Param", sizeof(CB_PARAM_DATA));
	Master::GetResourceManager()->SetConstbuffPS("Param", 7);

	// ループ
	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && Master::GetGameManager()->isGameLoop())
	{
		// 現在のカウントを取得する
		int time = GetNowCount();

		if(!Master::GetSceneManager()->IsInventoryScene())
		{

			//シーンマネージャーの更新
			Master::GetSceneManager()->Update();

			//シーンマネージャーの描画
			Master::GetSceneManager()->Draw();

			//必要であればオブジェクトの削除
			if (Master::GetObjectManager() != nullptr)
			{
				Master::GetObjectManager()->DeleteAllIfNeeded();
			}

		}

		else
		{
			ClearDrawScreen();

			Master::GetSceneManager()->UpdateInventoryScene();

			Master::GetSceneManager()->DrawInventoryScene();

			ScreenFlip();

			if (Master::GetSceneManager()->InventorySceneEnd())
			{
				Master::GetSceneManager()->DeleteInventoryScene();

				Master::GetSceneManager()->SetInventorySceneEnd(false);

				//背景の色を灰色にする
				SetBackgroundColor(0, 0, 0);
			}

		}

		// １７ミリ秒(約秒間６０フレームだった時の１フレームあたりの経過時間)
		// 経過するまでここで待つ
		while (GetNowCount() - time < 17)
		{
		}
	}

	//シーンマネージャーの終了
	Master::GetSceneManager()->Finaliza();

	Master::GetGameManager()->Finaliza();

	Master::Finalize();

	// Effekseer終了処理
	Effkseer_End();

	// DXライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}