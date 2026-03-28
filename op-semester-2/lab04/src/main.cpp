#include <cstdio>
#include <cstdlib>
#include <cstring>

struct Passenger {
    char name[50];
    int itemsCount;
    float totalWeight;
};

void readFile(Passenger passengers[], int &n) {
    FILE *f = fopen("/Users/mikhail/Desktop/passengerInfo.txt", "r");

    if (f == 0) {
        printf("error read from file");
        exit(1);
    }

    char line[200];
    fgets(line, sizeof(line), f);
    fgets(line, sizeof(line), f);

    int i = 0;
    while (fscanf(f, "%s%d%f",
                  passengers[i].name,
                  &passengers[i].itemsCount,
                  &passengers[i].totalWeight) == 3) {
        i++;
    }

    n = i;
    fclose(f);
}

double averege (Passenger passengers[], int n) {
double summ = 0;
    for (int i = 0; i < n; i++) {
        summ += passengers[i].itemsCount;
    }
return summ/n;
}

void writeFile(Passenger passengers[], int n) {
    FILE *passengerInfo2 = fopen("/Users/mikhail/Desktop/passengerInfo2.txt", "w");

    fprintf(passengerInfo2, "Information got from the %s.\n", "passengerInfo.txt");
    fprintf(passengerInfo2, "\n");

    fprintf(passengerInfo2, "Passengers with two or less items: \n");

   for (int i = 0; i < n; i++) {
    if (passengers[i].itemsCount <= 2) {
        fprintf(passengerInfo2, "%-20s %10d %15.1f\n",
            passengers[i].name,
            passengers[i].itemsCount,
            passengers[i].totalWeight);
    }
   }
   fprintf(passengerInfo2, "\n");

   double avg = averege(passengers, n);
   int count = 0;
   for (int i = 0; i < n; i++) {
    if (passengers[i].itemsCount > avg) {
        count++;
    }
}
   fprintf(passengerInfo2, "Count of passengers with items count above average (%.2f): %d\n",avg, count);

    fclose(passengerInfo2);
}

int main() {
    int n = 0;
    Passenger passengers[20];

    readFile(passengers, n);
    writeFile(passengers, n);

    return 0;
}