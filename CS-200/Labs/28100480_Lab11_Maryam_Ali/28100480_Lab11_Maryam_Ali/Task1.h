#ifndef BROWSERSTACK_H
#define BROWSERSTACK_H

#include <iostream>
#include <string>

// Node Class - Represents a webpage
class Node {
public:
    std::string URL;  // Web page URL
    Node* next;

    Node(const std::string& URL) 
        : URL(URL), next(nullptr) {}
};

// LinkedList Class 
class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    void insertAtHead(const std::string& URL);

    void deleteAtHead();

    void display() const;

    int getSize() const;

    ~LinkedList();
};

// HistoryStack Class - Manages browser history stack using LinkedList
class BrowserStack {
private:
    LinkedList list;  // LinkedList instance to manage page history

public:
    BrowserStack() {}

    // Adds a new page to the history stack (insert at head) - mimics push operation of Stack
    void push(const std::string& URL);

    // Goes back to the previous page (removes the most recent page from the stack) - mimics pop operation of Stack
    void pop();

    // Shows the current page (top of the stack)
    std::string showCurrentPage() const;

    // Clears the entire history stack
    void clear();

    // Displays the history stack from the most recent page to the oldest
    void showHistory() const;
};

#endif 
