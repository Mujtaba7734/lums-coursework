#include "../include/social_graph.h"
#include <queue>
#include <algorithm>
#include <utility>
#include <vector>
#include <stack>

SocialGraph::SocialGraph() = default;

SocialGraph::SocialGraph(SocialGraph &&other) noexcept
    : adjList(std::move(other.adjList))
{}

SocialGraph &SocialGraph::operator=(SocialGraph &&other) noexcept
{
    if (this != &other)
    {
        this->adjList = std::move(other.adjList);
    }
    return *this;   
}

// --- Vertex Management ---

void SocialGraph::addVertex(int node)
{
    if (node < 0) return;

    if (adjList.find(node) == adjList.end()) adjList[node] = std::vector<int>();
}

void SocialGraph::removeVertex(int node)
{
    if (node < 0) return;
    if (adjList.find(node) == adjList.end()) return;

    adjList.erase(node);

    for (auto &pair : adjList)
    {
        auto &edge = pair.second;
        edge.erase(std::remove(edge.begin(), edge.end(), node), edge.end());
    }
}

// --- Edge Management ---

void SocialGraph::addEdge(int from, int to, int /*weight*/)
{
    if (from < 0) return;
    if (to < 0) return;
    if (from == to) return;
    if (adjList.find(from) == adjList.end()) return;
    if (adjList.find(to) == adjList.end()) return;
    
    for (int parosi : adjList[from])
    {
        if (parosi == to) return;
    }
    adjList[from].push_back(to);
}

void SocialGraph::removeEdge(int from, int to)
{
    if (from < 0) return;
    if (to < 0) return;
    if (adjList.find(from) == adjList.end()) return;

    auto &edge = adjList[from];
    edge.erase(std::remove(edge.begin(), edge.end(), to), edge.end());
}

// --- Graph Queries ---

bool SocialGraph::hasEdge(int from, int to) const
{
    if (from < 0) return false;
    if (to < 0) return false;
    if (adjList.find(from) == adjList.end()) return false;

    auto edge = adjList.at(from);
    for (int parosi: edge)
    {
        if (parosi == to) return true;
    } 
    return false;
}

std::vector<int> SocialGraph::getAdjacent(int from) const
{
    if (from < 0) return {};
    if (adjList.find(from) == adjList.end()) return {};

    return adjList.at(from);
}

std::optional<std::vector<int>> SocialGraph::findShortestPath(int start, int end) const
{
    if (start < 0) return std::nullopt;
    if (end < 0) return std::nullopt;
    if (adjList.find(start) == adjList.end()) return std::nullopt;
    if (adjList.find(end) == adjList.end()) return std::nullopt;

    if (start == end) return std::vector<int>{start};

    std::queue<int> q;
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> visited;
    std::vector<int> path;

    q.push(start);
    visited[start] = true;
    parent[start] = -1;

    bool found = false;

    while (!q.empty())
    {
        int element = q.front();
        q.pop();

        if (element == end)
        {
            found = true;
            break;
        }
        for (int parosi: adjList.at(element))
        {
            if (!visited[parosi])
            {
                visited[parosi] = true;
                parent[parosi] = element;
                q.push(parosi);
            }
        }
    }

    if (!found) return std:: nullopt;

    
    int last = end;
    while (last != -1)
    {
        path.push_back(last);
        last = parent[last];
    } 
    std::reverse(path.begin(), path.end());
    return path;
}

// --- Advanced Analysis Functions ---

std::vector<std::pair<int, int>> SocialGraph::findEchoChambers() const
{
    if (adjList.empty()) return {};
    
    std::vector<std::pair<int, int>> chamber;

    for (auto pair:adjList)
    {
        int u = pair.first;
        for (int v: pair.second)
        {
            if (u < v)
            {
                if (hasEdge(v,u)) chamber.push_back({u,v});
            }
        }
    }
    
    return chamber;
}

std::unordered_map<int, double> SocialGraph::calculatePageRank(double damping, int iterations) const
{
    if (damping < 0) return {};
    if (iterations < 0) return {};

    std::unordered_map<int, double> rank;
    std::unordered_map<int, int> outDegree;
    std::unordered_map<int, double> newRank;

    int N = adjList.size();
    if (N == 0) return rank;

    double initialRank = 1.0/ N;
    for (auto pair:adjList)
    {
        rank[pair.first] = initialRank;
    }

    
    for (auto pair: adjList)
    {
        outDegree[pair.first] = pair.second.size();
    }

    for (int i = 0; i < iterations; i++ )
    {
        
        double sinkRank = 0.0;

        for (auto pair: rank)
        {
            int first = pair.first;
            if (outDegree[first] == 0) sinkRank += rank[first];
        }

        double basescore = (1.0 - damping) / N;
        double sink = (damping * sinkRank) / N;

        for (auto pair: adjList)
        {
            int first = pair.first;
            double incSum = 0.0;

            for (auto other: adjList)
            {
                int first_2 = other.first;
                auto edge = other.second;
                bool points2u = false;

                for (int parosi: edge)
                {
                    if (parosi == first)
                    {
                        points2u = true;
                        break;
                    }
                }

                if (points2u) incSum += rank[first_2] / outDegree[first_2];
            }
            newRank[first] = basescore + sink + (damping * incSum);
        }
        rank = newRank;
    }
    return rank;
}

std::vector<std::vector<int>> SocialGraph::findCommunities() const
{
    if (adjList.empty()) return {};
    
    std::vector<std::vector<int>> community;
    std::unordered_map<int, bool> visited;
    std::vector<int> stack_finish;
    std::unordered_map<int, std::vector<int>> transpose;
    std::vector<int> component;

    for (auto pair: adjList) 
    {
        visited[pair.first] = false;
    }

    for (auto pair: adjList)
    {
        if (!visited[pair.first])
        {
            kosaraju_dfs1(pair.first, visited, stack_finish);
        }
    }

    for (auto pair: adjList)
    {
        int first = pair.first;
        if (transpose.find(first) == transpose.end()) transpose[first] = {};

        for (int second: pair.second)
        {
            transpose[second].push_back(first);
            if (transpose.find(first) == transpose.end()) transpose[first] = {};
        }
    }

    visited.clear();
    for (auto pair: adjList)
    {
        visited[pair.first] = false;
    }

    while (!stack_finish.empty())
    {
        int first = stack_finish.back();
        stack_finish.pop_back();

        if (!visited[first])
        {
            component.clear();
            kosaraju_dfs2(first, visited, component, transpose);
            community.push_back(component);
        }
    }

    return community;
}

void SocialGraph::kosaraju_dfs1(int u, std::unordered_map<int, bool> &visited, std::vector<int> &finish_stack) const
{

    visited[u] = true;
    if (adjList.find(u) == adjList.end()) return;

    for (int first : adjList.at(u))
    {
        if (!visited[first]) kosaraju_dfs1(first, visited, finish_stack);
    }
    
    finish_stack.push_back(u);
}

void SocialGraph::kosaraju_dfs2(int u, std::unordered_map<int, bool> &visited, std::vector<int> &component, const std::unordered_map<int, std::vector<int>> &transposed_graph) const
{

    visited[u] = true;
    component.push_back(u);

    if (transposed_graph.find(u) == transposed_graph.end()) return;
    
    for (int first : transposed_graph.at(u))
    {
        if (!visited[first]) kosaraju_dfs2(first, visited, component, transposed_graph);
    }
}