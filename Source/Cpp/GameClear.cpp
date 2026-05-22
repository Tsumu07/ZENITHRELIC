#include "Dxlib.h"
#include "../Header/GameClear.h"
#include "../Header/SceneBase.h"
#include "../Header/SceneManager.h"
#include "../Header/GameManager.h"
#include "../Header/CheckKey.h"
#include "../Header/Player.h"
#include "../Header/ObujectManager.h"
#include "../Header/ItemBase.h" 
#include "../Header/InventoryScene.h"
#include "../Header/ItemManeger.h"
#include "../Master.h"

extern Inventory g_inventory;

  //コンストラクタ
 GameClear::GameClear()
:SceneBase()
,m_skybox()
,skyboxPShandle(-1)
,skyboxVShandle(-1)
,SelectpictureR(0.0f)
,SelectpictureL(0.0f)
,SelectY(0.0f)
,LogoX(0.0f)
,LogoY(0.0f)
,GameClearUIY(0.0f)
,GameClearUI()
,TitleUI(0.0f)
,ExitUI(0.0f)
,ContinueSelectUI(-1)
,TitleSelectUI(-1)
,ExitSelectUI(-1)
,GameClearLogo(-1)
,SelectPictureR(0.0f)
,SelectPictureL(0.0f)
,Right(false)
,Left(false)
,Decide(false)
,MaxRight(0.0f)
,MaxLeft(0.0f)
,ContinueUI(0.0f)
,InputJoycon(false)
,ButtonMusic(-1)
,GameClearBGM(-1)
,m_price(-1)
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
     ButtonMusic = LoadSoundMem("Musics/Button.mp3");
 
      //BGM再生
     PlaySoundMem(GameClearBGM, DX_PLAYTYPE_LOOP);
  
     LoadDivGraph("Assets/GameClearUI.png", 6, 2, 3, 324, 108, GameClearUI);
     GameClearLogo = LoadGraph("Assets/GameClear.png");
     SelectPictureR = LoadGraph("Assets/SelectpictureR.png");
     SelectPictureL = LoadGraph("Assets/SelectpictureL.png");

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
     skyboxVShandle = LoadVertexShader("cso/SkyBoxVS.cso");

     //SkyBox用ピクセルシェーダーを読み込む
     skyboxPShandle = LoadPixelShader("cso/SkyBoxPS.cso");

     m_price = Master::mpItemManeger->GetTotalAmount();

 }
 
  //更新
 void GameClear::Update()
 {
     //--------------------------------
     // UI初期化
     //--------------------------------
     ContinueSelectUI = 0;
     TitleSelectUI = 0;
     ExitSelectUI = 0;

     //--------------------------------
     // 入力取得
     //--------------------------------
     DINPUT_JOYSTATE input;
     GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
     Right = (input.X >= 500.0f || CheckDownKey(KEY_INPUT_D));
     Left = (input.X <= -500.0f || CheckDownKey(KEY_INPUT_A));
     Decide = (CheckDownController(PAD_INPUT_2) || CheckDownKey(KEY_INPUT_SPACE));

     if (input.X == 0)
     {
         InputJoycon = false;
     }

     //--------------------------------
     // 左右移動
     //--------------------------------
     if (Right && !InputJoycon)
     {
         PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

         SelectpictureR += 570;
         SelectpictureL += 570;

         InputJoycon = true;
     }

     if (Left && !InputJoycon)
     {
         PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

         SelectpictureR -= 570;
         SelectpictureL -= 570;

         InputJoycon = true;
     }

     //--------------------------------
     // カーソルループ
     //--------------------------------
     if (SelectpictureL > MaxRight)
     {
         SelectpictureR = 465.0f;
         SelectpictureL = 40.0f;
     }

     if (SelectpictureL < MaxLeft)
     {
         SelectpictureR = 1605.0f;
         SelectpictureL = 1180.0f;
     }

     //--------------------------------
     // 決定入力
     //--------------------------------
     if (Decide)
     {
         PlaySoundMem(ButtonMusic, DX_PLAYTYPE_BACK);

         if (SelectpictureL >= 35.0f && SelectpictureL <= 45.0f)
         {
             Master::mpSceneManager->ChangeScene(SceneName::GameScene);
         }
         else if (SelectpictureL >= 600.0f && SelectpictureL <= 610.0f)
         {
             Master::mpSceneManager->ChangeScene(SceneName::TitleScene);
         }
         else if (SelectpictureL >= 1170.0f && SelectpictureL <= 1180.0f)
         {
             Master::mpGameManager->EndGameLoop();
         }
     }

     //--------------------------------
     // UIカーソル
     //--------------------------------
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

     //--------------------------------
     // SkyBox更新
     //--------------------------------
     m_skybox->Update();


 }

 //描画
 void GameClear::Draw()
 {

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

     DeleteSoundMem(GameClearBGM);
     DeleteSoundMem(ButtonMusic);

     DeleteGraph(GameClearLogo);
     DeleteGraph(SelectPictureR);
     DeleteGraph(SelectPictureL);

     //UI画像削除
     for (int i = 0; i < 6; i++)
     {
         DeleteGraph(GameClearUI[i]);
     }

 }
