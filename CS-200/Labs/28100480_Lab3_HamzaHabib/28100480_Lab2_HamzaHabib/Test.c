#include <stdio.h>
#include <string.h>

int main() {
 char str1[20] = "Hello";
 char str2[] = " World";
 strcat(str1, str2);
 printf("Concatenated String: %s\n", str1);
} 