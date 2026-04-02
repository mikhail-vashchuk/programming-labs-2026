#include "state.h"

#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <limits>
#include <algorithm>
#include <strings.h>

void clearInputLine() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt() {
    int x;
    while (true) {
        if (std::cin >> x) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cout << "Error: enter a digit.\n";
        clearInputLine();
    }
}

double readDouble() {
    double x;
    while (true) {
        if (std::cin >> x) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cout << "Error: enter a digit.\n";
        clearInputLine();
    }
}

void readLine(char text[], int size) {
    while (true) {
        std::cin.getline(text, size);

        if (std::cin.fail()) {
            std::cout << "Error: line is too long.\n";
            clearInputLine();
            continue;
        }

        if (std::strlen(text) == 0) {
            std::cout << "Error: line cannot be empty.\n";
            continue;
        }

        return;
    }
}

void createFile(const char* fileName) {
    std::ofstream file(fileName, std::ios::binary);
    file.close();
}

bool deleteFile(const char* fileName) {
    return std::remove(fileName) == 0;
}

bool fileExists(const char* fileName) {
    std::ifstream file(fileName, std::ios::binary);
    return file.is_open();
}

int countRecords(const char* fileName) {
    std::ifstream file(fileName, std::ios::binary);

    file.seekg(0, std::ios_base::end);
    int k = file.tellg() / sizeof(State);
    file.close();

    return k;
}

void readFile(const char* fileName, State states[], int n) {
    std::ifstream file(fileName, std::ios::binary);

    for (int i = 0; i < n; i++) {
        file.read((char*)&states[i], sizeof(states[i]));
    }

    file.close();
}

void inputStates(State states[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << "\nCountry name: ";
        readLine(states[i].name, 30);

        std::cout << "Official language count: ";
        states[i].languageCount = readInt();

        std::cout << "Language: ";
        readLine(states[i].language, 30);

        std::cout << "Currency: ";
        readLine(states[i].currency, 20);

        std::cout << "USD rate: ";
        states[i].usdRate = readDouble();
    }
}

void addRecordsToFile(const char* fileName, const State states[], int n) {
    std::ofstream file(fileName, std::ios::binary | std::ios::app);

    for (int i = 0; i < n; i++) {
        file.write((char*)&states[i], sizeof(states[i]));
    }

    file.close();
}

void removeRecordsFromFile(const char* fileName, const State states[], int n, const char (*namesToDelete)[30], int m) {
    std::ofstream file(fileName, std::ios::binary);

    for (int i = 0; i < n; i++) {
        bool shouldDelete = false;
        for (int j = 0; j < m; j++) {
            if (std::strcmp (states[i].name, namesToDelete[j]) == 0) {
                shouldDelete = true;
                break;
            }
        }
        if (shouldDelete) {
            continue;
        }
        else {
            file.write((char*)&states[i], sizeof(states[i]));
        }
    }
    
     file.close();
}

void printRecord(const State& state) {
    std::cout << "\nCountry: " << state.name;
    std::cout << "\nOfficial language count: " << state.languageCount;
    std::cout << "\nLanguage: " << state.language;
    std::cout << "\nCurrency: " << state.currency;
    std::cout << "\nUSD rate: " << state.usdRate << "\n";
}

void printAllRecords(const State states[], int n) {
    for (int i = 0; i < n; i++) {
        printRecord(states[i]);
    }
}

void showCountriesWithMoreThanOneLanguage(const State states[], int n) {
    bool exists = false;

    for (int i = 0; i < n; i++) {
        if (states[i].languageCount > 1) {
            printRecord(states[i]);
            exists = true;
        }
    }

    if (!exists) {
        std::cout << "No countries found.\n";
    }
}

void showCountriesWithUsdRateBelow(const State states[], int n, double userRate) {
    bool exists = false;

    for (int i = 0; i < n; i++) {
        if (states[i].usdRate < userRate) {
            printRecord(states[i]);
            exists = true;
        }
    }

    if (!exists) {
        std::cout << "No countries found.\n";
    }
}

void sortCountries(State states[], int n) {
    std::sort(states, states + n, [](const State& a, const State& b) {
        return strcasecmp(a.name, b.name) < 0;
    });
}