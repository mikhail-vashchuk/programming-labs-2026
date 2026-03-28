#include <cstdio>
#include <cstdlib>
#include <cstring>

struct Passenger {
    char name[50];
    int itemsCount;
    float totalWeight;
};

int main() {

    FILE *f = fopen("/Users/mikhail/Desktop/passengerInfo.txt", "w");

    if (f == NULL) {
        printf("ERROR: file was not opened\n");
        return 1;
    }

   Passenger passengers[10];

    strcpy(passengers[0].name, "Maksym Kovalenko");
    passengers[0].itemsCount = 3;
    passengers[0].totalWeight = 18.5;

    strcpy(passengers[1].name, "Anna Shevchenko");
    passengers[1].itemsCount = 1;
    passengers[1].totalWeight = 7.2;

    strcpy(passengers[2].name, "Yuliia Bondar");
    passengers[2].itemsCount = 4;
    passengers[2].totalWeight = 23.8;

    strcpy(passengers[3].name, "Oleksii Marchenko");
    passengers[3].itemsCount = 2;
    passengers[3].totalWeight = 11.4;

    strcpy(passengers[4].name, "Sofiia Tkachenko");
    passengers[4].itemsCount = 5;
    passengers[4].totalWeight = 27.6;

    strcpy(passengers[5].name, "Andrii Melnyk");
    passengers[5].itemsCount = 2;
    passengers[5].totalWeight = 13.1;

    strcpy(passengers[6].name, "Kateryna Boiko");
    passengers[6].itemsCount = 3;
    passengers[6].totalWeight = 16.9;

    strcpy(passengers[7].name, "Danylo Kravchenko");
    passengers[7].itemsCount = 6;
    passengers[7].totalWeight = 31.2;

    strcpy(passengers[8].name, "Alina Oliinyk");
    passengers[8].itemsCount = 1;
    passengers[8].totalWeight = 6.5;

    strcpy(passengers[9].name, "Roman Hrytsenko");
    passengers[9].itemsCount = 4;
    passengers[9].totalWeight = 21.7;
    
   fprintf(f, "%-20s %10s %15s\n", "Passenger name", "Items", "Weight");
   fprintf(f, "-------------------------------------------------------\n");

    for (int i = 0; i < 10; i++) {
        fprintf(f, "%-20s %10d %15.1f\n",
            passengers[i].name,
            passengers[i].itemsCount,
            passengers[i].totalWeight);
    }

    fclose(f);

    return 0;
}