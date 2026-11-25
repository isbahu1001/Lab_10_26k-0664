#include <stdio.h>
#define REC 17
#define N 5

int main(void) {
    FILE *fp = fopen("temperature.txt", "w");
    if (!fp) { printf("Cannot create file\n"); return 1; }
    char city[11];
    float t;
    for (int i = 0; i < N; i++) {
        printf("City %d name and temperature: ", i + 1);
        scanf("%10s %f", city, &t);
        fprintf(fp, "%-10s %5.1f\n", city, t);
    }
    fclose(fp);

    fp = fopen("temperature.txt", "rb+");
    if (!fp) { printf("Cannot open file\n"); return 1; }

    int n;
    printf("City number: ");
    scanf("%d", &n);
    fseek(fp, (long)(n - 1) * REC, SEEK_SET);
    fscanf(fp, "%s %f", city, &t);
    printf("%s %.1f\n", city, t);

    printf("City number to correct: ");
    scanf("%d", &n);
    printf("New temperature: ");
    scanf("%f", &t);
    fseek(fp, (long)(n - 1) * REC, SEEK_SET);
    fscanf(fp, "%s %*f", city);               /* read name only */
    fseek(fp, (long)(n - 1) * REC, SEEK_SET);
    fprintf(fp, "%-10s %5.1f\n", city, t);
    fflush(fp);
    printf("%s updated to %.1f\n", city, t);

    rewind(fp);
    char hotCity[11] = "";
    float hot = -1000;
    for (int i = 0; i < N; i++) {
        fscanf(fp, "%s %f", city, &t);
        if (t > hot) {
            hot = t;
            for (int k = 0; k < 11; k++) hotCity[k] = city[k];
        }
    }
    printf("Hottest city: %s (%.1f)\n", hotCity, hot);

    fclose(fp);
    return 0;
}
