#include <stdio.h>

void grow(int heights[], int n) {
    if (n == 0) return;
    heights[n - 1] += (int)(heights[n - 1] * 0.10);
    grow(heights, n - 1);
}

int tallest(int heights[], int n) {          /* returns position */
    if (n == 1) return 0;
    int p = tallest(heights, n - 1);
    return (heights[n - 1] > heights[p]) ? n - 1 : p;
}

int search(int heights[], int n, int target) {
    if (n == 0) return -1;
    if (heights[n - 1] == target) return n - 1;
    return search(heights, n - 1, target);
}

int main(void) {
    int ids[6] = {101, 102, 103, 104, 105, 106};
    int heights[6] = {45, 120, 78, 200, 95, 150};

    grow(heights, 6);
    printf("New heights:");
    for (int i = 0; i < 6; i++) printf(" %d", heights[i]);
    printf("\n");

    int t = tallest(heights, 6);
    printf("Tallest: tower %d (%d m)\n", ids[t], heights[t]);

    int target;
    printf("Height to search: ");
    scanf("%d", &target);
    int p = search(heights, 6, target);
    if (p == -1) printf("No tower has height %d m\n", target);
    else         printf("Tower %d is %d m\n", ids[p], heights[p]);
    return 0;
}
