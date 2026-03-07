#include "../include/linked_list.h"
#include "../include/user.h"  // Add this so 'User' is complete
using namespace std;

template<typename T>
LinkedList<T>::LinkedList()  
{
    _head = NULL;
    _tail = NULL;
    _size = 0;

}

template<typename T>
LinkedList<T>::~LinkedList() 
{
    clear();    
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::push_back(const T& val) 
{
    Node *new_Node = new Node(val);
    if (!_tail){
        _head = _tail = new_Node;
        _size++;
        return _head;
    }
    _tail->next = new_Node;
    new_Node->prev = _tail;
    _tail = new_Node;
    _size++;
    return _tail;   
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::push_front(const T& val)
{
    Node *newNode = new Node(val);
    if (!_head){
        _head = _tail = newNode;
        _size++;
        return _head;
    }
    newNode->next = _head;
    _head->prev = newNode;
    _head = newNode;
    _size++;
    return _head;
    
}

template<typename T>
void LinkedList<T>::insert_after(Node* pos, const T& val) 
{
    if (!pos) return;
    Node * newNode = new Node(val);
    newNode->next = pos->next;
    newNode->prev = pos;
    if (pos->next)
    {
        pos->next->prev = newNode;
    }
    else _tail = newNode;
    pos->next = newNode;
    _size++;
}

template<typename T>
void LinkedList<T>::remove(Node* node) 
{
    if(!node) return;
    if (node == _head) _head = node->next;
    if (node == _tail) _tail = node->prev;
    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev; 
    delete node;
    --_size;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::find(function<bool(const T&)> pred) 
{
    Node *curr = _head;
    while (curr){
        if (pred(curr->data)) {
            return curr;
        }
        curr = curr->next;
    }
    return nullptr;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::head() const {
    return _head;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::tail() const {
    return _tail;
}

template<typename T>
size_t LinkedList<T>::size() const {
    return _size;
}

template<typename T>
void LinkedList<T>::clear() {
    
    while (_head){
        Node *temp = _head;
        _head = _head->next;
        temp->next = temp->prev = nullptr;
        delete temp;
    }
    _head = _tail = nullptr;
    _size =0;
}

// Explicit template instantiation for commonly used types
template class LinkedList<int>;
template class LinkedList<string>;

// Forward declare User struct for template instantiation
struct User;
template class LinkedList<User>;