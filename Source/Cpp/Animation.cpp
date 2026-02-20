#include "../Haeder/Animation.h"
#include "../Haeder/DxLibBox.h"
#include "../Haeder/DxLibUtil.h"
#include "../Haeder/Animator.h"//前方宣言したAnimatorの情報をcpp側で確定させる


Animation::Animation()
{
	keys.clear();
	tag = "";
}

Animation::~Animation()
{
	keys.clear();
	tag.clear();
}

void Animation::AddKeyFrame(KeyFrame key)
{
	keys.push_back(key);
}

void Animation::SetTag(std::string name)
{
	tag = name;
}

void Animation::Update(Animator* boss, float frame)
{
	VECTOR temp_rot = {};
	int motionIndex = -1;

	for (int i = 0; i < keys.size(); i++)
	{
		if (keys[i].key > frame)//現在のフレームよりキーの最終フレームのほうが大きい
		{
			motionIndex = i;//現在のモーションインデックス
			break;
		}
	}
	//全キーの最終フレームを過ぎているならアニメーションのリセットを行う
	if (motionIndex == -1)
	{
		frame = 0.0f;
		motionIndex = 0;
	}

	DxLibBox* target = boss->GetBox(tag); //Animatorから補間対象のDxLibBoxを取得する

	if (motionIndex == 0)
	{
		target->SetRot(keys[0].rot);
	}
	else
	{
		//  t =（現在のフレーム数 - 前回キーの最終フレーム） / （今回キーの最終フレーム - 前回キーの最終フレーム）;
		float t = (frame - keys[motionIndex - 1].key) / (keys[motionIndex].key - keys[motionIndex - 1].key);

		//回転の補間にはSpherelerp（球面線形補間）を使用する
		target->SetRot(DxLibLerp(keys[motionIndex - 1].rot, keys[motionIndex].rot, t));
	}
}
