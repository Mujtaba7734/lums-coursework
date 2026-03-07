#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_roll_numbers(char* input)
{
    printf("check 1");
    char **(tokens) = (char**) + (200 * sizeof(char));
    char completedstring5[200];
    char completedstring6[200];
    char completedstring7[200];
    char completedstring8[200];
    int i=0;
    char *token = strtok(input, ",");
    while (token != NULL)
    {
        *(tokens + i) = token;
        i++; 
        token = strtok(NULL, ","); 
    }
    printf("check 3");
    for (int j=0; i<i; j++)
    {
        if (*(*(tokens + 1) + j) == '5')
        {
            strcat(completedstring5, tokens[i]);
            strcat(completedstring5, ",");
        }
        if (*(*(tokens + 1) + j) == '6')
        {
            strcat(completedstring6, tokens[i]);
            strcat(completedstring6, ",");
        }
        if (*(*(tokens + 1) + j) == '7')
        {
            strcat(completedstring7, tokens[i]);
            strcat(completedstring7, ",");
        }
        if (*(*(tokens + 1) + j) == '8')
        {
            strcat(completedstring8, tokens[i]);
            strcat(completedstring8, ",");
        }
        strcat(completedstring5, "\0");
        strcat(completedstring6, "\0");
        strcat(completedstring7, "\0");
        strcat(completedstring8, "\0");
        printf("Roll Numbers of batch 25: %s\n", *completedstring5);
        printf("Roll Numbers of batch 26: %s\n", *completedstring6);
        printf("Roll Numbers of batch 27: %s\n", *completedstring7);
        printf("Roll Numbers of batch 28: %s\n", *completedstring8);
    }
}

int main()
{
    char string[200];
    printf("Enter the roll numbers: ");
    scanf("%[^\n]s", string);
    process_roll_numbers(string);
}