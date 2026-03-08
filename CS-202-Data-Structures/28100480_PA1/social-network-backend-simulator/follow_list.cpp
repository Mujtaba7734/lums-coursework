#include "../include/follow_list.h"
#include "../include/user.h"
#include <iostream>
using namespace std;

FollowList::~FollowList() {
    while (head){
        FollowNode *temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
}

void FollowList::addFollowing(User* u) {
    if (!u) return;
    FollowNode* newNode = new FollowNode(u);
    if (!head) {head = newNode; return;} 
    FollowNode *temp = head;
    while (temp)
    {
        if (temp->user->userID == u->userID) {delete newNode; return;}
        temp= temp->next;
    }
   
    newNode->next = head;
    head = newNode;
}

bool FollowList::removeFollowing(int userID) {
    if (!head) return false;

    FollowNode *to_delete = head;
    
    if (to_delete->user->userID == userID)
    {
        head = head->next;

        delete to_delete;
        return true;
    }

    FollowNode *prev = nullptr;
    while (to_delete &&to_delete->user->userID != userID)
    {
        prev = to_delete;
        to_delete = to_delete->next;   
    }
    if (!to_delete) return false;
    
    prev->next = to_delete->next;
    delete to_delete;
    return true;
}

User* FollowList::findFollowing(int userID) {
    if (!head) return nullptr;
    FollowNode *temp = head;
    while (temp && temp->user->userID != userID)
    {
        temp = temp->next;
    }
    if (!temp) return nullptr;
    return temp->user;
}

void FollowList::displayFollowing() const 
{
    if (!head) return;
    FollowNode *temp = head;
    while (temp)
    {
        cout << "User ID. " << temp->user->userID << " | " << temp->user->userName << endl;
        temp = temp->next;
    }
}