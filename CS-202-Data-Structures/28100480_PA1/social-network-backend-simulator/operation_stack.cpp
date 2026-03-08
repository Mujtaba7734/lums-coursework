#include "../include/operation_stack.h"
#include <cstddef> // size_t
#include <iostream>
using namespace std;

UndoRedoManager::UndoRedoManager(UserManager& um, PostPool& pool): userManager(um), postPool(pool) {}
    

void UndoRedoManager::beginTransaction() {
   transactionMarkers.push(undoStack.size());
}

void UndoRedoManager::commitTransaction() {
    if (transactionMarkers.empty()) return;

    transactionMarkers.pop();

    for (void *obj: trashList)
    {
        if (!obj) continue;
        postPool.freePost(static_cast<Post *>(obj));
    }
    trashList.clear();
}

void UndoRedoManager::rollbackTransaction() {
    if (transactionMarkers.empty()) return;
    size_t marker = transactionMarkers.top();
    transactionMarkers.pop();

    while (undoStack.size() > marker)
    {
        OpFrame frame = undoStack.back();
        undoStack.pop_back();

        if (frame.type == OpType::DELETE_USER)
        {
            userManager.createUser(frame.userID, frame.snapshot_username_or_content);
        }
        if (frame.type == OpType::CREATE_USER)
        {
            userManager.deleteUser(frame.userID);
        }
        if (frame.type == OpType::CREATE_POST)
        {
            userManager.deletePost(frame.userID, frame.postID);
        }
        if (frame.type == OpType::DELETE_POST)
        {
            Post *p = postPool.allocPost();
            p->postID =frame.postID;

            size_t sep = frame.snapshot_username_or_content.find(':');
            p->category = frame.snapshot_username_or_content.substr(0, sep);
            string views = frame.snapshot_username_or_content.substr(sep + 1);
            p->views = stoi(views);

            userManager.addPost(frame.userID, p);
        }
        if (frame.type == OpType::FOLLOW)
        {
            userManager.unfollow(frame.userID, frame.postID);
        }
        if (frame.type == OpType::UNFOLLOW)
        {
            userManager.follow(frame.userID, frame.postID);
        }
    }

    for (void *obj: trashList)
    {
        if (!obj) continue;
        postPool.freePost(static_cast<Post *>(obj));
    }
    trashList.clear();
}

void UndoRedoManager::record(const OpFrame& f) {
    undoStack.push_back(f);
    redoStack.clear();
}

bool UndoRedoManager::undo() {
    if (undoStack.empty()) return false;
    
    OpFrame frame = undoStack.back();
    undoStack.pop_back();

    if (frame.type == OpType::DELETE_USER)
    {
        userManager.createUser(frame.userID, frame.snapshot_username_or_content);
    }
    else if (frame.type == OpType::CREATE_USER)
    {
        userManager.deleteUser(frame.userID);
    }
    else if (frame.type == OpType::CREATE_POST)
    {
        userManager.deletePost(frame.userID, frame.postID);
    }
    else if (frame.type == OpType::DELETE_POST)
    {
        Post *p = postPool.allocPost();
        if (!p) {
            redoStack.push_back(frame);
            return false;
        }

        p->postID =frame.postID;
        size_t sep = frame.snapshot_username_or_content.find(':');
        p->category = frame.snapshot_username_or_content.substr(0, sep);
        string views = frame.snapshot_username_or_content.substr(sep + 1);
        p->views = stoi(views);
        
        userManager.addPost(frame.userID, p);
    }
    else if (frame.type == OpType::FOLLOW)
    {
        userManager.unfollow(frame.userID, frame.postID);
    }
    else if (frame.type == OpType::UNFOLLOW)
    {
        userManager.follow(frame.userID, frame.postID);
    }
    else
    {
        redoStack.push_back(frame);
        return false;
    }
    
    redoStack.push_back(frame);
    return true;
}

bool UndoRedoManager::redo() {
    if (redoStack.empty()) return false;
    
    OpFrame frame = redoStack.back();
    redoStack.pop_back();

    if (frame.type == OpType::DELETE_USER)
    {
        userManager.deleteUser(frame.userID);
    }
    else if (frame.type == OpType::CREATE_USER)
    {
        userManager.createUser(frame.userID, frame.snapshot_username_or_content);
    }
    else if (frame.type == OpType::CREATE_POST)
    {
        Post *p = postPool.allocPost();
        p->postID =frame.postID;

        size_t sep = frame.snapshot_username_or_content.find(':');
        p->category = frame.snapshot_username_or_content.substr(0, sep);
        string views = frame.snapshot_username_or_content.substr(sep + 1);
        p->views = stoi(views);

        userManager.addPost(frame.userID, p);
    }
    else if (frame.type == OpType::DELETE_POST)
    {
        userManager.deletePost(frame.userID, frame.postID);
    }
    else if (frame.type == OpType::FOLLOW)
    {
        userManager.follow(frame.userID, frame.postID);
    }
    else if (frame.type == OpType::UNFOLLOW)
    {
        userManager.unfollow(frame.userID, frame.postID);
    }
    else {
        undoStack.push_back(frame);
        return false;
    }
    undoStack.push_back(frame);
    return true;
}
