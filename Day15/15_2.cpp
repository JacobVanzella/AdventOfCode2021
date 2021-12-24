#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

// #define test
#ifdef test
    #define SZ 50
    #define sz 10
    #define NUM_TILES 5
    #define FILE_NAME "test.txt"
#else
    #define SZ 500
    #define sz 100
    #define NUM_TILES 5
    #define FILE_NAME "input.txt"
#endif

struct vert
{
    int32_t pos;
    int32_t risk;
};

int32_t h(int32_t pos) { return 1 * ((SZ - pos % SZ) + (SZ - pos / SZ)); }

int32_t reconstruct_path(const std::array<int32_t, SZ * SZ> &graph, int32_t src, std::map<int32_t, vert> cameFrom, vert current)
{
    int32_t cost = 0;
    while (current.pos != src)
    {
        cost += graph[current.pos];
        current = cameFrom.at(current.pos);
    }

    return cost;
}

int32_t AStar(const std::array<int32_t, SZ * SZ> &graph, const int32_t src, const int32_t dest)
{
    int32_t neighb[4] = {-1, 1, -SZ, SZ}; // {left, right, up, down}
    auto comp = [](vert a, vert b)
    { return a.risk > b.risk; };
    std::priority_queue<vert, std::vector<vert>, decltype(comp)> openSet(comp);
    std::map<int32_t, vert> cameFrom;
    std::array<int32_t, SZ * SZ> gScore, fScore;

    for (int32_t i = 0; i < SZ * SZ; i++)
        gScore[i] = fScore[i] = INT32_MAX;
    gScore[src] = 0;
    fScore[src] = h(src);
    openSet.emplace(vert{src, fScore[src]});

    while (!openSet.empty())
    {
        vert v = openSet.top();
        openSet.pop();

        // Reached destination
        if (v.pos == dest)
            return reconstruct_path(graph, src, cameFrom, v);

        for (auto dir : neighb)
        {
            // Bounds Check
            if ((v.pos % SZ == 0 && dir == -1) ||     // OoB Left
                (v.pos % SZ == SZ - 1 && dir == 1) || // OoB Right
                (v.pos / SZ == 0 && dir == -SZ) ||    // OoB Up
                (v.pos / SZ == SZ - 1 && dir == SZ))  // OoB Down
                continue;

            // Update the open set.
            int32_t tmp_gScore = gScore[v.pos] + graph[v.pos + dir];
            if (tmp_gScore < gScore[v.pos + dir])
            {
                cameFrom.emplace(v.pos + dir, v);
                gScore[v.pos + dir] = tmp_gScore;
                fScore[v.pos + dir] = tmp_gScore + h(v.pos + dir);
                openSet.emplace(vert{v.pos + dir, fScore[v.pos + dir]});
            }
        }
    }

    // Failed to find a valid path
    return -1;
}

int main(int argc, char const *argv[])
{
    std::array<int32_t, SZ * SZ> tileGraph;
    std::array<int32_t, SZ * SZ> graph;
    std::fstream input(FILE_NAME);

    for (int32_t i = 0; i < sz; i++)
    {
        for (int32_t j = 0; j < sz; j++)
        {
            tileGraph[sz * i + j] = input.peek() - 48;
            input.ignore(1, EOF);
        }
        input.ignore(1, EOF);
    }

    for (int32_t grdY = 0; grdY < NUM_TILES; grdY++)
        for (int32_t grdX = 0; grdX < NUM_TILES; grdX++)
            for (int32_t i = 0; i < sz; i++)
                for (int32_t j = 0; j < sz; j++)
                    if (tileGraph[sz * i + j] + grdX + grdY <= 9)
                        graph[SZ * (i + grdY * sz) + (j + grdX * sz)] = tileGraph[sz * i + j] + grdX + grdY;
                    else
                        graph[SZ * (i + grdY * sz) + (j + grdX * sz)] = (tileGraph[sz * i + j] + grdX + grdY) % 9;

    std::cout << "Ans. " << AStar(graph, 0, SZ * SZ - 1) << std::endl;
}