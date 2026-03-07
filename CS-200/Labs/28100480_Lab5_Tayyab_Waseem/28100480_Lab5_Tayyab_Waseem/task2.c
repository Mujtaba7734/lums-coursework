#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define the Node structure
typedef struct Node
{
    int value;
    struct Node *next;
} Node;

// Function to create a node
Node *createNode(int val)
{
    struct Node *nem_node = (struct Node*) malloc (sizeof(struct Node));
    nem_node->value = val;
    nem_node->next = NULL;
    
    return nem_node;
}

// Function to print the linked list
void printList(Node *head)
{
    struct Node *temp = head;
    while (temp-> next != NULL)
    {
        printf("%d -> ", temp->value);
        temp = temp->next;
    }
    printf("NULL");
}


// Helper function
bool isPalindromeHelper(Node **left, Node *right)
{
    if (left == NULL || right == NULL)
    {
        return true;
    } 
    if (right->next == NULL)
    {
        return true;
    }
    isPalindromeHelper(left, right ->next);
    if ((*left)-> value == right->value)
    {
        left = &(*left)->next;
    }
    else
    {
        return false;
    }
}
    // struct Node *head = right;
    // int i =0;
    // while (head != ((*left)))
    // {
    //     i++;
    // }
    // int count = 0;
    // while (right->next ==  NULL)
    // {

    // }
    // while (right->next ==  NULL && count != i)
    // {
    //     right = right->next;
    //     count++;
    // }

    // if ((*left) == right)
    // {
    //     *left = (*left)->next; 
    //     return isPalindromeHelper(left, head); 
    // }
    // else 
    // {
    //     return false;
    // }
    // You can view the below ispalindrome function to see which parameters you are getting here






// ------------------------------- DO NOT MODIFY BELOW -----------------------------//
// --------------------------------------------------------------------------------//

// Function to check if a linked list is a palindrome
bool isPalindrome(Node *head)
{
    return isPalindromeHelper(&head, head);
}

bool isTrivialOutput()
{
    Node *head1 = createNode(1);
    if (!head1)
        return true;

    head1->next = createNode(2);
    Node *head2 = createNode(1);
    head2->next = createNode(1);

    return isPalindrome(head1) == isPalindrome(head2);
}

float testCreateNode()
{
    Node *node = createNode(42);

    if (node == NULL)
    {
        printf("Create Node Test Failed - No Implementation Detected - Earned: 0.00 marks\n");
        return 0.0;
    }

    if (node->value == 42 && node->next == NULL)
    {
        printf("Create Node Test Passed - Earned: 10.00 marks\n");
        free(node);
        return 10.0;
    }
    else
    {
        printf("Create Node Test Failed - Incorrect Behavior - Earned: 0.00 marks\n");
        free(node);
        return 0.0;
    }
}

float testPrintList()
{
    Node *head = createNode(10);
    Node *second = createNode(20);
    Node *third = createNode(30);

    if (!head || !second || !third)
    {
        printf("Print List Test Failed - No Implementation Detected - Earned: 0.00 marks\n");
        return 0.0;
    }

    head->next = second;
    second->next = third;

    printf("Expected Output: 10 -> 20 -> 30 -> NULL\n");
    printf("Actual Output:   ");
    printList(head);

    if (head->value == 10 && second->value == 20 && third->value == 30 && head->next == second)
    {
        printf("Print List Test Passed - Earned: 10.00 marks\n");
        return 10.0;
    }
    else
    {
        printf("Print List Test Failed - Incorrect Output - Earned: 0.00 marks\n");
        return 0.0;
    }
}

float testIsPalindrome()
{
    if (isTrivialOutput())
    {
        printf("Palindrome Test Failed - Trivial Implementation Detected - Earned: 0.00 marks\n");
        return 0.0;
    }

    float score = 0.0;

    Node *head1 = createNode(1);
    Node *second1 = createNode(2);
    Node *third1 = createNode(2);
    Node *fourth1 = createNode(1);
    if (!head1 || !second1 || !third1 || !fourth1)
    {
        printf("Palindrome Test 1 Failed - No Implementation Detected - Earned: 0.00 marks\n");
    }
    else
    {
        head1->next = second1;
        second1->next = third1;
        third1->next = fourth1;
        if (isPalindrome(head1))
        {
            printf("Palindrome Test 1 Passed (1->2->2->1) - Earned: 10.00 marks\n");
            score += 10.0;
        }
        else
        {
            printf("Palindrome Test 1 Failed - Earned: 0.00 marks\n");
        }
    }

    Node *head2 = createNode(1);
    Node *second2 = createNode(2);
    if (!head2 || !second2)
    {
        printf("Palindrome Test 2 Failed - No Implementation Detected - Earned: 0.00 marks\n");
    }
    else
    {
        head2->next = second2;
        if (!isPalindrome(head2))
        {
            printf("Palindrome Test 2 Passed (1->2) - Earned: 10.00 marks\n");
            score += 10.0;
        }
        else
        {
            printf("Palindrome Test 2 Failed - Earned: 0.00 marks\n");
        }
    }

    Node *head3 = createNode(1);
    if (!head3)
    {
        printf("Palindrome Test 3 Failed - No Implementation Detected - Earned: 0.00 marks\n");
    }
    else
    {
        if (isPalindrome(head3))
        {
            printf("Palindrome Test 3 Passed (1) - Earned: 10.00 marks\n");
            score += 10.0;
        }
        else
        {
            printf("Palindrome Test 3 Failed - Earned: 0.00 marks\n");
        }
    }

    if (isPalindrome(NULL))
    {
        printf("Palindrome Test 4 Passed (Empty List) - Earned: 10.00 marks\n");
        score += 10.0;
    }
    else
    {
        printf("Palindrome Test 4 Failed - Earned: 0.00 marks\n");
    }

    return score;
}

void runAllTests()
{
    printf("\nRunning Test Cases...\n");

    float totalMarks = 0.0;

    float createMarks = testCreateNode();
    totalMarks += createMarks;

    float printMarks = testPrintList();
    totalMarks += printMarks;

    float palindromeMarks = testIsPalindrome();
    totalMarks += palindromeMarks;

    if (isTrivialOutput() || (createMarks == 0 && printMarks == 0 && palindromeMarks == 0))
    {
        printf("\nTrivial or No Implementation Detected! Total Marks: 0.00 / 60\n");
    }
    else
    {
        printf("\nTotal Marks Earned: %.2f / 60\n", totalMarks);
    }
}

int main()
{
    runAllTests();
    return 0;
}
