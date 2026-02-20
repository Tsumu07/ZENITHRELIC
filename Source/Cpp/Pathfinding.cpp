#include "../Haeder/Pathfinding.h"

//-----------------------------------------------
// 座標変換
//-----------------------------------------------
GridPillar AStarDynamic::ToGrid(const VECTOR& pos, float step)
{
    return GridPillar
    {
        (int)floor(pos.x / step),
        (int)floor(pos.z / step)
    };
}

VECTOR AStarDynamic::ToWorld(const GridPillar& Pillar, float step, float y)
{
    return VGet(
        Pillar.x * step + step * 0.5f,
        y,
        Pillar.z * step + step * 0.5f
    );
}

//-----------------------------------------------
// グリッド構築
//-----------------------------------------------
void AStarDynamic::BuildGrid(std::unordered_map<GridPillar, GridCell, GridPillarHash>& grid,
    const std::vector<ObstacleData>& obstacles,const std::vector<WallBox>& walls,float step)
{
    // 円形障害物
    for (const auto& obs : obstacles)
    {
        GridPillar c = ToGrid(obs.pos, step);
        int r = (int)ceil(obs.radius / step);

        for (int dx = -r; dx <= r; dx++)
        {
            for (int dz = -r; dz <= r; dz++)
            {
                grid[{ c.x + dx, c.z + dz }].blocked = true;
            }
        }
    }

    // 壁（AABB）
    for (const auto& wall : walls)
    {
        int minX = (int)floor(wall.minX / step);
        int maxX = (int)floor(wall.maxX / step);
        int minZ = (int)floor(wall.minZ / step);
        int maxZ = (int)floor(wall.maxZ / step);

        for (int x = minX; x <= maxX; x++)
        {
            for (int z = minZ; z <= maxZ; z++)
            {
                grid[{ x, z }].blocked = true;
            }
        }
    }
}

//-----------------------------------------------
// マスが塞がっているか
//-----------------------------------------------
bool AStarDynamic::IsBlockedCell(const GridPillar& Pillar,const std::unordered_map<GridPillar, GridCell, GridPillarHash>& grid)
{
    auto it = grid.find(Pillar);
    if (it == grid.end())
    {
        return false;
    }

    return it->second.blocked;
}

//-----------------------------------------------
// A*
//-----------------------------------------------
bool AStarDynamic::FindPath(const VECTOR& start,const VECTOR& goal,const std::vector<ObstacleData>& obstacles,
    const std::vector<WallBox>& walls,std::vector<VECTOR>& outPath,float step,float agentRadius,int maxIter)
{ 
    //----------------------------------
    // グリッド変換
    //----------------------------------
    auto toPillar = [&](const VECTOR& worldPos)
    {
        return GridPillar
        {
           (int)floor(worldPos.x / step),
           (int)floor(worldPos.z / step)
        };
    };

    auto toWorld = [&](const GridPillar& gridPos)
    {
            return VGet(gridPos.x * step + step * 0.5f,start.y, gridPos.z * step + step * 0.5f);
    };

    auto heuristic = [&](const GridPillar& a, const GridPillar& b)
    {
        VECTOR worldPosA = toWorld(a);
        VECTOR worldPosB = toWorld(b);

        return VSize(VSub(worldPosA, worldPosB));
    };

    GridPillar startK = toPillar(start);
    GridPillar goalK = toPillar(goal);

    //----------------------------------
    // 通れないマス作成
    //----------------------------------
    float Radius = agentRadius;

    std::unordered_set<GridPillar, GridPillarHash> blocked;

    // ---- 円障害物 ----
    for (const auto& obs : obstacles)
    {
        int minX = (int)floor((obs.pos.x - obs.radius - Radius) / step);
        int maxX = (int)floor((obs.pos.x + obs.radius + Radius) / step);
        int minZ = (int)floor((obs.pos.z - obs.radius - Radius) / step);
        int maxZ = (int)floor((obs.pos.z + obs.radius + Radius) / step);

        for (int gridX = minX; gridX <= maxX; gridX++)
        {
            for (int gridZ = minZ; gridZ <= maxZ; gridZ++)
            {
                VECTOR cellCenter = VGet(gridX * step + step * 0.5f,0.0f, gridZ * step + step * 0.5f);

                float dx = cellCenter.x - obs.pos.x;
                float dz = cellCenter.z - obs.pos.z;

                if (dx * dx + dz * dz <= (obs.radius + Radius) * (obs.radius + Radius))
                {
                    blocked.insert({ gridX, gridZ });
                }
            }
        }
    }

    // ---- 壁(AABB) ----
    for (const auto& wall : walls)
    {
        int minX = (int)floor((wall.minX - Radius) / step);
        int maxX = (int)floor((wall.maxX + Radius) / step);
        int minZ = (int)floor((wall.minZ - Radius) / step);
        int maxZ = (int)floor((wall.maxZ + Radius) / step);

        for (int gridX = minX; gridX <= maxX; gridX++)
        {
            for (int gridZ = minZ; gridZ <= maxZ; gridZ++)
            {
                blocked.insert({ gridX, gridZ });
            }
        }
    }

    // スタート or ゴールが塞がれていたら失敗
    if (blocked.count(startK) || blocked.count(goalK))
    {
        return false;
    }

    //----------------------------------
    // A*
    //----------------------------------
    std::priority_queue<Node, std::vector<Node>, NodeCmp> open;
    std::unordered_set<GridPillar, GridPillarHash> closed;
    std::unordered_map<GridPillar, float, GridPillarHash> gScore;
    std::unordered_map<GridPillar, GridPillar, GridPillarHash> parent;

    gScore[startK] = 0.0f;
    open.push({ startK, heuristic(startK, goalK) });

    const int dirs[8][2] =
    {
        { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 },
        { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 }
    };

    for (int iter = 0; iter < maxIter && !open.empty(); iter++)
    {
        GridPillar cur = open.top().Pillar;
        open.pop();

        if (closed.count(cur))
        {
            continue;
        }

        closed.insert(cur);

        if (cur == goalK)
        {
            //----------------------------------
            // 経路復元
            //----------------------------------
            outPath.clear();
            GridPillar tracePillar = cur;

            while (!(tracePillar == startK))
            {
                outPath.push_back(toWorld(tracePillar));
                tracePillar = parent[tracePillar];
            }

            outPath.push_back(start);
            std::reverse(outPath.begin(), outPath.end());

            return true;
        }

        for (auto& dir : dirs)
        {
            GridPillar nb{ cur.x + dir[0], cur.z + dir[1] };

            // 通れないマス
            if (blocked.count(nb))
                continue;

            // ---- 斜め移動の角抜け防止 ----
            if (dir[0] != 0 && dir[1] != 0)
            {
                GridPillar s1{ cur.x + dir[0], cur.z };
                GridPillar s2{ cur.x, cur.z + dir[1] };
                if (blocked.count(s1) || blocked.count(s2))
                { 
                    continue;
                }
            }

            float moveCost = (dir[0] && dir[1]) ? 1.414f : 1.0f;
            float tentativeGCost = gScore[cur] + moveCost * step;

            if (!gScore.count(nb) || tentativeGCost < gScore[nb])
            {
                gScore[nb] = tentativeGCost;
                parent[nb] = cur;
                open.push({ nb, tentativeGCost + heuristic(nb, goalK) });
            }
        }
    }

    return false;
}