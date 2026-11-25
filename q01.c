#include <stdio.h>
#define REC 42

int main(void) {
    FILE *fp = fopen("items.txt", "w");
    if (!fp) { printf("Cannot create file\n"); return 1; }
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 1, "Rice",       250.00, 40);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 2, "Sugar",      160.00, 25);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 3, "Milk",       220.00, 30);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 4, "CookingOil", 560.00, 12);
    fprintf(fp, "%-4d %-20s %9.2f %5d\n", 5, "Tea",        450.00, 18);
    fclose(fp);

    fp = fopen("items.txt", "rb+");
    if (!fp) { printf("Cannot open file\n"); return 1; }

    int itemNo, qty, no, stock;
    char name[21];
    float price, total = 0;

    while (1) {
        printf("Item no: ");
        scanf("%d", &itemNo);
        if (itemNo == 0) break;
        printf("Quantity: ");
        scanf("%d", &qty);

        fseek(fp, (long)(itemNo - 1) * REC, SEEK_SET);
        fscanf(fp, "%d %s %f %d", &no, name, &price, &stock);

        if (stock >= qty) {
            float cost = qty * price;
            printf("%-10s %d x %.2f = %.2f\n", name, qty, price, cost);
            total += cost;
            stock -= qty;
            fseek(fp, (long)(itemNo - 1) * REC, SEEK_SET);
            fprintf(fp, "%-4d %-20s %9.2f %5d\n", no, name, price, stock);
            fflush(fp);
        } else {
            printf("Only %d %s in stock\n", stock, name);
        }
    }
    printf("Total bill: %.2f\n", total);
    fclose(fp);
    return 0;
}
