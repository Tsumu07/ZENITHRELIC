
#include "../Haeder/DxLibBox.h"
#include "../Haeder/GameManager.h"
#include "../Haeder/ResourceManeger.h"
#include "../Master.h"

DxLibBox::DxLibBox()
{
	ZeroMemory(vertex, sizeof(VERTEX) * 24);//指定したメモリサイズを0で埋める（Windows専用）
	ZeroMemory(index, sizeof(short) * 36);

	pos = VGet(0.0f, 0.0f, 0.0f);
	rot = VGet(0.0f, 0.0f, 0.0f);
	scale = VGet(1.0f, 1.0f, 1.0f);
	offset = VGet(0.0f, 0.0f, 0.0f);

	parent = nullptr;
	graph = -1;

	CreateIdentityMatrix(&world);
}

DxLibBox::~DxLibBox()
{

}

void DxLibBox::Create(float width, float height, float depth)
{
	width /= 2;
	height /= 2;
	depth /= 2;

	//正面
	//左上
	vertex[0].pos = VGet(-width, height, -depth);//頂点座標
	vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);	   //法線
	vertex[0].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[0].u = 0.125f;
	vertex[0].v = 0.125f;
	//右上
	vertex[1].pos = VGet(width, height, -depth);//頂点座標
	vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);	   //法線
	vertex[1].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[1].u = 0.25f;
	vertex[1].v = 0.125f;
	//左下
	vertex[2].pos = VGet(-width, -height, -depth);//頂点座標
	vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);	   //法線
	vertex[2].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[2].u = 0.125f;
	vertex[2].v = 0.25f;
	//右下
	vertex[3].pos = VGet(width, -height, -depth);//頂点座標
	vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);	   //法線
	vertex[3].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[3].u = 0.25f;
	vertex[3].v = 0.25f;

	//上面
	//左上
	vertex[4].pos = VGet(-width, height, depth);//頂点座標
	vertex[4].norm = VGet(0.0f, 1.0f, 0.0f);	   //法線
	vertex[4].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[4].u = 0.125f;
	vertex[4].v = 0.0f;
	//右上
	vertex[5].pos = VGet(width, height, depth);//頂点座標
	vertex[5].norm = VGet(0.0f, 1.0f, 0.0f);	   //法線
	vertex[5].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[5].u = 0.25f;
	vertex[5].v = 0.0f;
	//左下
	vertex[6].pos = VGet(-width, height, -depth);//頂点座標
	vertex[6].norm = VGet(0.0f, 1.0f, 0.0f);	   //法線
	vertex[6].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[6].u = 0.125f;
	vertex[6].v = 0.125f;
	//右下
	vertex[7].pos = VGet(width, height, -depth);//頂点座標
	vertex[7].norm = VGet(0.0f, 1.0f, 0.0f);	   //法線
	vertex[7].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[7].u = 0.25f;
	vertex[7].v = 0.125f;

	//右面
	//左上
	vertex[8].pos = VGet(width, height, -depth);//頂点座標
	vertex[8].norm = VGet(1.0f, 0.0f, 0.0f);	   //法線
	vertex[8].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[8].u = 0.25f;
	vertex[8].v = 0.125f;
	//右上
	vertex[9].pos = VGet(width, height, depth);//頂点座標
	vertex[9].norm = VGet(1.0f, 0.0f, 0.0f);	   //法線
	vertex[9].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[9].u = 0.375f;
	vertex[9].v = 0.125f;
	//左下
	vertex[10].pos = VGet(width, -height, -depth);//頂点座標
	vertex[10].norm = VGet(1.0f, 0.0f, 0.0f);	   //法線
	vertex[10].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[10].u = 0.25f;
	vertex[10].v = 0.25f;
	//右下
	vertex[11].pos = VGet(width, -height, depth);//頂点座標
	vertex[11].norm = VGet(1.0f, 0.0f, 0.0f);	   //法線
	vertex[11].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[11].u = 0.375f;
	vertex[11].v = 0.25f;

	//裏面
	//左上
	vertex[12].pos = VGet(width, height, depth);//頂点座標
	vertex[12].norm = VGet(0.0f, 0.0f, 1.0f);	   //法線
	vertex[12].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[12].u = 0.375f;
	vertex[12].v = 0.125f;
	//右上
	vertex[13].pos = VGet(-width, height, depth);//頂点座標
	vertex[13].norm = VGet(0.0f, 0.0f, 1.0f);	   //法線
	vertex[13].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[13].u = 0.5f;
	vertex[13].v = 0.125f;
	//左下
	vertex[14].pos = VGet(width, -height, depth);//頂点座標
	vertex[14].norm = VGet(0.0f, 0.0f, 1.0f);	   //法線
	vertex[14].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[14].u = 0.375f;
	vertex[14].v = 0.25f;
	//右下
	vertex[15].pos = VGet(-width, -height, depth);//頂点座標
	vertex[15].norm = VGet(0.0f, 0.0f, 1.0f);	   //法線
	vertex[15].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[15].u = 0.5f;
	vertex[15].v = 0.25f;

	//下面
	//右下
	vertex[16].pos = VGet(width, -height, depth);//頂点座標
	vertex[16].norm = VGet(0.0f, -1.0f, 0.0f);	   //法線
	vertex[16].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[16].u = 0.25f;
	vertex[16].v = 0.0f;
	//左下
	vertex[17].pos = VGet(-width, -height, depth);//頂点座標
	vertex[17].norm = VGet(0.0f, -1.0f, 0.0f);	   //法線
	vertex[17].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[17].u = 0.375f;
	vertex[17].v = 0.0f;
	//右上
	vertex[18].pos = VGet(width, -height, -depth);//頂点座標
	vertex[18].norm = VGet(0.0f, -1.0f, 0.0f);	   //法線
	vertex[18].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[18].u = 0.25f;
	vertex[18].v = 0.125f;
	//左上
	vertex[19].pos = VGet(-width, -height, -depth);//頂点座標
	vertex[19].norm = VGet(0.0f, -1.0f, 0.0f);	   //法線
	vertex[19].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[19].u = 0.375f;
	vertex[19].v = 0.125f;

	//左面
	//左上
	vertex[20].pos = VGet(-width, height, depth);//頂点座標
	vertex[20].norm = VGet(-1.0f, 0.0f, 0.0f);	   //法線
	vertex[20].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[20].u = 0.0f;
	vertex[20].v = 0.125f;
	//右上
	vertex[21].pos = VGet(-width, height, -depth);//頂点座標
	vertex[21].norm = VGet(-1.0f, 0.0f, 0.0f);	   //法線
	vertex[21].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[21].u = 0.125f;
	vertex[21].v = 0.125f;
	//左下
	vertex[22].pos = VGet(-width, -height, depth);//頂点座標
	vertex[22].norm = VGet(-1.0f, 0.0f, 0.0f);	   //法線
	vertex[22].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[22].u = 0.0f;
	vertex[22].v = 0.25f;
	//右下
	vertex[23].pos = VGet(-width, -height, -depth);//頂点座標
	vertex[23].norm = VGet(-1.0f, 0.0f, 0.0f);	   //法線
	vertex[23].dif = GetColorU8(255, 255, 255, 255);//白を設定する
	vertex[23].u = 0.125f;
	vertex[23].v = 0.25f;

	for (int i = 0; i < 6; i++)
	{
		index[(i * 6) + 0] = 0 + (i * 4);
		index[(i * 6) + 1] = 1 + (i * 4);
		index[(i * 6) + 2] = 2 + (i * 4);
		index[(i * 6) + 3] = 1 + (i * 4);
		index[(i * 6) + 4] = 3 + (i * 4);
		index[(i * 6) + 5] = 2 + (i * 4);
	}
}

void DxLibBox::SetPos(float x, float y, float z)
{
	pos = VGet(x, y, z);
}

void DxLibBox::SetRot(float x, float y, float z)
{
	rot = VGet(x, y, z);
}

void DxLibBox::SetRot(VECTOR r)
{
	rot = r;
}

void DxLibBox::SetScale(float x, float y, float z)
{
	scale = VGet(x, y, z);
}

void DxLibBox::SetOffset(float x, float y, float z)
{
	offset = VGet(x, y, z);
}

void DxLibBox::SetParent(MATRIX* p)
{
	parent = p;
}

void DxLibBox::SetTexture(std::string texName)
{
	//テクスチャを読み込む
	graph = Master::mpResourceManager->LoadImageFromFile(texName);
}

MATRIX* DxLibBox::GetMatrix(void)
{
	return &world;
}

void DxLibBox::Transform(void)
{
	CreateIdentityMatrix(&world);//単位行列で初期化

	MATRIX mScale, mRotX, mRotY, mRotZ, mTrans, mOffset;

	CreateScalingMatrix(&mScale, scale.x, scale.y, scale.z);//拡大縮小行列を作成する
	CreateRotationXMatrix(&mRotX, rot.x);//X軸回転の行列を作成する
	CreateRotationYMatrix(&mRotY, rot.y);//Y軸回転の行列を作成する
	CreateRotationZMatrix(&mRotZ, rot.z);//Z軸回転の行列を作成する
	CreateTranslationMatrix(&mTrans, pos.x, pos.y, pos.z);//移動行列を作成する
	CreateTranslationMatrix(&mOffset, offset.x, offset.y, offset.z);//オフセット移動（回転前移動）行列を作成する

	//ワールドマトリクスはScale→Rotation→Translationの順で掛けて作成する
	CreateMultiplyMatrix(&world, &world, &mScale);
	//オフセット移動を反映させる
	CreateMultiplyMatrix(&world, &world, &mOffset);
	//回転行列を掛ける場合はYawPitchRollで掛ける
	//                       Y   X   Z
	CreateMultiplyMatrix(&world, &world, &mRotY);
	CreateMultiplyMatrix(&world, &world, &mRotX);
	CreateMultiplyMatrix(&world, &world, &mRotZ);
	CreateMultiplyMatrix(&world, &world, &mTrans);

	//親行列が設定されている場合は最後に掛ける
	if (parent != nullptr)
		CreateMultiplyMatrix(&world, &world, parent);
}

void DxLibBox::Draw(void)
{
	//ワールドマトリックスをテンポラリの頂点へ反映する
	VERTEX3D tempVertex[24] = {};
	for (int i = 0; i < 24; i++)
	{
		tempVertex[i] = vertex[i];//頂点情報をコピーする
		tempVertex[i].pos = VTransform(tempVertex[i].pos, world);//頂点をワールド変換する
		tempVertex[i].norm = VTransformSR(tempVertex[i].norm, world);//法線をワールド変換する
	}

	//テクスチャが設定されているか？
	if (graph != -1)
		DrawPolygonIndexed3D(tempVertex, 24, index, 12, graph, TRUE);
	else
		DrawPolygonIndexed3D(tempVertex, 24, index, 12, DX_NONE_GRAPH, TRUE);//テクスチャなし
}

void DxLibBox::SetUVFront(float u, float v, float uw, float vh)
{
	vertex[0].u = u;
	vertex[0].v = v;
	vertex[1].u = u + uw;
	vertex[1].v = v;
	vertex[2].u = u;
	vertex[2].v = v + vh;
	vertex[3].u = u + uw;
	vertex[3].v = v + vh;
}

void DxLibBox::SetUVBack(float u, float v, float uw, float vh)
{
	vertex[12].u = u;
	vertex[12].v = v;
	vertex[13].u = u + uw;
	vertex[13].v = v;
	vertex[14].u = u;
	vertex[14].v = v + vh;
	vertex[15].u = u + uw;
	vertex[15].v = v + vh;
}

void DxLibBox::SetUVUp(float u, float v, float uw, float vh)
{
	vertex[4].u = u;
	vertex[4].v = v;
	vertex[5].u = u + uw;
	vertex[5].v = v;
	vertex[6].u = u;
	vertex[6].v = v + vh;
	vertex[7].u = u + uw;
	vertex[7].v = v + vh;
}

void DxLibBox::SetUVBottom(float u, float v, float uw, float vh)
{
	vertex[16].u = u;
	vertex[16].v = v;
	vertex[17].u = u + uw;
	vertex[17].v = v;
	vertex[18].u = u;
	vertex[18].v = v + vh;
	vertex[19].u = u + uw;
	vertex[19].v = v + vh;
}

void DxLibBox::SetUVRight(float u, float v, float uw, float vh)
{
	vertex[8].u = u;
	vertex[8].v = v;
	vertex[9].u = u + uw;
	vertex[9].v = v;
	vertex[10].u = u;
	vertex[10].v = v + vh;
	vertex[11].u = u + uw;
	vertex[11].v = v + vh;
}

void DxLibBox::SetUVLeft(float u, float v, float uw, float vh)
{
	vertex[20].u = u;
	vertex[20].v = v;
	vertex[21].u = u + uw;
	vertex[21].v = v;
	vertex[22].u = u;
	vertex[22].v = v + vh;
	vertex[23].u = u + uw;
	vertex[23].v = v + vh;
}

