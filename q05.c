#include <stdio.h>
#define REC 23

int main(void) {
    /* create the starting file */
    FILE *fp = fopen("expenses.txt", "w");
    if (!fp) { printf("Cannot create file\n"); return 1; }
    fprintf(fp, "%-12s %9.2f\n", "Food",      1200.00);
    fprintf(fp, "%-12s %9.2f\n", "Transport",  500.00);
    fprintf(fp, "%-12s %9.2f\n", "Books",      850.00);
    fprintf(fp, "%-12s %9.2f\n", "Mobile",     300.00);
    fclose(fp);

    char cat[13];
    float amt;

    /* 1. append */
    printf("Category: ");
    scanf("%12s", cat);
    printf("Amount: ");
    scanf("%f", &amt);
    fp = fopen("expenses.txt", "ab");
    fprintf(fp, "%-12s %9.2f\n", cat, amt);
    fclose(fp);

    /* 2. latest two */
    fp = fopen("expenses.txt", "rb+");
    if (!fp) { printf("Cannot open file\n"); return 1; }
    fseek(fp, -2 * REC, SEEK_END);
    char c1[13], c2[13];
    float a1, a2;
    fscanf(fp, "%s %f %s %f", c1, &a1, c2, &a2);
    printf("Latest two: %s %.2f, %s %.2f\n", c1, a1, c2, a2);

    /* 3. fix an entry */
    int n;
    printf("Entry to fix: ");
    scanf("%d", &n);
    printf("Correct amount: ");
    scanf("%f", &amt);
    fseek(fp, (long)(n - 1) * REC, SEEK_SET);
    fscanf(fp, "%s %*f", cat);
    fseek(fp, (long)(n - 1) * REC, SEEK_SET);
    fprintf(fp, "%-12s %9.2f\n", cat, amt);
    fflush(fp);

    /* 4. print all + total */
    rewind(fp);
    float total = 0;
    while (fscanf(fp, "%s %f", cat, &amt) == 2) {
        printf("%s %.2f\n", cat, amt);
        total += amt;
    }
    printf("Total: %.2f\n", total);

    fclose(fp);
    return 0;
}
