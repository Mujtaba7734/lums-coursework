#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int size = 2;
    int *arr =(int *) malloc (size * sizeof (int));
    int quantity;
    int totalstock =0;
    int maximum = 0;
    int current_size = 0;
    printf("Emter Quantity (-1 to stop): ");
    scanf("%d", &quantity);
    *(arr + current_size) = quantity;
    while (quantity != -1)
    {
        if (current_size >=2)
        {
            size++;
            arr =(int *) realloc(arr, size * sizeof (int));
        }  
        totalstock += *(arr + current_size);
        if (*(arr + current_size) > maximum)
        {
            maximum = *(arr + current_size);
        }
        current_size++;
        printf("Enter Quantity (-1 to stop): ");
        scanf("%d", &quantity);
        *(arr + current_size) = quantity;
    }
    printf("Quantities: ");
    for (int i = current_size - 1; i > -1; i--)
    {
        printf("%d", *(arr + i));
        printf(", ");
    }
    printf("\n Total stock: %d\n ", totalstock);
    printf("Max quantity: %d\n ", maximum);

    return 0;
}