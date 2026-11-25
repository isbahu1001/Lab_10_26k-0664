#include <stdio.h>

int markZone(char map[][5], int r, int c, char label) {
    if (r < 0 || r >= 5 || c < 0 || c >= 5 || map[r][c] != '*')
        return 0;
    map[r][c] = label;
    return 1 + markZone(map, r - 1, c, label)
             + markZone(map, r + 1, c, label)
             + markZone(map, r, c - 1, label)
             + markZone(map, r, c + 1, label);
}

int main(void) {
    float temp[5][5] = {
        { 2.1f, -1.5f, -2.0f,  3.0f,  4.2f},
        { 1.8f, -0.5f,  2.5f,  3.1f, -1.0f},
        { 3.3f,  2.0f,  1.5f, -0.8f, -2.0f},
        {-1.2f,  3.4f,  4.0f,  3.8f, -0.6f},
        {-2.5f, -3.1f,  5.1f,  6.0f,  4.7f}
    };
    char map[5][5];
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            map[i][j] = (temp[i][j] < 0) ? '*' : '.';

    char label = 'A';
    int zones = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (map[i][j] == '*') {
                int size = markZone(map, i, j, label);
                printf("Zone %c: %d stations\n", label, size);
                label++;
                zones++;
            }
        }
    }
    printf("Total zones: %d\n\n", zones);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++)
            printf("%c  ", map[i][j]);
        printf("\n");
    }
    return 0;
}
