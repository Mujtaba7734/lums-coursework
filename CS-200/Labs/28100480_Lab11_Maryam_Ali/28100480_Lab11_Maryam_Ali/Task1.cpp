#include "Task1.h"

// LinkedList Methods
void LinkedList::insertAtHead(const std::string& URL) 
{
    Node* newNode = new Node(URL);
    Node *temp = this->head;
    this->head = newNode;
    this->head->next = temp;
}

void LinkedList::deleteAtHead()
{
    if (this->head == NULL)
    {
        return;
    }
    Node *temp = this->head->next;
    delete this->head;
    this->head = temp;
}

void LinkedList::display() const {
    Node* current = head;
    if (!current) {
        std::cout << "No history yet." << std::endl;
        return;
    }
    std::cout << "History:" << std::endl;
    while (current) {
        std::cout << "- " << current->URL << std::endl;
        current = current->next;
    }
}

int LinkedList::getSize() const {
    int count = 0;
    Node* current = head;
    while (current) {
        count++;
        current = current->next;
    }
    return count;
}

// Destructor for LinkedList
LinkedList::~LinkedList() 
{
    while (head != nullptr)
    {
        deleteAtHead();
    }
}

// BrowserStack Methods
void BrowserStack::push(const std::string& URL) 
{
    list.insertAtHead(URL);
}

void BrowserStack::pop() 
{
    list.deleteAtHead();
}

std::string BrowserStack::showCurrentPage() const 
{
    if (list.getSize() == 0)
    {
        return "No page is currently loaded.";
    }
    return "Currently Viewing: " + this->list.head->URL;
}

void BrowserStack::clear() 
{
    list.~LinkedList();
}

void BrowserStack::showHistory() const 
{
    list.display();
}
