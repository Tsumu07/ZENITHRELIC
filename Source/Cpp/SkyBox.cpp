#include "../Haeder/SkyBox.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ResourceManeger.h"
#include "../Haeder/ObujectManager.h"
#include "../Haeder/SceneManager.h"
#include "../Master.h"

SkyBox::SkyBox()
:Object(),
width(0.0f),
height(0.0f),
depth(0.0f),
rotationAngle(0.0f)
,GetSceneName()
{
	ZeroMemory(vertex, sizeof(VERTEX) * 24);
	ZeroMemory(index, sizeof(short) * 36);

	graph = -1;
}

SkyBox::~SkyBox()
{

}

void SkyBox::Initaliza(void)
{
	LoadBox = "Assets/SkyBox.dds";

	graph = Master::mpResourceManager->LoadImageFromFile(LoadBox);

	 width = 20000 / 2;
	 height = 20000 / 2;
	 depth = 20000 / 2;

	//正面
	//左上
	vertex[0].pos = VGet(-width, height, -depth);//頂点座標
	vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);	   //法線
	vertex[0].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[0].u = 0.0f;
	vertex[0].v = 0.0f;
	//右上
	vertex[1].pos = VGet(width, height, -depth);//頂点座標
	vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);	   //法線
	vertex[1].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[1].u = 1.0f;
	vertex[1].v = 0.0f;
	//左下
	vertex[2].pos = VGet(-width, -height, -depth);//頂点座標
	vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);	   //法線
	vertex[2].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[2].u = 0.0f;
	vertex[2].v = 1.0f;
	//右下
	vertex[3].pos = VGet(width, -height, -depth);//頂点座標
	vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);	   //法線
	vertex[3].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[3].u = 1.0f;
	vertex[3].v = 1.0f;

	//上面
	//左上
	vertex[4].pos = VGet(-width, height, depth);//頂点座標
	vertex[4].norm = VGet(0.0f, 1.0f, 0.0f);	   //法線
	vertex[4].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[4].u = 0.0f;
	vertex[4].v = 0.0f;
	//右上
	vertex[5].pos = VGet(width, height, depth);//頂点座標
	vertex[5].norm = VGet(0.0f, 1.0f, 0.0f);	   //法線
	vertex[5].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[5].u = 1.0f;
	vertex[5].v = 0.0f;
	//左下
	vertex[6].pos = VGet(-width, height, -depth);//頂点座標
	vertex[6].norm = VGet(0.0f, 1.0f, 0.0f);	   //法線
	vertex[6].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[6].u = 0.0f;
	vertex[6].v = 1.0f;
	//右下
	vertex[7].pos = VGet(width, height, -depth);//頂点座標
	vertex[7].norm = VGet(0.0f, 1.0f, 0.0f);	   //法線
	vertex[7].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[7].u = 1.0f;
	vertex[7].v = 1.0f;

	//右面
	//左上
	vertex[8].pos = VGet(width, height, -depth);//頂点座標
	vertex[8].norm = VGet(1.0f, 0.0f, 0.0f);	   //法線
	vertex[8].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[8].u = 0.0f;
	vertex[8].v = 0.0f;
	//右上
	vertex[9].pos = VGet(width, height, depth);//頂点座標
	vertex[9].norm = VGet(1.0f, 0.0f, 0.0f);	   //法線
	vertex[9].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[9].u = 1.0f;
	vertex[9].v = 0.0f;
	//左下
	vertex[10].pos = VGet(width, -height, -depth);//頂点座標
	vertex[10].norm = VGet(1.0f, 0.0f, 0.0f);	   //法線
	vertex[10].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[10].u = 0.0f;
	vertex[10].v = 1.0f;
	//右下
	vertex[11].pos = VGet(width, -height, depth);//頂点座標
	vertex[11].norm = VGet(1.0f, 0.0f, 0.0f);	   //法線
	vertex[11].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[11].u = 1.0f;
	vertex[11].v = 1.0f;

	//裏面
	//左上
	vertex[12].pos = VGet(width, height, depth);//頂点座標
	vertex[12].norm = VGet(0.0f, 0.0f, 1.0f);	   //法線
	vertex[12].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[12].u = 0.0f;
	vertex[12].v = 0.0f;
	//右上
	vertex[13].pos = VGet(-width, height, depth);//頂点座標
	vertex[13].norm = VGet(0.0f, 0.0f, 1.0f);	   //法線
	vertex[13].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[13].u = 1.0f;
	vertex[13].v = 0.0f;
	//左下
	vertex[14].pos = VGet(width, -height, depth);//頂点座標
	vertex[14].norm = VGet(0.0f, 0.0f, 1.0f);	   //法線
	vertex[14].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[14].u = 0.0f;
	vertex[14].v = 1.0f;
	//右下
	vertex[15].pos = VGet(-width, -height, depth);//頂点座標
	vertex[15].norm = VGet(0.0f, 0.0f, 1.0f);	   //法線
	vertex[15].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[15].u = 1.0f;
	vertex[15].v = 1.0f;

	//下面
	//右下
	vertex[16].pos = VGet(width, -height, depth);//頂点座標
	vertex[16].norm = VGet(0.0f, -1.0f, 0.0f);	   //法線
	vertex[16].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[16].u = 0.0f;
	vertex[16].v = 0.0f;
	//左下
	vertex[17].pos = VGet(-width, -height, depth);//頂点座標
	vertex[17].norm = VGet(0.0f, -1.0f, 0.0f);	   //法線
	vertex[17].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[17].u = 1.0f;
	vertex[17].v = 0.0f;
	//右上
	vertex[18].pos = VGet(width, -height, -depth);//頂点座標
	vertex[18].norm = VGet(0.0f, -1.0f, 0.0f);	   //法線
	vertex[18].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[18].u = 0.0f;
	vertex[18].v = 1.0f;
	//左上
	vertex[19].pos = VGet(-width, -height, -depth);//頂点座標
	vertex[19].norm = VGet(0.0f, -1.0f, 0.0f);	   //法線
	vertex[19].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[19].u = 1.0f;
	vertex[19].v = 1.0f;

	//左面
	//左上
	vertex[20].pos = VGet(-width, height, depth);//頂点座標
	vertex[20].norm = VGet(-1.0f, 0.0f, 0.0f);	   //法線
	vertex[20].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[20].u = 0.0f;
	vertex[20].v = 0.0f;
	//右上
	vertex[21].pos = VGet(-width, height, -depth);//頂点座標
	vertex[21].norm = VGet(-1.0f, 0.0f, 0.0f);	   //法線
	vertex[21].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[21].u = 1.0f;
	vertex[21].v = 0.0f;
	//左下
	vertex[22].pos = VGet(-width, -height, depth);//頂点座標
	vertex[22].norm = VGet(-1.0f, 0.0f, 0.0f);	   //法線
	vertex[22].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[22].u = 0.0f;
	vertex[22].v = 1.0f;
	//右下
	vertex[23].pos = VGet(-width, -height, -depth);//頂点座標
	vertex[23].norm = VGet(-1.0f, 0.0f, 0.0f);	   //法線
	vertex[23].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[23].u = 1.0f;
	vertex[23].v = 1.0f;

	for (int i = 0; i < 6; i++)
	{
		index[(i * 6) + 0] = 0 + (i * 4);
		index[(i * 6) + 1] = 2 + (i * 4);
		index[(i * 6) + 2] = 1 + (i * 4);
		index[(i * 6) + 3] = 1 + (i * 4);
		index[(i * 6) + 4] = 2 + (i * 4);
		index[(i * 6) + 5] = 3 + (i * 4);
	}
}

void SkyBox::Update(void)
{	
	//SkyBoxの切り替え
	GetSceneName = Master::mpSceneManager->GetCurrentScene();

	switch (GetSceneName)
	{
	case TitleScene:
		LoadBox = "Assets/SkyBox.dds";
		break;
	case GameScene:
		LoadBox = "Assets/SkyBox.dds";
		break;
	case GameOverScene:
		LoadBox = "Assets/GameOver.dds";
		break;
	case GameClearScene:
		LoadBox = "Assets/GameClear.dds";
		break;
	default:
		break;
	}

	const float rotationSpeed = 0.0001f;

	rotationAngle += rotationSpeed;

	//一周したらリセット
	if (rotationAngle > DX_TWO_PI_F)
	{
		rotationAngle -= DX_TWO_PI_F;
	}
}

void SkyBox::Draw(void)
{

	graph = Master::mpResourceManager->LoadImageFromFile(LoadBox);
	
	SetLightEnable(FALSE);

	MATRIX rotM = MGetRotY(rotationAngle);

	VERTEX3DSHADER drawVertex[24];

	//シェーダー
	int skyboxCB = Master::mpResourceManager->GetConstBuff("Rotation");
	CB_ROTATION* cb = (CB_ROTATION*)GetBufferShaderConstantBuffer(skyboxCB);

	rotM = MTranspose(rotM);
	cb->Rot = rotM;
	UpdateShaderConstantBuffer(skyboxCB);

	//使用するテクスチャを0番にセット
	SetUseTextureToShader(0, graph);

	DrawPolygonIndexed3DToShader(vertex, 24, index, 12);

	rotM = MGetIdent();

	//元に戻す
	SetTransformToWorld(&rotM);

	SetLightEnable(TRUE);
}

void SkyBox::Finaliza()
{
	SetDeleteFlag(true);
}
