#include "../include/interaction_graph.h"
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <queue>

InteractionGraph::InteractionGraph() = default;

InteractionGraph::InteractionGraph(InteractionGraph &&other) noexcept
    : userToPostEdges(std::move(other.userToPostEdges)),
      postToUserEdges(std::move(other.postToUserEdges)) {}

InteractionGraph &InteractionGraph::operator=(InteractionGraph &&other) noexcept
{
    if (this != &other)
    {
        userToPostEdges = std::move(other.userToPostEdges);
        postToUserEdges = std::move(other.postToUserEdges);
    }
    return *this;
}

// --- Graph Management ---

void InteractionGraph::addVertex(int id, NodeType type)
{
    if (id < 0) return;

    if (type == NodeType::USER)
    {
        if (userToPostEdges.find(id) == userToPostEdges.end()) userToPostEdges[id] = {};
    }
    else
    {
        if (postToUserEdges.find(id) == postToUserEdges.end()) postToUserEdges[id] = {};
    }
}

void InteractionGraph::removeVertex(int id, NodeType type)
{
    if (id < 0) return;

    if (type == NodeType::USER)
    {
        if (userToPostEdges.find(id) == userToPostEdges.end()) return;

        auto interaction = userToPostEdges[id];

        for (auto tointeract : interaction)
        {
            int postID = tointeract.targetID;
            if (postToUserEdges.find(postID) != postToUserEdges.end())
            {
                auto &userlist = postToUserEdges[postID];
                int i = 0;
                while (i< userlist.size())
                {
                    if(userlist[i].targetID == id) userlist.erase(userlist.begin() + i);
                    else i++;
                }
            }
        }
        userToPostEdges.erase(id);
    }
    else
    {
        if (postToUserEdges.find(id) == postToUserEdges.end()) return;
        
        auto interation = userToPostEdges[id];
        for (auto tointeract : interation)
        {
            int userID = tointeract.targetID;
            if (userToPostEdges.find(userID) != userToPostEdges.end())
            {
                auto &postList = userToPostEdges[userID];
                int i = 0;
                while (i < postList.size())
                {
                    if (postList[i].targetID == id) postList.erase(postList.begin() + i);
                    else i++;
                }
            }
        }
        postToUserEdges.erase(id);
    }
}

void InteractionGraph::addInteraction(int userID, int postID, int weight)
{
    if (userID < 0) return;
    if  (postID < 0) return;
    if (userToPostEdges.find(userID) == userToPostEdges.end()) return;
    if (postToUserEdges.find(postID) == postToUserEdges.end()) return;

    auto &userEdge = userToPostEdges[userID];
    int i = 0;
    while (i < userEdge.size())
    {
        if (userEdge[i].targetID == postID) userEdge.erase(userEdge.begin() + i);
        else i++;
    }

    auto &postEdge = postToUserEdges[postID];
    int j = 0;
    while (j < postEdge.size())
    {
        if (postEdge[j].targetID == userID) postEdge.erase(postEdge.begin() + j);
        else j++;
    }

    userToPostEdges[userID].push_back({postID, weight});
    postToUserEdges[postID].push_back({userID, weight});

}

// --- Advanced Analysis Functions ---

// -- Helper Sort function

bool sortSimilarity(std::pair<int, double> &a, std::pair<int, double> &b)
{
    if (std::abs(a.second - b.second) > 1e-9) return a.second > b.second;
    return a.first < b.first;
}

std::vector<std::pair<int, double>> InteractionGraph::findSimilarUsers(int userID, int topN) const
{
    //  TODO: Jaccard Similarity

    if (userID < 0) return {};
    if (topN <= 0) return {};
    if (userToPostEdges.find(userID) == userToPostEdges.end()) return {};

    std::vector<int> post2target;
    std::vector<int> post_other;
    std::vector<std::pair<int, double>> anysimilarity;

    for (auto iterate : userToPostEdges.at(userID))
    {
        post2target.push_back(iterate.targetID);
    }

    if (post2target.empty()) return {};

    std::sort(post2target.begin(), post2target.end());
    post2target.erase(std::unique(post2target.begin(), post2target.end()), post2target.end());

    for (auto edge: userToPostEdges)
    {
        post_other.clear();

        int otherID = edge.first;
        if (otherID == userID) continue;

        for (auto iterate : edge.second)
        {
            post_other.push_back(iterate.targetID);
        }

        if (post_other.empty()) continue;
        
        std::sort(post_other.begin(), post_other.end());
        post_other.erase(std::unique(post_other.begin(), post_other.end()), post_other.end());

        int i = 0;
        int j = 0;
        int count_intersection = 0;
        int count_union = 0;

        while (i < post2target.size() && j < post_other.size())
        {
            if (post2target[i] == post_other[j])
            {
                count_intersection++;
                count_union++;
                i++;
                j++;
            }
            else if (post2target[i] < post_other[j])
            {
                count_union++;
                i++;
            }
            else
            {
                count_union++;
                j++;
            }
        }

        count_union += (post2target.size() - i);
        count_union += (post_other.size() - j);

        if (count_union == 0) continue;

        double jaccard_algo = double(count_intersection) / double(count_union);

        if (jaccard_algo > 0.0) anysimilarity.push_back({otherID, jaccard_algo});
    }

    std::sort(anysimilarity.begin(), anysimilarity.end(), sortSimilarity);

    if (topN < anysimilarity.size()) anysimilarity.resize(topN);

    return anysimilarity;
}

std::vector<int> InteractionGraph::recommendPosts(int userID, int topN) const
{
    if (userID < 0) return {};
    if (topN < 0) return {};
    if (userToPostEdges.find(userID) == userToPostEdges.end()) return {};

    int total = 5;
    auto similarUsers = findSimilarUsers(userID, total);

    if (similarUsers.empty()) return {};

    std::unordered_set<int> posts_seen_User;
    std::unordered_map<int, double> score_post;
    std::vector<std::pair<int,double>> suitable_candidates;
    std::vector<int> recommend2Users;

    for (auto interact: userToPostEdges.at(userID))
    {
        posts_seen_User.insert(interact.targetID);
    }

    for (auto userSimilar : similarUsers)
    {
        int otherID = userSimilar.first;
        double similarity_score = userSimilar.second;

        for (auto interact: userToPostEdges.at(otherID))
        {
            int postID = interact.targetID;

            if (posts_seen_User.find(postID) != posts_seen_User.end()) continue;

            score_post[postID] += similarity_score;
        }
    }

    for (auto & pair: score_post)
    {
        suitable_candidates.push_back(pair);
    }

    std::sort(suitable_candidates.begin(), suitable_candidates.end(), sortSimilarity);

    int min = std::min((int)suitable_candidates.size(), topN);

    for (int i = 0; i < min; i++)
    {
        recommend2Users.push_back(suitable_candidates[i].first);
    }
    
    return recommend2Users;
}

std::unordered_map<int, double> InteractionGraph::calculateTrendScores(const std::unordered_map<int, double> &pageRanks) const
{

    std::unordered_map<int, double> trendScore;

    for (auto pair: postToUserEdges)
    {
        int postID = pair.first;
        auto interactionss = pair.second;

        double score = 0.0;

        for (auto interact2: interactionss)
        {
            int userID = interact2.targetID;
            int weight = interact2.weight;

            double userRank = 0.0;

            if (pageRanks.find(userID) != pageRanks.end()) userRank = pageRanks.at(userID);

            score += (userRank * weight);
        }

        trendScore[postID] = score;
    }

    return trendScore;
}

std::optional<std::vector<int>> InteractionGraph::getProcessingOrder() const
{
    // TODO: Kahn's algorithm for topological sorting.

    std::unordered_map<int, int> inDegree;
    std::vector<int> result;

    for (auto pair : userToPostEdges)
    {
        inDegree[pair.first] = 0;
    }

    for (auto pair: userToPostEdges)
    {
        for (auto edge: pair.second)
        {
            inDegree[edge.targetID]++;
        }
    }

    std::queue<int> queue;

    for (auto pair: userToPostEdges)
    {
        queue.push(pair.first);
    }

    for (auto pair: postToUserEdges)
    {
        if (inDegree[pair.first] ==0)
        {
            queue.push(pair.first);
        }
    }

    while (!queue.empty())
    {
        int user  = queue.front();
        queue.pop();
        result.push_back(user);

        if (userToPostEdges.find(user) != userToPostEdges.end())
        {
            for (auto interact2 : userToPostEdges.at(user))
            {
                int post = interact2.targetID;
                if (inDegree.find(post) != inDegree.end())
                {
                    inDegree[post]--;
                    if (inDegree[post] == 0)
                    {
                        queue.push(post);
                    }
                }
            }
        }
    }
    
    int totalNodes = userToPostEdges.size() + postToUserEdges.size();

    if (result.size() != totalNodes) return std::nullopt;
    return result;
}