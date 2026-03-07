#ifndef CHATGROUP_HPP
#define CHATGROUP_HPP
#include <iostream>
#include <string>
#include "Message.hpp"

using namespace std;

class ChatGroup
{
private:
    string name;
    Message **messages; // Dynamically allocated array of pointers
    int messageCount;
    int messageCapacity;
    int size; // total size in Bytes

public:
    ChatGroup();
    ChatGroup(string name, Message **messages, int messageCount, int messageCapacity);
    ChatGroup(ChatGroup &otherChatGroup);
    ~ChatGroup();

    string getName();
    Message **getMessages();
    int getMessageCount();
    int getMessageCapacity();
    int getSize();

    void addMessage(string messageName, int messageSize, string dateCreated, const char *content);
    void deleteMessage(string messageName);
    void resizeMessages();
    Message *searchMessage(string messageName);
    void copyMessageTo(string messageName, ChatGroup &destChatGroup);
    void moveMessageTo(string messageName, ChatGroup &destChatGroup);
    void sortMessages(int attribute); // 1 for name, 2 for size, 3 for date
    void printChatGroupContent();
};

/* Example Format:
Contents of ChatGroupName

Message 1:
Message Name: ...
Message Size: ... Bytes
Date Created: ...
Message Content: ...

Message 2:
Message Name: ...
Message Size: ... Bytes
Date Created: ...
Message Content: ...
*/

#endif
