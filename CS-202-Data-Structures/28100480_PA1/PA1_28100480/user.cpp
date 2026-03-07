#include "../include/user.h"
#include "../include/follow_list.h"
#include <iostream>
using namespace std;

User::User(int id, const string& name): userID(id), userName(name), posts(), following(new FollowList){}

// Copy constructor
User::User(const User& other)  
{
    this->userID = other.userID;
    this->userName = other.userName;

    this->posts = PostList();
    PostNode *current = other.posts.head;
    while (current){
        this->posts.addPost(*current->post);
        current = current->next;
    }
    
    this->following = new FollowList;
    // Don't copy the following relationships - they should be rebuilt separately
    // This prevents circular dependency issues and dangling pointers
}

// Copy assignment operator
User& User::operator=(const User& other) {
    if (this == &other) return *this;

    this->userID = other.userID;
    this->userName = other.userName;

    this->posts = PostList();
    PostNode *current = other.posts.head;
    while (current){
        this->posts.addPost(*current->post);
        current = current->next;
    }

    delete this->following;
    this->following = new FollowList;
    FollowNode *otheruser = other.following->head;
    while (otheruser)
    {
        this->following->addFollowing(otheruser->user);
        otheruser = otheruser->next;
    }
    
    return *this;
}

// Move constructor
User::User(User&& other) noexcept {
    this->userID = other.userID;
    other.userID = 0;
    this->userName = other.userName;
    other.userName = "";

    this->posts = PostList();
    PostNode *current = other.posts.head;
    while (current){
        this->posts.addPost(*current->post);
        current = current->next;
    }
    other.posts = PostList();

    this->following = other.following;
    other.following = nullptr;

}

// Move assignment operator
User& User::operator=(User&& other) noexcept {
    if (this == &other) return *this;

    this->userID = other.userID;
    other.userID = 0;
    this->userName = other.userName;
    other.userName = "";
    
    this->posts = PostList();
    PostNode *current = other.posts.head;
    while (current){
        this->posts.addPost(*current->post);
        current = current->next;
    }
    other.posts = PostList();

    delete this->following;
    this->following = nullptr;

    this->following = other.following;
    other.following = nullptr;

    return *this;
}

User::~User() {
    this->userID = 0;
    this->userName = "";
    delete following;
    following = nullptr;
}

void User::addPost(int postID, const string& category) {
    this->posts.addPost(Post(postID, category));
}

void User::followUser(User* otherUser) {
    if (this->userID == otherUser->userID) return;
    this->following->addFollowing(otherUser);
}

void User::displayFollowing() const {
    this->following->displayFollowing();
}