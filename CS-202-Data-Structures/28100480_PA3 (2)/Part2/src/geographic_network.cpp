#include "../include/geographic_network.h"
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
#include <limits>
#include <functional>
#include <unordered_map>
#include <climits>

// -- Custom Implementation of DSU
struct DSU 
{
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;

    void makeSet(int first)
    {
        parent[first] = first;
        rank[first] = 0;
    }

    int find(int first)
    {
        if (parent.find(first) == parent.end()) return first;
        if (first != parent[first]) parent[first] = find(parent[first]);
        return parent[first];
    }

    void unionSets(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b) return;
        
        if (rank[a] < rank[b]) parent[a] = b;
        else if (rank[a] > rank[b]) parent[b] = a;
        else {parent[b] = a; rank[a]++;}
    }
};

GeographicNetwork::GeographicNetwork() = default;
GeographicNetwork::GeographicNetwork(GeographicNetwork &&other) noexcept : adjList(std::move(other.adjList)) {}
GeographicNetwork &GeographicNetwork::operator=(GeographicNetwork &&other) noexcept
{
    if (this != &other)
    {
        adjList = std::move(other.adjList);
    }
    return *this;
}

// --- Vertex Management ---
void GeographicNetwork::addVertex(int node)
{
    if (node < 0) return;
    if (adjList.find(node) != adjList.end()) return;

    adjList[node] = std::vector<Edge>();
}

void GeographicNetwork::removeVertex(int node)
{
    if (node < 0) return;
    if (adjList.find(node) == adjList.end()) return;

    adjList.erase(node);

    for (auto &pair: adjList)
    {
        auto &edge = pair.second;
        int i = 0;
        while (i < edge.size())
        {
            if (edge[i].to == node) edge.erase(edge.begin() + i);
            else i++;
        }    
    }
}

// --- Edge Management ---
void GeographicNetwork::addEdge(int from, int to, int weight)
{
    if (from < 0) return;
    if (to < 0) return;

    if (adjList.find(from) == adjList.end()) return;
    if (adjList.find(to) == adjList.end()) return;

    removeEdge(from, to);

    adjList[from].push_back({to, weight});

    if (from != to) adjList[to].push_back({from, weight});
}

void GeographicNetwork::removeEdge(int from, int to)
{
    if (from < 0) return;
    if (to < 0) return;

    bool from_Exist = (adjList.find(from) != adjList.end());
    bool to_Exist = (adjList.find(to) != adjList.end());  

    if (from_Exist)
    {
        auto &edge = adjList[from];
        int i = 0;
        while (i < edge.size())
        {
            if (edge[i].to == to) edge.erase(edge.begin() + i);
            else i++;
        }
    }

    if (to_Exist)
    {
        auto &edge = adjList[to];
        int i = 0;
        while (i < edge.size())
        {
            if (edge[i].to == from) edge.erase(edge.begin() + i);
            else i++;
        }
    }
}

// --- Graph Queries ---
bool GeographicNetwork::hasEdge(int from, int to) const
{
    if (from  < 0) return false;
    if (to < 0) return false;
    if (adjList.find(from) == adjList.end()) return false;
    if (adjList.find(to) == adjList.end()) return false; 

    for (auto edge : adjList.at(from))
    {
        if (edge.to == to) return true;
    }

    return false;
}

std::vector<int> GeographicNetwork::getAdjacent(int from) const
{
    if (from < 0) return {};
    if (adjList.find(from) == adjList.end()) return {};

    std::vector<int> parosi;
    for (auto edge: adjList.at(from))
    {
        parosi.push_back(edge.to);
    }
    return parosi;
}

// --- Core Algorithm: Dijkstra's ---
std::optional<std::vector<int>> GeographicNetwork::findShortestPath(int start, int end) const
{
    if (start < 0) return std::nullopt;
    if (end < 0) return std::nullopt;
    if (adjList.find(start) == adjList.end()) return std::nullopt;
    if (adjList.find(end) == adjList.end()) return std::nullopt;

    if (start == end) return std::vector<int>{start};

    using P = std::pair<int, int>;
    
    std::priority_queue<P, std::vector<P>, std::greater<P>> priority_q;
    std::unordered_map<int, int> distance;
    std::unordered_map<int, int> parent;
    std::vector<int> path;

    for (auto pair: adjList)
    {
        distance[pair.first] = std::numeric_limits<int>::max();
    }

    distance[start] = 0;
    parent[start] = -1;
    priority_q.push({0, start});

    while (!priority_q.empty())
    {
        int first = priority_q.top().first;
        int second = priority_q.top().second;
        priority_q.pop();

        if (first > distance[second]) continue;
        if (second == end) break;

        for (auto edge : adjList.at(second))
        {
            int to =edge.to;
            int weigHT = edge.weight;

            if (distance[second] + weigHT < distance[to])
            {
                distance[to] = distance[second] + weigHT;
                parent[to] = second;
                priority_q.push({distance[to], to});
            }
        }
    }

    if (distance[end] == std::numeric_limits<int>::max()) return std::nullopt;
    
    for (int hehe = end; hehe != -1; hehe = parent[hehe])
    {
        path.push_back(hehe);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

// -- Helper Function to sort
bool compareMSTedges(GeographicNetwork::MstEdge& a, GeographicNetwork::MstEdge& b)
{
    return a.weight < b.weight;
}

// --- Core Algorithm: Kruskal's for MST ---
std::vector<GeographicNetwork::MstEdge> GeographicNetwork::calculateMinimumSpanningTree() const
{
    if (adjList.empty()) return {};

    std::vector<MstEdge> result;
    std::vector<MstEdge> totalEdges;
    DSU dsu;

    for (auto pair: adjList)
    {
        int first = pair.first;
        dsu.makeSet(first);

        for (auto edge: pair.second)
        {
            int to = edge.to;
            if (first < to)
            {
                totalEdges.push_back({first, to, edge.weight});
            }
        }
    }
    std::sort(totalEdges.begin(), totalEdges.end(), compareMSTedges);

    for (auto edge: totalEdges)
    {
        if (dsu.find(edge.u) != dsu.find(edge.v))
        {
            dsu.unionSets(edge.u, edge.v);
            result.push_back(edge);
        }
    }
    return result;
}

// --- Implementations of Advanced Analysis Functions ---

std::vector<int> GeographicNetwork::findCriticalNodes() const
{
    if (adjList.empty()) return {};

    std::vector<int> criticalNode;
    std::unordered_map<int, int> distance;
    std::unordered_map<int, int> low;
    std::unordered_map<int, int> parent;
    int time = 0;

    for (auto pair: adjList)
    {
        distance[pair.first] = -1;
        low[pair.first] = -1;
        parent[pair.first] = -1;
    }

    for (auto pair:adjList)
    {
        if (distance[pair.first] == -1) findAP_dfs(pair.first, time, parent, distance, low, criticalNode);
    }

    std::sort(criticalNode.begin(), criticalNode.end());
    criticalNode.erase(std::unique(criticalNode.begin(), criticalNode.end()), criticalNode.end());

    return criticalNode;
}

void GeographicNetwork::findAP_dfs(int u, int &time, std::unordered_map<int, int> &parent, std::unordered_map<int, int> &disc, std::unordered_map<int, int> &low, std::vector<int> &result) const
{
    if (adjList.find(u) == adjList.end()) return;
    
    int children = 0;
    time++;
    disc[u] = time;
    low[u] = time;

    for (auto edge: adjList.at(u))
    {
        int to = edge.to;
        if (to == parent[u]) continue;

        if (disc[to] != -1) low[u] = std::min(low[u], disc[to]);
        else
        {
            children++;
            parent[to] = u;
            findAP_dfs(to, time, parent, disc, low, result);

            low[u] = std::min(low[u], low[to]);

            if (parent[u] != -1 && low[to] >= disc[u]) result.push_back(u);
        }
    }

    if (parent[u] == -1 && children > 1) result.push_back(u);
}

std::optional<std::vector<int>> GeographicNetwork::findPathWithMinEffort(int start, int end) const
{
    if (start < 0) return std::nullopt;
    if (end < 0) return std::nullopt;
    if (adjList.find(start) == adjList.end()) return std::nullopt;
    if (adjList.find(end) == adjList.end()) return std::nullopt;

    if (start == end) return std::vector<int>{start};

    using P = std::pair<int, int>;
    
    std::priority_queue<P, std::vector<P>, std::greater<P>> priority_q;
    std::unordered_map<int, int> maxminWeight;
    std::unordered_map<int, int> parent;
    
    for (auto pair:adjList) 
    {
        maxminWeight[pair.first] = std::numeric_limits<int>::max();
    }

    maxminWeight[start] = 0;
    parent[start] = -1;
    priority_q.push({0, start});

    while (!priority_q.empty())
    {
        int minEffort = priority_q.top().first;
        int second = priority_q.top().second;
        priority_q.pop();

        if (minEffort > maxminWeight[second]) continue;;
        if (second == end) break;

        for (auto edge: adjList.at(second))
        {
            int to = edge.to;
            int weight = edge.weight;

            int newMinEffort = std::max(minEffort, weight);

            if (newMinEffort < maxminWeight[to])
            {
                maxminWeight[to] = newMinEffort;
                parent[to] = second;
                priority_q.push({newMinEffort, to});
            }
        }
    }

    if (maxminWeight[end] == std::numeric_limits<int>::max()) return std::nullopt;

    std::vector<int> path;
    for (int a = end; a != -1; a = parent[a])
    {
        path.push_back(a);
    }

    std::reverse(path.begin(), path.end());
    return path;
}
int GeographicNetwork::findBestCity(int distanceThreshold) const
{
    if (adjList.empty()) return -1;
    if (distanceThreshold < 0) return -1;
    
    using P= std::pair<int, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> priority_q;
    std::vector<int> nodes;
    std::unordered_map<int, int> distance;

    for (auto pair : adjList)
    {
        nodes.push_back(pair.first);
    }

    std::sort(nodes.begin(), nodes.end());
    

    int best_city = -1;
    int minimumtoReach = INT_MAX;

    for (int start: nodes)
    {
        for (int n: nodes)
        {
            distance[n] = INT_MAX;
        }
        distance[start] = 0;
        priority_q.push({0, start});
        
        while (!priority_q.empty())
        {
            auto [d,first] = priority_q.top();
            priority_q.pop();
            
            for (auto edge: adjList.at(first))
            {
                int to = edge.to;
                int weight = edge.weight;

                if (distance[first] + weight < distance[to])
                {
                    distance[to] = distance[first] + weight;
                    priority_q.push({distance[to], to});
                }
            }
        }
        int count = 0;
        for (int node: nodes)
        {
            if (node != start && distance[node] <= distanceThreshold) count++;
        }

        if (count < minimumtoReach || (count == minimumtoReach && start > best_city))
        {
            minimumtoReach = count;
            best_city = start;
        }
    }
    return best_city;
}