#include "../include/post_list.h"
#include <iostream>

PostList::~PostList() {
    PostNode *temp = head;
    while (temp){
        PostNode* next = temp->next;
        delete temp->post;
        delete(temp);
        temp = next;
    }
    head = nullptr;
}

void PostList::addPost(const Post& p) {
    Post* q = new Post(p);
    PostNode* newNode = new PostNode(q);
    if (!head) {head = newNode; return;}
    newNode->next = head;
    head = newNode;
}

bool PostList::removePost(int postID) {
    if (!head) return false;
    PostNode *to_delete = head;
    
    if (to_delete->post->postID == postID)
    {
        head = head->next;
        delete to_delete->post;
        delete to_delete;
        return true;
    }

    PostNode* prev = nullptr; 
    while (to_delete &&to_delete->post->postID != postID)
    {
        prev = to_delete;
        to_delete = to_delete->next;   
    }
    if (!to_delete) return false;

    prev->next = to_delete->next;
    delete to_delete->post;
    delete to_delete;
    return true;
}

Post* PostList::findPost(int postID) 
{
    if (!head) return nullptr;
    PostNode *temp = head;
    while (temp && temp->post->postID != postID)
    {
        temp = temp->next;
    }
    if (!temp) return nullptr;
    return temp->post;
}

void PostList::displayPosts() const {
    if (!head) return;
    PostNode *temp = head;
    while (temp)
    {
        cout << "Post No. " << temp->post->postID << " | " << temp->post->content << endl;
        temp = temp->next;
    }
}

bool PostList::isEmpty() const {
    if (!head) return true;
    return false;
}