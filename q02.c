#include <stdio.h>
#define REC 24
#define LECTURES 20

int main(void) {
    FILE *fp = fopen("attendance.txt", "w");
    if (!fp) { printf("Cannot create file\n"); return 1; }
    fprintf(fp, "%-3d %-15s %3d\n", 1, "Ayesha", 18);
    fprintf(fp, "%-3d %-15s %3d\n", 2, "Bilal",  14);
    fprintf(fp, "%-3d %-15s %3d\n", 3, "Hamza",  20);
    fprintf(fp, "%-3d %-15s %3d\n", 4, "Sana",   12);
    fprintf(fp, "%-3d %-15s %3d\n", 5, "Zainab", 16);
    fclose(fp);

    fp = fopen("attendance.txt", "rb+");
    if (!fp) { printf("Cannot open file\n"); return 1; }

    int roll, r, att, leave;
    char name[16];

    /* Check attendance */
    printf("Roll number: ");
    scanf("%d", &roll);
    fseek(fp, (long)(roll - 1) * REC, SEEK_SET);
    fscanf(fp, "%d %s %d", &r, name, &att);
    float pct = att * 100.0f / LECTURES;
    printf("%s: %d / %d (%.1f%%)", name, att, LECTURES, pct);
    if (pct < 75) printf(" Short attendance");
    printf("\n");

    /* Medical leave */
    printf("Roll number for leave: ");
    scanf("%d", &roll);
    printf("Lectures: ");
    scanf("%d", &leave);
    fseek(fp, (long)(roll - 1) * REC, SEEK_SET);
    fscanf(fp, "%d %s %d", &r, name, &att);
    att += leave;
    if (att > LECTURES) att = LECTURES;
    fseek(fp, (long)(roll - 1) * REC, SEEK_SET);
    fprintf(fp, "%-3d %-15s %3d\n", r, name, att);
    fflush(fp);
    printf("%s: now %d / %d (%.1f%%)\n", name, att, LECTURES, att * 100.0f / LECTURES);

    /* Last record */
    fseek(fp, -REC, SEEK_END);
    fscanf(fp, "%d %s %d", &r, name, &att);
    printf("Last record: %d %s %d\n", r, name, att);

    fclose(fp);
    return 0;
}
