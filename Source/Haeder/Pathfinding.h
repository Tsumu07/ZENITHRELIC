#pragma once
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include "DxLib.h"
#include "Spider_State.h"

//-----------------------------------------------
// 円柱の障害物
//-----------------------------------------------
struct ObstaclData
{
	VECTOR pos;
	float radius;
};

//-----------------------------------------------
// 壁の障害物(AABB)
//-----------------------------------------------
struct WallBox
{
	float minX;
	float maxX;
	float minZ;
	float maxZ;
};

//-----------------------------------------------
// グリットキー
//-----------------------------------------------
struct GridPillar
{
	int x;
	int z;

	bool operator==(const GridPillar& o) const
	{
		return x == o.x && z == o.z;
	}
};

struct GridPillarHash
{
	size_t operator()(const GridPillar& k) const
	{
		return std::hash<int>()(k.x) ^ (std::hash<int>()(k.z) << 1);
	}
};

//-----------------------------------------------
// グリッドセル
//-----------------------------------------------
struct GridCell
{
	bool blocked = false;
};

//----------------------------
// A* ノード
//----------------------------
struct Node
{
	GridPillar Pillar;
	float f;
};

struct NodeCmp
{
	bool operator()(const Node& a, const Node& b) const
	{
		return a.f > b.f;
	}
};

//==================================================
// A* 本体
//==================================================
class AStarDynamic
{
public:
	static bool FindPath(
		const VECTOR& start,
		const VECTOR& goal,
		const std::vector<ObstacleData>& obstacles,
		const std::vector<WallBox>& walls,
		std::vector<VECTOR>& outPath,
		float step,
		float agentRadius,
		int maxIter
	);

private:
	static GridPillar ToGrid(const VECTOR& pos, float step);
	static VECTOR ToWorld(const GridPillar& Pillar, float step, float y);

	static void BuildGrid(
		std::unordered_map<GridPillar, GridCell, GridPillarHash>& grid,
		const std::vector<ObstacleData>& obstacles,
		const std::vector<WallBox>& walls,
		float step
	);

	static bool IsBlockedCell(
		const GridPillar& Pillar,
		const std::unordered_map<GridPillar, GridCell, GridPillarHash>& grid
	);
};
