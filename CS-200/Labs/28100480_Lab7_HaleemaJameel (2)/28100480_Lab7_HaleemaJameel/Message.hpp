#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

class Message
{
private:
    string name;
    int size;           // in Bytes
    string dateCreated; // in form YYYY-MM-DD
    char *content;      // Dynamically allocated character array

public:
    Message();
    Message(string name, int size, string dateCreated, const char *content);
    Message(Message &otherMessage);
    ~Message();

    string getName() const;
    int getSize() const;
    string getDateCreated() const;
    char *getContent() const;

    void editMessageContent(const string newContent);
    void displayDetails() const;
};

#endif
