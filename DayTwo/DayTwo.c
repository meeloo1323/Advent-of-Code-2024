#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main()
{
    // Open the input file and read in the data
    FILE *file = fopen("DayTwoInput.txt", "r");
    char fileLine[50];
    int reports[1000][10]; // Stores the parsed input file in a 2d int array
    int index = 0;
    while (fgets(fileLine, 50, file) != NULL)
    {
        // While the line has not been fully parsed, convert ascii to int and store in a 2d int array
        char *token = strtok(fileLine, " ");
        int level = 0;
        while (token != NULL) // Read in from the file.
        {
            reports[index][level] = atoi(token);
            token = strtok(NULL, " ");
            level++;
        }
        while (level < 10) // Fill the rest of the 2d array with -1 (the input does not contain any negative numbers. This will act as an indicator for reaching the end of a report)
        {
            reports[index][level] = -1;
            level++;
        }
        index++;
    }
    fclose(file);

    // Begin counting the number of safe reports
    int totalCorrect = 0;
    for (index = 0; index < 1000; index++)
    {
        bool safe = true; // Start our report parsing with the assumption that it's safe
        if (reports[index][0] > reports[index][1]) // If our first comparison indicates descending order
        {
            for (int level = 0; level < 10; level++)
            {
                if (reports[index][level + 1] == -1) // If we reached the end of the report
                    break;
                else if (reports[index][level] <= reports[index][level + 1] || abs(reports[index][level] - reports[index][level + 1]) > 3) // If our next level is the same or in ascending order, or the difference is greater than 3, mark report as unsafe
                {
                    safe = false;
                    break;
                }
            }
        }
        else if (reports[index][0] < reports[index][1]) // If our first comparison indicates ascending order
        {
            for (int level = 0; level < 10; level++)
            {
                if (reports[index][level + 1] == -1) // If we reached the end of the report
                    break;
                else if (reports[index][level] >= reports[index][level + 1] || abs(reports[index][level] - reports[index][level + 1]) > 3) // If our next level is the same or in descending order, or the difference is greater than 3, mark report as unsafe
                {
                    safe = false;
                    break;
                }
            }
        }
        else // If our first comparison indicates that they are the same number, mark report as unsafe
            safe = false;
        if (safe)
            totalCorrect++;
    }

    printf("Total Safe: %i\n", totalCorrect);
}