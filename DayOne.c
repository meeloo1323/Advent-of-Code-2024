/*
Two pairs of lists. Pair up smallest number in the left list with the smallest number in the right list, then the second-smallest left number with the second-smallest right number, and so on.
Within each pair, figure out how far apart the two numbers are; you'll need to add up all of those distances.
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE* file;
    file = fopen("./DayOneInput.txt", "R");

    if (file == NULL)
    {
        printf("File \"DayOneInput.txt\" could not be found");
        exit(1);
    }

    printf("Success");
}