#pragma once

#include "DxLib.h"


class KeyFrame
{
public:
	float	key; //キー
	VECTOR	rot; //このキーの時の角度

	KeyFrame(float k, VECTOR r);
	virtual ~KeyFrame();

	void SetKeyFrame(float k, VECTOR r);
};
