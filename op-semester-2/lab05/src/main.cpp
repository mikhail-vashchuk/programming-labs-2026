#include <iostream>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <limits>
#include <algorithm>
#include <strings.h>

// Structure

struct State {
    char name[30];
    int languageCount;
    char language[30];
    char currency[20];
    double usdRate;
};

// Helpful functions

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

// Main Functions - create/delete

void createFile(const char* fileName) {
    std::ofstream file(fileName, std::ios::binary);
    file.close();
}

bool deleteFile(const char* fileName) {
    return std::remove(fileName) == 0;
}

// If exists

bool fileExists(const char* fileName) {
    std::ifstream file(fileName, std::ios::binary);
    return file.is_open();
}

// Count records

int countRecords(const char* fileName) {
    std::ifstream file(fileName, std::ios::binary);

    file.seekg(0, std::ios_base::end);
    int k = file.tellg() / sizeof(State);
    file.close();

    return k;
}

// Read file

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

// Write file

void addRecordsToFile(const char* fileName, const State states[], int n) {
    std::ofstream file(fileName, std::ios::binary | std::ios::app);

    for (int i = 0; i < n; i++) {
        file.write((char*)&states[i], sizeof(states[i]));
    }

    file.close();
}

// Remove some records from file

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

// Print

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

// Show countries with more than one official language

void showCountriesWithMoreThanOneLanguage(const State states[], int n) {
    for (int i = 0; i < n; i++) {
        if (states[i].languageCount > 1) {
            printRecord(states[i]);
        }
    }
}

// Show countries with a low USD exchange rate

void showCountriesWithUsdRateBelow(const State states[], int n, double userRate) {
    for (int i = 0; i < n; i++) {
        if (states[i].usdRate < userRate) {
            printRecord(states[i]);
        }
    }
}

// Sort countries

void sortCountries(State states[], int n) {
    std::sort(states, states + n, [](const State& a, const State& b) {
        return strcasecmp(a.name, b.name) < 0;
    });
}

// Main

int main() {
    char fileName[80];
    int k = 0;
    State* states = nullptr;

    while (true) {
        std::cout << "\n1: Create file\n";
        std::cout << "2: Add record(s) to the file\n";
        std::cout << "3: Delete file\n";
        std::cout << "4: Delete record(s) from the file\n";
        std::cout << "5: Show all records from the file\n";
        std::cout << "6: Show countries with more than one official language\n";
        std::cout << "7: Show countries with a USD rate below a given value\n";
        std::cout << "8: Show countries in alphabetical order\n";
        std::cout << "0: Exit\n";

        k = readInt();

        switch (k) {

            case 1: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (fileExists(fileName)) {
                     std::cout << "File with the same name already exists.\n";
                      break;
                }

                createFile(fileName);
                std::cout << "\nFile " << fileName << " created successfully.\n";
                break;
            }

            case 2: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                std::cout << "Enter the number of states you want to add: ";
                int n = readInt();

                states = new State[n];

                inputStates(states, n);
                addRecordsToFile(fileName, states, n);

                std::cout << "\nRecords were saved successfully.\n";

                delete[] states;
                states = nullptr;
                
                break;
            }

            case 3: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                if (deleteFile(fileName)) 
                std::cout << "File deleted successfully.\n";
                else std::cout << "Error. Could not delete file.\n";

                break;
            }

            case 4: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                int n = countRecords(fileName);
                states = new State[n];
                readFile(fileName, states, n);

                std::cout << "Enter a number of records you want to remove: ";
                int m = readInt();
                char (*namesToDelete)[30] = new char[m][30];
                
                for (int i = 0; i < m; i++) {
                     std::cout << "Enter country name " << i + 1 << ": ";
                     readLine(namesToDelete[i], 30);
                }

                removeRecordsFromFile(fileName, states, n, namesToDelete, m);
                std::cout << "Records were processed successfully.\n";

                delete[] states;
                states = nullptr;
                delete[] namesToDelete;
                namesToDelete = nullptr;

                break;
            }

            case 5: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }
                
                int n = countRecords(fileName);
                states = new State[n];
                readFile(fileName, states, n);

                std::cout << "All records from the file:\n";
                printAllRecords(states, n);
                
                delete[] states;
                states = nullptr;

                break;
            }

            case 6: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                int n = countRecords(fileName);
                states = new State[n];
                readFile(fileName, states, n);

                std::cout << "Countries with more than one official language:\n";
                showCountriesWithMoreThanOneLanguage(states, n);
                
                delete[] states;
                states = nullptr;

                break;
            }

            case 7: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                int n = countRecords(fileName);
                states = new State[n];
                readFile(fileName, states, n);

                std::cout << "Enter the maximum USD rate: ";
                double userRate = readDouble();
                std::cout << "Countries with a USD rate below " << userRate << ":\n";
                showCountriesWithUsdRateBelow(states, n, userRate);
                
                delete[] states;
                states = nullptr;

                break;
            }

            case 8: {
                std::cout << "\nEnter a file name: ";
                readLine(fileName, 80);

                if (!fileExists(fileName)) {
                     std::cout << "Error: file does not exist.\n";
                      break;
                }

                int n = countRecords(fileName);
                states = new State[n];
                readFile(fileName, states, n);

                std::cout << "Countries in alphabetical order:\n";
                sortCountries(states, n);
                printAllRecords(states, n);
                
                delete[] states;
                states = nullptr;

                break;
            }

            default:
            std::cout << "Error: wrong menu option.\n";
            break;

            case 0:
                return 0;
        }
    }
}