#pragma once

#include <map>
#include <string>
#include <list>
#include "DxLib.h"

// ライト・カメラ用定数バッファ構造体
struct CB_LIGHT_CAMERA
{
	FLOAT4 CameraPos;
	FLOAT4 LightDir;
};

//skybox用定数バッファ構造体
struct CB_ROTATION
{
	MATRIX Rot;
};

//フェードイン、フェードアウト用定数バッファ構造体
struct CB_DISSOLVE_PARAM
{
	float dissolveThreshold;
	float dissolveRange;
	float dummy[2];
};

//ゲージ用定数バッファ構造体
struct CB_PARAM_DATA
{
	float hp[4];
	float baseColor[4];
	float diffColor[4];
	float lostColor[4];
};

class ResourceManager
{
private:
	std::map<std::string, int> m_images;
	std::map<std::string, int> m_effects;
	std::map<std::string, int> m_constbuff;


public:
	ResourceManager() = default;
	~ResourceManager() = default;

	int LoadImageFromFile(std::string name);
	void ReleaseAllImages();
	int GetImage(std::string name);

	int LoadEffectFromFile(std::string name, float baseScale = 1.0f);
	int GetEffect(std::string name);

	void UnloadImage(std::string tag);
	void UnloadImage(int handle);

	void UnloadEffect(std::string tag);

	void Uninitializa(void);

	int CreateConstbuff(std::string name, int size);
	void SetConstbuffVS(std::string name, int slot);
	void SetConstbuffPS(std::string name, int slot);
	int GetConstBuff(std::string name);

	
};