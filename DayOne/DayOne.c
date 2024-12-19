/*
Two pairs of lists. Pair up smallest number in the left list with the smallest number in the right list, then the second-smallest left number with the second-smallest right number, and so on.
Within each pair, figure out how far apart the two numbers are; you'll need to add up all of those distances.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int *list, int leftIndex, int middleIndex, int rightIndex)
{
    int leftDummyIndex, rightDummyIndex, index;
    int leftDummySize, rightDummySize;
    leftDummySize = middleIndex - leftIndex + 1;
    rightDummySize = rightIndex - middleIndex;
    int *leftDummy, *rightDummy;
    leftDummy = calloc(leftDummySize, sizeof(int));
    rightDummy = calloc(rightDummySize, sizeof(int));

    for (leftDummyIndex = 0; leftDummyIndex < leftDummySize; leftDummyIndex++)
        leftDummy[leftDummyIndex] = list[leftIndex + leftDummyIndex];
    for (rightDummyIndex = 0; rightDummyIndex < rightDummySize; rightDummyIndex++)
        rightDummy[rightDummyIndex] = list[middleIndex + 1 + rightDummyIndex];
    
    leftDummyIndex = 0;
    rightDummyIndex = 0;
    index = leftIndex;

    while (leftDummyIndex < leftDummySize && rightDummyIndex < rightDummySize)
    {
        if (leftDummy[leftDummyIndex] <= rightDummy[rightDummyIndex])
        {
            list[index] = leftDummy[leftDummyIndex];
            leftDummyIndex++;
        }
        else
        {
            list[index] = rightDummy[rightDummyIndex];
            rightDummyIndex++;
        }
        index++;
    }
    while (leftDummyIndex < leftDummySize)
    {
        list[index] = leftDummy[leftDummyIndex];
        index++;
        leftDummyIndex++;
    }
    while (rightDummyIndex < rightDummySize)
    {
        list[index] = rightDummy[rightDummyIndex];
        index++;
        rightDummyIndex++;
    }

    free(leftDummy);
    free(rightDummy);
}

void mergeSort(int *list, int leftIndex, int rightIndex)
{
    if (leftIndex < rightIndex)
    {

        int middleIndex = (rightIndex - leftIndex) / 2 + leftIndex;

        mergeSort(list, leftIndex, middleIndex);
        mergeSort(list, middleIndex + 1, rightIndex);

        merge(list, leftIndex, middleIndex, rightIndex);
    }
}

int main()
{
    FILE* file;
    file = fopen("DayOneInput.txt", "r");

    if (file == NULL)
    {
        printf("File \"DayOneInput.txt\" could not be found");
        exit(1);
    }

    int leftList[1000], rightList[1000]; // Knowing Advent of Code gives me 1000 lines of pairs, our assumption is that there is only 1000 pairs, and no more.
    int index = 0;
    char fileLine[50];
    while (fgets(fileLine, 50, file) != NULL)
    {
        char *token = strtok(fileLine, " ");
        leftList[index] = atoi(token);
        token = strtok(NULL, " ");
        rightList[index] = atoi(token);
        index++;
    }
    fclose(file);

    mergeSort(leftList, 0, 999);
    mergeSort(rightList, 0, 999);

    int sum = 0;
    for (int i = 0; i < 1000; i++)
        sum += abs(leftList[i] - rightList[i]);
    printf("The sum of differences is: %i", sum);
}