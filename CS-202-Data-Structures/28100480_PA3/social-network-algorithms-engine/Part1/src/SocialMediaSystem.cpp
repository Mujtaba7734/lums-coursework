#include "SocialMediaSystem.h"

SocialMediaSystem::SocialMediaSystem()
    : feed(10)  // initial capacity
{}

int SocialMediaSystem::findPostIndex(int value) 
{
    if (value < 0) return -1;

    for (int i = 0; i < feed.size(); i++)
    {
        if (feed.elementAt(i) == value) return i;
    }
    return -1;
}

void SocialMediaSystem::buildUndiscoveredFeed(vector<int> likes) 
{
    if (likes.empty()) return;

    for (int val:likes)
    {
        feed.insertKey(val);
    }
}

void SocialMediaSystem::updatePostLikes(int oldLikes, int newLikes) 
{
    if (oldLikes < 0) return;
    if (newLikes < 0) return;

    int index = findPostIndex(oldLikes);
    if (index != -1)
    {
        if (newLikes > oldLikes)
        {
            feed.increaseKey(index, newLikes);
        }
        else if (newLikes < oldLikes)
        {
            feed.decreaseKey(index, newLikes);
        }
    }
}

void SocialMediaSystem::clearLowEngagementPosts(int threshold) 
{
    if (threshold < 0) return;

    while (feed.size() > 0 && feed.getMin() < threshold)
    {
        feed.extractMin();
    }   
}

vector<int> SocialMediaSystem::getTopNPosts(int N) 
{
    if (N <= 0) return {};

    vector<int> topItems;
    
    MinHeap temp = feed;

    int count = 0;
    while (temp.size() > 0 && count < N)
    {
        topItems.push_back(temp.extractMin());
        count++;
    }
    
    return topItems;
}

void SocialMediaSystem::decreasePostLikes(int currentLikes, int newLikes) 
{
    if (currentLikes < 0) return;
    if (newLikes < 0) return;
    int index = findPostIndex(currentLikes);
    if (index != -1) feed.decreaseKey(index, newLikes);   
}
