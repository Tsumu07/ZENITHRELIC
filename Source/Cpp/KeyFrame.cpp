
#include "../Haeder/KeyFrame.h"


KeyFrame::KeyFrame(float k, VECTOR r) : key(k), rot(r)
{

}

KeyFrame::~KeyFrame()
{

}

void KeyFrame::SetKeyFrame(float k, VECTOR r)
{
	key = k;
	rot = r;
}