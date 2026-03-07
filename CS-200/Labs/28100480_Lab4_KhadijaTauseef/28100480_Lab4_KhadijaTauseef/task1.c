#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int digit;
    struct Node* next;
} Node;

void addNode(Node* head, Node* to_add)
{
    if (head == NULL) 
    {
        head = to_add;
    }
    else
    {
        struct Node* temp = head;
        while (temp -> next != NULL)
        {
            temp = temp -> next;
        }
        temp -> next = to_add;
    }
}

Node* createListFromNumber(int num)
{
    int ans;
    int temp_num = num;
    int no_digits =0;
    struct Node *head;
    while (temp_num > 0)
    {
        ans = temp_num % 10;
        struct Node *p = (Node *)malloc (sizeof (struct Node));
        if (!p)
        {
            printf("Memory Allocation Failed \n");
        }
        p -> digit = ans;
        p -> next = NULL;
        if (no_digits == 0)
        {
            head = p;
        }
        else
        {
        addNode(head, p);
        }
        no_digits++;

        temp_num = temp_num / 10;
         
    }
    
}

void printNumAsList(Node* head)
{
    struct Node* temp = head;
    printf("Head -> ");
    while (temp != NULL)
    {
        printf("%d -> ", (*temp).digit);
        temp = temp -> next;
    }
    printf("NULL\n");
}

Node* reverseList(Node* head)
{

}

Node* addNumbers(Node* num1, Node* num2)
{

}


/* ------- DO NOT MODIFY BELOW ------- */

int testAddNode() {
    int marks = 0;
    // Create a list containing a single digit (3)
    Node* head = createListFromNumber(3);
    // Create a new single-node list containing digit (7)
    Node* singleNode = createListFromNumber(7);

    // addNode should append the singleNode to the end of head list.
    addNode(head, singleNode);
    
    // Check that the list now has two nodes: 3 then 7.
    if(head && head->digit == 3 &&
       head->next && head->next->digit == 7 &&
       head->next->next == NULL)
    {
        marks = 5;
    }
    
    if(marks == 5)
        printf("\033[0;32maddNode works: %d/5\033[0m\n", marks);
    else
        printf("\033[0;31maddNode works: %d/5\033[0m\n", marks);
    
    return marks;
}

int testCreateListFromNumber() {
    int marks = 0;
    int input = 14028;
    int expectedDigits[5] = {1, 4, 0, 2, 8};
    int valid = 1;
    int index = 0;
    Node* head = createListFromNumber(input);
    Node* curr = head;
    
    while (curr != NULL && index < 5) {
        if(curr->digit != expectedDigits[index]){
            valid = 0;
            break;
        }
        curr = curr->next;
        index++;
    }
    // There should be exactly 5 nodes.
    if(index != 5 || curr != NULL)
        valid = 0;
    
    if(valid)
        marks = 10;
    
    if(marks == 10)
        printf("\033[0;32mcreateListFromNumber works: %d/10\033[0m\n", marks);
    else
        printf("\033[0;31mcreateListFromNumber works: %d/10\033[0m\n", marks);
    
    return marks;
}

int testPrintNumAsList() {
    printf("\033[0;36mprintNumAsList() to be manually checked by TAs: ?/5\033[0m\n");
    Node* head = createListFromNumber(98765);
    printNumAsList(head);
    // Assume 0 marks based on manual check.
    return 0;
}

int testReverseList() {
    int marks = 0;
    // Create list for the number 123. Expected list: 1 -> 2 -> 3 -> NULL.
    Node* head = createListFromNumber(123);
    // Save pointers to individual nodes.
    Node* one = head;
    Node* two = head->next;
    Node* three = head->next->next;
    
    // reverseList should reverse the list in-place.
    reverseList(head);
    
    // Expected after reversal: three -> two -> one -> NULL.
    if (three->next == two &&
        two->next == one &&
        one->next == NULL)
    {
        marks = 7;
    }
    
    if(marks == 7)
        printf("\033[0;32mreverseList works: %d/7\033[0m\n", marks);
    else
        printf("\033[0;31mreverseList works: %d/7\033[0m\n", marks);
    
    return marks;
}

int testAddNumbers() {
    int marks = 0;
    int index = 0;
    Node* curr = NULL;
    
    // Test Case 1: 123 + 456 = 579
    Node* num1 = createListFromNumber(123);   // represents 1->2->3
    Node* num2 = createListFromNumber(456);     // represents 4->5->6
    Node* result = addNumbers(num1, num2);       // should represent 5->7->9
    
    int expected1[3] = {5, 7, 9};
    int valid1 = 1;
    curr = result;
    index = 0;
    while(curr != NULL && index < 3) {
        if(curr->digit != expected1[index]){
            valid1 = 0;
            break;
        }
        curr = curr->next;
        index++;
    }
    if(index != 3 || curr != NULL)
        valid1 = 0;
    
    if(valid1)
        marks += 3;
    
    // Test Case 2: 99 + 1 = 100
    num1 = createListFromNumber(99);   // represents 9->9
    num2 = createListFromNumber(1);      // single node 1
    result = addNumbers(num1, num2);     // should represent 1->0->0
    
    int expected2[3] = {1, 0, 0};
    int valid2 = 1;
    curr = result;
    index = 0;
    while(curr != NULL && index < 3) {
        if(curr->digit != expected2[index]) {
            valid2 = 0;
            break;
        }
        curr = curr->next;
        index++;
    }
    if(index != 3 || curr != NULL)
        valid2 = 0;
    
    if(valid2)
        marks += 5;
    
    // Test Case 3: 917 + 99 = 1016
    num1 = createListFromNumber(917);   // represents 9->1->7
    num2 = createListFromNumber(99);     // represents 9->9
    result = addNumbers(num1, num2);       // should represent 1->0->1->6
    
    int expected3[4] = {1, 0, 1, 6};
    int valid3 = 1;
    curr = result;
    index = 0;
    while(curr != NULL && index < 4) {
        if(curr->digit != expected3[index]) {
            valid3 = 0;
            break;
        }
        curr = curr->next;
        index++;
    }
    if(index != 4 || curr != NULL)
        valid3 = 0;
    
    if(valid3)
        marks += 5;
    
    if(marks == 13)
        printf("\033[0;32maddNumbers works: %d/13\033[0m\n", marks);
    else
        printf("\033[0;31maddNumbers works: %d/13\033[0m\n", marks);
    
    return marks;
}

int main() {
    printf("\033[1m\033[35mRunning Tests For Linked List...\033[0m\n");
    int total = 0;
    int max_marks = 5 + 10 + 7 + 13; // Marks for addNode, createListFromNumber, reverseList, addNumbers
    
    total += testAddNode();
    total += testCreateListFromNumber();
    total += testPrintNumAsList();
    total += testReverseList();
    total += testAddNumbers();
    
    if(total == max_marks)
        printf("\033[0;32mTotal Marks: %d/%d\033[0m\n", total, max_marks);
    else
        printf("\033[0;31mTotal Marks: %d/%d\033[0m\n", total, max_marks);
    
    return 0;
}