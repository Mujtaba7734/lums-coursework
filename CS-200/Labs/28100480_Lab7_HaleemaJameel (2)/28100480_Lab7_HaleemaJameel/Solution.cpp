#include "Message.hpp"
#include "ChatGroup.hpp"

// Default constructor
Message::Message()
{
    name = "";
    size = 0;
    dateCreated = "";
    content = nullptr; 
}

// Parameterized constructor
Message::Message(string name, int size, string dateCreated, const char *content)
{
    this->name = name;
    this->size = size;
    this->dateCreated = dateCreated;
    this->content = new char [size + 1];
    strcpy(this->content, content);
}

// Copy constructor
Message::Message(Message &otherMessage)
{
    name = otherMessage.name;
    size = otherMessage.size;
    dateCreated = otherMessage.dateCreated;
    content = new char [size + 1];
    strcpy(content, otherMessage.content);
}

// Destructor
Message::~Message()
{
    delete [] content;
    content = nullptr;
}

// Getters
string Message::getName() const
{
    return name;
}

int Message::getSize() const
{
    return size;
}

string Message::getDateCreated() const
{
    return dateCreated;
}

char *Message::getContent() const
{
    return content;
}


// Edit the dynamic content
void Message::editMessageContent(const string newContent)
{
    if (content != NULL)
    {
        size = strlen(newContent.c_str()) + 1;
        delete []content; 
        content = new char [size];
        strcpy(content, newContent.c_str());
        content[size -1] = '\0';
    }
}

// Display message details
void Message::displayDetails() const
{
    cout << "Message Name: " << name << endl;
    cout << "Message Size: " << size << " Bytes" << endl;
    cout << "Date Created: " << dateCreated << endl;
    cout << "Message Content: " << content << endl;
}

// Default constructor
ChatGroup::ChatGroup()
{
    name = "";
    messages = nullptr;
    messageCount = 0;
    messageCapacity = 0;
    size = 0;
}

// Parameterized constructor
ChatGroup::ChatGroup(string name, Message **messages, int messageCount, int messageCapacity)
{
    this->name = name;
    this->messageCount = messageCount;
    this->messageCapacity = messageCapacity;
    size = 0;
    if (messageCount < messageCapacity)
    {
        this->messages = new Message * [messageCount];
        for (int i = 0; i < messageCount; i++)
        {
            this->messages[i] = new Message (*messages[i]);
            size += messages[i]->getSize();
        }
    }
}

// Copy constructor
ChatGroup::ChatGroup(ChatGroup &otherChatGroup)
{
    name = otherChatGroup.name;
    messageCount = otherChatGroup.messageCount;
    messageCapacity = otherChatGroup.messageCapacity;
    size = 0;
    if (messageCount < messageCapacity)
    {
        messages = new Message * [messageCount];
        for (int i = 0; i < messageCount; i++)
        {
            messages[i] = new Message (*otherChatGroup.messages[i]);
            size += messages[i]->getSize();
        }
    }
}

// Destructor
ChatGroup::~ChatGroup()
{
    for (int i = 0; i < messageCount; i++)
    {
        delete messages[i];
    }
    delete [] messages;
}

// Getters
string ChatGroup::getName()
{
    return name;
}

Message **ChatGroup::getMessages()
{
    return messages;
}

int ChatGroup::getMessageCount()
{
    return messageCount;
}

int ChatGroup::getMessageCapacity()
{
    return messageCapacity;
}

int ChatGroup::getSize()
{
    return size;
}

// Add a new message
void ChatGroup::addMessage(string messageName, int messageSize, string dateCreated, const char *content)
{
    if (searchMessage(messageName) != nullptr)
    {
        return;
    }

    if (messageCount >= messageCapacity)
    {
        resizeMessages();
    }
    messages[messageCount] = new Message(messageName, messageSize, dateCreated, content);
    
    size += messages[messageCount]->getSize();
    messageCount++;
}

// Delete an existing message
void ChatGroup::deleteMessage(string messageName)
{
    for (int i = 0; i < messageCount; i++)
    {
        if (messages[i]->getName() == messageName)
        {
            size -= messages[i]->getSize();
            delete messages[i];
            for (int j = i; j < messageCount; i++)
            {
                if (messages[j + 1]  != NULL)
                {
                    messages[j] = messages[j + 1];
                }
            }
            messageCount--;
            return;
        }
    }
}

// Increase the capacity of the messages array
void ChatGroup::resizeMessages()
{
    messageCapacity = messageCapacity * 2;
    Message **newmessages = new Message * [messageCapacity];
    for (int i = 0; i < messageCount; i++)
    {
        newmessages[i] = new Message (*messages[i]);
        delete messages[i];
    }
    delete [] messages;
    messages = newmessages;
}

// Search for a message by name
Message *ChatGroup::searchMessage(string messageName)
{
    for (int i = 0; i < messageCount; i++)
    {
        if (messages[i]->getName() == messageName)
        {
            return messages[i];
        }
    }
    return nullptr;

}

// Copy a message from this ChatGroup to another
void ChatGroup::copyMessageTo(string messageName, ChatGroup &destChatGroup)
{
    for (int i = 0; i < messageCount; i++)
    {
        if (messages[i]->getName() == messageName)
        {
            delete [] destChatGroup.messages[i];
            destChatGroup.messages[i] = new Message(messages[i]->getName(), messages[i]->getSize(), messages[i]->getDateCreated(), messages[i]->getContent());
        }
    }
}

// Move a message from this ChatGroup to another
void ChatGroup::moveMessageTo(string messageName, ChatGroup &destChatGroup)
{
    copyMessageTo(messageName, destChatGroup);
    deleteMessage(messageName);
}

// Sort the messages (1 for name, 2 for size, 3 for date)
void ChatGroup::sortMessages(int attribute)
{
    if (attribute == 1)
    {
        for (int i =0; i < messageCount; i++)
        {
            for (int j = i + 1; j < messageCount; j++)
            {
                if (messages[i]->getName() == messages[j]->getName())
                {
                    Message *temp = messages[i];
                    messages[i] = messages[j];
                    messages[j] = temp;
                }
            }
        }
    }

    if (attribute == 2)
    {
        for (int i =0; i < messageCount; i++)
        {
            for (int j = i + 1; j < messageCount; j++)
            {
                if (messages[i]->getSize() == messages[j]->getSize())
                {
                    Message *temp = messages[i];
                    messages[i] = messages[j];
                    messages[j] = temp;
                }
            }
        }
    }

    if (attribute == 3)
    {
        for (int i =0; i < messageCount; i++)
        {
            for (int j = i + 1; j < messageCount; j++)
            {
                if (messages[i]->getDateCreated() == messages[j]->getDateCreated())
                {
                    Message *temp = messages[i];
                    messages[i] = messages[j];
                    messages[j] = temp;
                }
            }
        }
    }
}

// Print the details of all messages in the ChatGroup
void ChatGroup::printChatGroupContent()
{
    for (int i = 0; i < messageCount; i++)
    {
        cout << "Message " << i + 1 << ":" << endl;
        messages[i]->displayDetails(); 
        cout << endl;
    }
}

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