#include "../Haeder/DxLibUtil.h"


//ê¸å`ï‚ä‘
VECTOR DxLibLerp(VECTOR& start, VECTOR& end, float t)
{
	VECTOR ret;
	ret = VAdd(start, VScale(VSub(end, start), t));

	return ret;
}
