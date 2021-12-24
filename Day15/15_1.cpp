#include <array>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

// #define test
#ifdef test
    #define SZ 10
    #define FILE_NAME "test.txt"
#else
    #define SZ 100
    #define FILE_NAME "input.txt"
#endif

int32_t dijkstra(const std::array<int32_t, SZ * SZ> &graph, const int32_t source, const int32_t dest)
{
    auto comp = [](std::pair<int32_t, int32_t> a, std::pair<int32_t, int32_t> b)
    { return (a.second > b.second); };

    std::priority_queue<std::pair<int32_t, int32_t>, std::vector<std::pair<int32_t, int32_t>>, decltype(comp)> pq(comp);
    std::vector<int32_t> dist(SZ * SZ, INT32_MAX);
    int32_t neighbours[4] = {-1, 1, -SZ, SZ}; // {left, right, up, down}

    pq.emplace(source, 0);
    dist[source] = 0;

    while (!pq.empty())
    {
        int32_t u = pq.top().first;
        pq.pop();

        for (auto dir : neighbours)
        {
            // Bounds Check
            if ((u % SZ == 0 && dir == -1) ||     // OoB Left
                (u % SZ == SZ - 1 && dir == 1) || // OoB Right
                (u / SZ == 0 && dir == -SZ) ||    // OoB Up
                (u / SZ == SZ - 1 && dir == SZ))  // OoB Down
                continue;

            int32_t v = u + dir;
            if (dist[u] + graph[v] < dist[v])
            {
                dist[v] = dist[u] + graph[v];
                pq.emplace(v, dist[v]);
            }
        }
    }

    return dist[dest];
}

int main(int argc, char const *argv[])
{
    std::array<int32_t, SZ * SZ> graph;
    std::fstream input(FILE_NAME);

    for (int32_t i = 0; i < SZ; i++)
    {
        for (int32_t j = 0; j < SZ; j++)
        {
            graph[SZ * i + j] = input.peek() - 48;
            input.ignore(1, EOF);
        }
        input.ignore(1, EOF);
    }

    std::cout << "Ans. " << dijkstra(graph, 0, SZ * SZ - 1) << std::endl;
}