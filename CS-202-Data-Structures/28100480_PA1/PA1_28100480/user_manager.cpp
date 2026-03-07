#include "../include/user_manager.h"
#include "../include/user.h"
#include "../include/follow_list.h"
#include "../include/post_pool.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

UserManager::UserManager(): users() {}

UserManager::~UserManager() {users.clear();}

LinkedList<User>::Node* UserManager::createUser(int userID, const string& username) {

    if (findUserByID(userID)) return nullptr;
    if (findUserByName(username)) return nullptr;
    User newUser(userID, username);
    return users.push_back(newUser);
}

bool UserManager::deleteUser(int userID) {
    auto findNode = findUserByID(userID);
    if (!findNode) return false;

    LinkedList<User>::Node *temp = users.head();
    if (!temp) return false;

    while (temp)
    {
        if (temp->data.following) temp->data.following->removeFollowing(userID);
        temp = temp->next;
    }

    users.remove(findNode);
    return true;
}

bool UserManager::follow(int followerID, int followeeID) 
{
    if (followerID == followeeID) return false;

    auto followerNode = findUserByID(followerID);
    auto followeeNode = findUserByID(followeeID);

    if (!followeeNode) return false;
    if (!followerNode) return false;
    
    if(followerNode->data.following->findFollowing(followeeID)) return false;
    
    followerNode->data.following->addFollowing(&followeeNode->data);
    return true;
}

bool UserManager::unfollow(int followerID, int followeeID) {

    if (followerID == followeeID) return false;

    auto followerNode = findUserByID(followerID);
    auto followeeNode = findUserByID(followeeID);

    if (!followeeNode) return false;
    if (!followerNode) return false;
    
    if (!followerNode->data.following->findFollowing(followeeID)) return false;

    followerNode->data.following->removeFollowing(followeeID);
    return true;
}

bool UserManager::isFollowing(int followerID, int followeeID) const {
    if (followerID == followeeID) return false;
    if (!const_cast<UserManager*>(this)->findUserByID(followerID)) return false;
    if (!const_cast<UserManager*>(this)->findUserByID(followeeID)) return false;

    LinkedList<User>::Node *to_find = const_cast<UserManager*>(this)->findUserByID(followerID); 
    if (!to_find->data.following->findFollowing(followeeID)) return false;
    return true;
}

bool UserManager::addPost(int userID, Post* post) {

    auto *to_find = findUserByID(userID);
    if (!to_find) return false;
    if (!post) return false;
    
    to_find->data.posts.addPost(*post);
    
    return true;
}

bool UserManager::deletePost(int userID, PostID postID) {
    if (!findUserByID(userID)) return false;
    LinkedList<User>::Node *to_find = findUserByID(userID);
    if (to_find->data.posts.removePost(postID)) return true;
    return false;
}

LinkedList<User>::Node* UserManager::findUserByID(int userID) 
{
    auto foundNode = users.find([&](const User &u) {
        return u.userID == userID;
    });

    return foundNode;
}

LinkedList<User>::Node* UserManager::findUserByName(const string& username) 
{
    auto foundNode = users.find([&](const User &u) {
        return u.userName == username;
    });

    return foundNode;
}

void UserManager::exportUsersCSV(const string& path) const {
    ofstream out(path);
    if (!out.is_open()) { cerr << "Error opening " << path << "\n"; return; }

    for (auto node = users.head(); node; node = node->next) {
        const User &u = node->data;
        ostringstream line;
        line << u.userID << "," << u.userName << ",";

        // followee IDs only
        if (u.following) {
            auto f = u.following->head;
            while (f) {
                line << f->user->userID;
                if (f->next) line << "|";
                f = f->next;
            }
        }
        line << ",";

        // posts
        if (u.posts.head) {
            auto p = u.posts.head;
            while (p) {
                line << p->post->postID << ":" << p->post->category << ":" << p->post->views;
                if (p->next) line << "|";
                p = p->next;
            }
        }

        out << line.str() << "\n";
    }

    out.close();
}

void UserManager::importUsersCSV(const string& path) 
{
    users.clear();
    ifstream in(path);
    if (!in.is_open()) {
        cout << "Error: Cant open file for reading" << endl;
        return;
    }   

    string line;

    while (getline(in, line)) {
        stringstream ss(line);
        string userIDstr, username, followeeStr, postStr;

        getline(ss, userIDstr, ',');
        getline(ss, username, ',');
        getline(ss, followeeStr, ',');
        getline(ss, postStr);

        int userID = stoi(userIDstr);
        auto userNode = createUser(userID, username);

        if (!postStr.empty()) {
            stringstream pss(postStr);
            string postEntry;

            while(getline(pss, postEntry, '|')){
                stringstream postSS(postEntry);
                string postIDstr, category, viewstr;

                getline(postSS, postIDstr, ':');
                getline(postSS, category, ':');
                getline(postSS, viewstr, ':');

                int postID = stoi(postIDstr);
                int view = stoi(viewstr);

                Post* post = new Post(postID, category, view);
                addPost(userID, post);
            }   
        }
    }
    in.close();

    in.open(path);
    if (!in.is_open()) {
        cout << "Error: Cant reopen file for reading" << endl;
        return;
    }
    
    while (getline(in, line)) {
        stringstream ss(line);
        string userIDstr, username, followeeStr, postStr;

        getline(ss, userIDstr, ',');
        getline(ss, username, ',');
        getline(ss, followeeStr, ',');
        getline(ss, postStr);

        int userID = stoi(userIDstr);

        if (!followeeStr.empty()) {
            stringstream fss(followeeStr);
            string followeeIDstr;
            while (getline(fss, followeeIDstr, '|')) 
            {
                int followeeID = stoi(followeeIDstr);
                follow(userID, followeeID);
            }
        }
    }
    in.close();

    cout << "Data restored successfully!" << endl;
}

void UserManager::dumpAllUsers(ostream& out) const {
    auto node = users.head();
    while (node) {
        out << "UserID: " << node->data.userID << " | Username: " << node->data.userName << "\n";

        out << "Following: ";
        if (node->data.following)
        {
            auto fNode = node->data.following->head;
            while (fNode) {
                out << fNode->user->userID;
                if (fNode->next) out << ", ";
                fNode = fNode->next;
            }
        }
        out << "\n";

        out << "Posts: ";
        auto pNode = node->data.posts.head;
        while (pNode) {
            out << "[" << pNode->post->postID 
                << ":" << pNode->post->category 
                << ":" << pNode->post->views << "]";
            if (pNode->next) out << ", ";
            pNode = pNode->next;
        }
        out << "\n";

        node = node->next;
    }
}