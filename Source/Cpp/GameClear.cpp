#include "Dxlib.h"
#include "../Haeder/GameClear.h"
#include "../Haeder/SceneBase.h"
#include "../Haeder/SceneManager.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/CheckKey.h"
#include "../Haeder/Player.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/ItemBase.h" 
#include "../Haeder/InventoryScene.h"
#include "../Master.h"

  //コンストラクタ
 GameClear::GameClear()
 :SceneBase()
 ,m_skybox()
 ,skyboxPShandle(0)
 ,skyboxVShandle(0)
 ,SelectpictureR(0.0f)
 ,SelectpictureL(0.0f)
 ,SelectY(0.0f)
 ,ContinueSelectUI(0)
 ,TitleSelectUI(0)
 ,ExitSelectUI(0)
 ,GameClearUI()
 ,LogoX(0.0f)
 ,LogoY(0.0f)
 ,GameClearUIY(0.0f)
 ,MaxRight(0.0f)
 ,MaxLeft(0.0f)
 ,TitleUI(0.0f)
 ,ContinueUI(0.0f)
 ,ExitUI(0.0f)
 ,InputJoycon(false)
 ,ButtonMusic(0)
 ,GameClearBGM(0)
 ,m_price(0)
 ,GameClearLogo(-1)
 ,SelectPictureR(0.0f)
 ,SelectPictureL(0.0f)
 {
 }
 
  //デストラクタ
 GameClear::~GameClear()
 {
 }
 
  //初期化
 void GameClear::Initaliza()
 {
     SetCameraPositionAndTarget_UpVecY
     (
         VGet(0.0f, 100.0f, -200.0f),
         VGet(0.0f, 100.0f, 0.0f)
     );

     //カメラのクリッピング距離を設定　どこまで写すのか
     SetCameraNearFar(1.0f, 30000.0f);

     /////////サウンドの読み込み/////////
     //BGN
     GameClearBGM = LoadSoundMem("Musics/GameClear.mp3");
 
      //ボタン
      ButtonMusic = LoadSoundMem("Musics/poka01.mp3");
 
      //BGM再生
     PlaySoundMem(GameClearBGM, DX_PLAYTYPE_LOOP);
  
     LoadDivGraph("Assets/GameClearUI.png", 6, 2, 3, 320, 108, GameClearUI);

     //一番右
     MaxRight = 1180.0f;

     //一番左
     MaxLeft = 40.0f;

     //UI
     LogoX = 200.0f;
     LogoY = 0.0f;
     GameClearUIY = 700.0f;
     ContinueUI = 180.0f;
     TitleUI = 750.0f;
     ExitUI = 1320.0f;
     SelectpictureL = 40.0f;
     SelectpictureR = 465.0f;
     SelectY = 640.0f;

     ContinueSelectUI = 0;
     TitleSelectUI = 0;
     ExitSelectUI = 0;

      //一瞬の取得
     InputJoycon = false;
 
     //スカイボックスのインスタンスを作成する
     {
         m_skybox = new SkyBox();
         m_skybox->Initaliza();
         m_skybox->SetLayer(1);
         m_skybox->SetTag(0);
         m_skybox->SetPos(VGet(0.0f, 0.0f, 0.0f));
         m_skybox->SetDir(VGet(1.0f, 0.0f, 0.0f));
         m_skybox->SetSpeed(0.0f);
         m_skybox->SetTeam(1);
     }

     //SkyBox用頂点シェーダを読み込む
     skyboxVShandle = LoadVertexShader("SkyBoxVS.cso");

     //SkyBox用ピクセルシェーダーを読み込む
     skyboxPShandle = LoadPixelShader("SkyBoxPS.cso");

     GameClearLogo = LoadGraph("Assets/GameClear.png");
     SelectPictureR = LoadGraph("Assets/SelectpictureR.png");
     SelectPictureL = LoadGraph("Assets/SelectpictureL.png");


 }
 
  //更新
 void GameClear::Update()
 {
     ContinueSelectUI = 0;
     TitleSelectUI = 0;
     ExitSelectUI = 0;

     DINPUT_JOYSTATE input;
 

     //入力状態を取得
     GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
 
     if (input.Y == 0)
     {
         InputJoycon = false;
     }

     if (CheckDownController(PAD_INPUT_2) != 0 || CheckDownKey(KEY_INPUT_Q))
     {
         //ゲーム画面
         if (SelectpictureL >= 35.0f && SelectpictureL <= 45.0f)
         {
             Master::mpSceneManager->ChangeScene(SceneName::GameScene);

         }

         //タイトル
         else if (SelectpictureL >= 600.0f && SelectpictureL <= 610.0f)
         {
             Master::mpSceneManager->ChangeScene(SceneName::TitleScene);
         }

         //終了
         else if (SelectpictureL >= 1170.0f && SelectpictureL <= 1180.0f)
         {
             Master::mpGameManager->EndGameLoop();

         }
     }

     //右
     if (input.Y <= -500.0f && InputJoycon == false || CheckDownKey(KEY_INPUT_D))
     {
         PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

         SelectpictureR += 570;
         SelectpictureL += 570;

         InputJoycon = true;

     }

     //一番右
     if (SelectpictureL > MaxRight)
     {
         SelectpictureR = 465.0f;
         SelectpictureL = 40.0f;

     }

     //左
     if (input.Y >= 500.0f && InputJoycon == false || CheckDownKey(KEY_INPUT_A))
     {
         PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);
         SelectpictureR -= 570;
         SelectpictureL -= 570;

         InputJoycon = true;

     }

     //一番左
     if (SelectpictureL < MaxLeft)
     {
         SelectpictureR = 1605;
         SelectpictureL = 1180;

     }

     //カーソル
     if (SelectpictureL >= 38.0f && SelectpictureL <= 45.0f)
     {
         ContinueSelectUI = 1;

     }

     else if (SelectpictureL >= 600.0f && SelectpictureL <= 610.0f)
     {
         TitleSelectUI = 1;

     }

     else if (SelectpictureL >= 1170.0f && SelectpictureL <= 1180.0f)
     {
         ExitSelectUI = 1;

     }

     m_skybox->Update();


 }

 //描画
 void GameClear::Draw()
 {
     //合計金額
     m_price = g_inventory.GetTotalAmount();

     SetUseVertexShader(skyboxVShandle);

     // 使用するピクセルシェーダーをセット
     SetUsePixelShader(skyboxPShandle);

     m_skybox->Draw();

     //終わったら解除
     SetUseVertexShader(-1);
     SetUsePixelShader(-1);

     DrawGraph(LogoX, LogoY, GameClearLogo, true);
     DrawGraph(SelectpictureR, SelectY, SelectPictureR, true);
     DrawGraph(SelectpictureL, SelectY - 15, SelectPictureL, true);

     //UI
     DrawGraph(ContinueUI, GameClearUIY, GameClearUI[0 + ContinueSelectUI], true);
     DrawGraph(TitleUI, GameClearUIY, GameClearUI[2 + TitleSelectUI], true);
     DrawGraph(ExitUI, GameClearUIY, GameClearUI[4 + ExitSelectUI], true);

     //合計金額
     char price[32];
     sprintf_s(price, "合計金額 %d $", m_price);

     SetFontSize(48);
     DrawString(780, 550, price, GetColor(0, 0, 0));
     SetFontSize(16);

 }
 
  //終了処理
 void GameClear::Finaliza()
 {
     Master::mpObjectManager->Delete(m_skybox);
     m_skybox = nullptr;

     //ClearDrawScreen();

     DeleteSoundMem(GameClearBGM);
 }
