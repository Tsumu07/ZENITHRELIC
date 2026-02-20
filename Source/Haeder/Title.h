#pragma once
#include "SceneBase.h"
#include "../Haeder/SkyBox.h"

class Title : public SceneBase
{
private:

    //SkyBox関係
    SkyBox* m_skybox;
    int skyboxPShandle;
    int skyboxVShandle;

    //---UI関係---//
    float SelectpictureR;
    float SelectpictureL;
    float SelectY;

    float LogoX;
    float LogoY;

    float TitleUIY;

    float GameUI;

    float SettingUI;

    float ExitUI;

    int TitleUI[7];
    int StageUI[6];

    float GuideUIX;
    float GuideUIY;

    float PlusMinusUIX;
    float PlusMinusUIY;

    int GameSelectUI;
    int SettingSelectUI;
    int ExitSelectUI;

    int NomalStageUI;
    int CreatedStageNo1UI;
    int CreatedStageNo2UI;
    //------------//
    
    //セレクトの制限
    //右
    float MaxRight;

    //左
    float MaxLeft;

    bool InputJoycon;
    //--------//

    //ステージ選択
    bool StageSelect;

    //BGM
    int ButtonMusic;
    int TitleBGM;

    //保存したステージ番号
    int StageNumber;

    //保存なしの表示
    float WarnCount;
    bool WarnFlag;


public:
    Title();   //コンストラクタ
    ~Title();  //デストラクタ

    void Initaliza();  //初期化
    void Update();     //更新
    void Draw();       //描画
    void Finaliza();   //終了処理

    //選択したステージナンバーを設定
    void SetStageNumber(int number) { StageNumber = number; }

    //選択したステージナンバーの取得
    int GetStageNumber()const { return StageNumber; }

};

// 共通インスタンスを宣言（extern）
extern Title g_Title;
