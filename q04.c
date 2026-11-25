#include <stdio.h>
#include <string.h>
#define REC 39
#define ROOMS 10
#define RATE 8000.00

void checkIn(FILE *fp) {
    int room, rno, nights, oldNights;
    char name[21], status, oldName[21];
    float rate;

    printf("Check-in room: ");
    scanf("%d", &room);
    printf("Name: ");
    scanf("%20s", name);
    printf("Nights: ");
    scanf("%d", &nights);

    long pos = (long)(room - 101) * REC;
    fseek(fp, pos, SEEK_SET);
    fscanf(fp, "%d %c %s %d %f", &rno, &status, oldName, &oldNights, &rate);

    if (status == 'F') {
        fseek(fp, pos, SEEK_SET);
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'B', name, nights, rate);
        fflush(fp);
        printf("Room %d booked\n", room);
    } else {
        printf("Room already booked\n");
    }
}

void searchGuest(FILE *fp) {
    char guests[ROOMS][21], status[ROOMS], key[21];
    int rooms[ROOMS], nights, found = 0;
    float rate;

    rewind(fp);
    for (int i = 0; i < ROOMS; i++)
        fscanf(fp, "%d %c %s %d %f", &rooms[i], &status[i], guests[i], &nights, &rate);

    printf("Search name: ");
    scanf("%20s", key);
    for (int i = 0; i < ROOMS; i++) {
        if (strcmp(guests[i], key) == 0) {
            printf("%s is in room %d\n", key, rooms[i]);
            found = 1;
            break;
        }
    }
    if (!found) printf("%s not found\n", key);
}

void checkOut(FILE *fp) {
    int room, rno, nights;
    char status, name[21];
    float rate;

    printf("Check-out room: ");
    scanf("%d", &room);
    long pos = (long)(room - 101) * REC;
    fseek(fp, pos, SEEK_SET);
    fscanf(fp, "%d %c %s %d %f", &rno, &status, name, &nights, &rate);

    if (status == 'F') {
        printf("Room %d is already free\n", room);
        return;
    }
    printf("Bill: %d x %.2f = %.2f\n", nights, rate, nights * rate);
    fseek(fp, pos, SEEK_SET);
    fprintf(fp, "%3d %c %-20s %2d %8.2f\n", room, 'F', "-", 0, rate);
    fflush(fp);
}

int main(void) {
    FILE *fp = fopen("hotel.txt", "w");
    if (!fp) { printf("Cannot create file\n"); return 1; }
    for (int r = 101; r <= 110; r++)
        fprintf(fp, "%3d %c %-20s %2d %8.2f\n", r, 'F', "-", 0, RATE);
    fclose(fp);

    fp = fopen("hotel.txt", "rb+");
    if (!fp) { printf("Cannot open file\n"); return 1; }

    checkIn(fp);      /* first booking */
    checkIn(fp);      /* try the same room again */
    searchGuest(fp);
    checkOut(fp);

    fclose(fp);
    return 0;
}
