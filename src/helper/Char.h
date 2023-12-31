#include <stdio.h>
#include <stdlib.h>

void longToCharArray(long value, char **charArray)
{
    // Determine the maximum length needed for the string representation
    int maxLength = snprintf(NULL, 0, "%ld", value);
    // Allocate memory for the character array
    *charArray = (char *)malloc((maxLength + 1) * sizeof(char)); // +1 for the null terminator
    // Check if memory allocation is successful
    if (*charArray != NULL)
    {
        // Convert the long to a character array
        snprintf(*charArray, maxLength + 1, "%ld", value);
    }
    else
    {
        // Handle memory allocation failure
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
}