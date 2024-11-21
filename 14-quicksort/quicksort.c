#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0;
int moveCount = 0;

void generateRandomArray(int array[]) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisonCount++;
        if (array[j] < pivot) {
            i++;

            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            moveCount++;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    moveCount++;

    return i + 1;
}

void doIterativeQuickSort(int array[], int low, int high, int isFirst) {
    int stack[SIZE];
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    int rounds = 0;

    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];

        int pi = partition(array, low, high);

        if (isFirst && rounds % 10 == 0) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n\n");
        }
        rounds++;

        if (pi - 1 > low) {
            stack[++top] = low;
            stack[++top] = pi - 1;
        }

        if (pi + 1 < high) {
            stack[++top] = pi + 1;
            stack[++top] = high;
        }
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];
    double totalComparisons = 0;
    double totalMoveCount = 0;

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Iterative Quick Sort Run\n");
            doIterativeQuickSort(array, 0, SIZE - 1, 1);
            printf("Result\n");
            printArray(array, SIZE);
        }
        else {
            doIterativeQuickSort(array, 0, SIZE - 1, 0);
        }

        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    printf("\nAverage Comparisons : %.2f\n", totalComparisons / 20.0);
    printf("Average Moves : %.2f\n", totalMoveCount / 20.0);

    return 0;
}
