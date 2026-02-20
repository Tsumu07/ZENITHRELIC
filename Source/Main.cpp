#include "DxLib.h"
#include "Haeder/GameManager.h"
#include "Haeder/ObujectManager.h"
#include "Haeder//Camera.h"
#include "Haeder//CheckKey.h"
#include "Haeder//SceneManager.h"
#include "Haeder//Player.h"
#include "Haeder//StageFrame.h"
#include "Haeder//ResourceManeger.h"
#include "Master.h"
#include <string>
#include <EffekseerForDXLib.h>


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ウインドウモードで起動
	ChangeWindowMode(true);
	//ChangeWindowMode(false);

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
	Master::mpSceneManager->Initaliza();

	// 定数バッファの作成とセットアップ
	//シェーダーに受け渡す
	//カメラ
	Master::mpResourceManager->CreateConstbuff("Camera", sizeof(CB_LIGHT_CAMERA));
	Master::mpResourceManager->SetConstbuffPS("Camera", 4);

	//skybox
	Master::mpResourceManager->CreateConstbuff("Rotation", sizeof(CB_ROTATION));
	Master::mpResourceManager->SetConstbuffPS("Rotation", 5);

	////フェードイン、フェードアウト
	Master::mpResourceManager->CreateConstbuff("Dissolve", sizeof(CB_DISSOLVE_PARAM));
	Master::mpResourceManager->SetConstbuffPS("Dissolve", 6);

	//ゲージ
	Master::mpResourceManager->CreateConstbuff("Param", sizeof(CB_PARAM_DATA));
	Master::mpResourceManager->SetConstbuffPS("Param", 7);

	// ループ
	while(ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 && Master::mpGameManager->isGameLoop())
	{
		// 現在のカウントを取得する
		int time = GetNowCount();

		if(!Master::mpSceneManager->IsMenuScene())
		{

			//シーンマネージャーの更新
			Master::mpSceneManager->Update();

			//シーンマネージャーの描画
			Master::mpSceneManager->Draw();

			//必要であればオブジェクトの削除
			if (Master::mpObjectManager != nullptr)
			{
				Master::mpObjectManager->DeleteAllIfNeeded();
			}

		}

		else
		{
			ClearDrawScreen();

			Master::mpSceneManager->UpdateMenuScene();

			Master::mpSceneManager->DrawMenuScene();

			ScreenFlip();

			if (Master::mpSceneManager->MenuSceneEnd())
			{
				Master::mpSceneManager->DeleteMenuScene();

				Master::mpSceneManager->SetMenuSceneEnd(false);

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
	Master::mpSceneManager->Finaliza();

	Master::mpGameManager->Finaliza();

	//
	delete Master::mpGameManager;

	Master::Finalize();

	// DXライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}
