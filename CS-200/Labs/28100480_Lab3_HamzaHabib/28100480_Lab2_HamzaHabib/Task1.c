#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* copy_substring(const char* str, int start, int no_of_chars)
{
    char *copy_string = (char *) malloc ((no_of_chars + 1) * sizeof(char));
    int index = 0;
    for (int i = start; i < no_of_chars + start; i++)
    {
        copy_string[index] = str[i];
        index++;
    }
    copy_string[index] = '\0';
    return copy_string;
    free(copy_string);
}

int main()
{
    char string[100];
    int no_of_char;
    int index;
    printf("Enter a string: ");
    scanf("%[^\n]s", string);
    printf("Enter the starting index: ");
    scanf("%d", &index);
    printf("Enter the number of characters to copy: ");
    scanf("%d", &no_of_char);
    printf("Copied Substring: %s\n", copy_substring(string, index, no_of_char));
    return 0;
}