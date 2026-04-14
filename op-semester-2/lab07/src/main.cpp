#include <iostream>
#include <cstring>
#include <limits>

void clearInputLine() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void readLine(char *phrase, int size) {
    while (true) {
        std::cin.getline(phrase, size);

        if (std::cin.fail()) {
            std::cout << "Error. The line is too long.\n";
            clearInputLine();
            continue;
        }

        if (strlen(phrase) == 0) {
            std::cout << "Error. The line is empty.\n";
            continue;
        }

        break;
    }
}

bool isLatinLetter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

void countLatinLetters(const char *phrase, int index, int &count) {
    if (phrase[index] == '\0') {
        return;
    }
    if (isLatinLetter(phrase[index])) {
        count++;
    }
countLatinLetters(phrase, index + 1, count);
}

int main() {
    char phrase [128];
    std::cout << "Enter a line of text: ";
    readLine(phrase, sizeof(phrase));

    std::cout << "Latin letters in the line: ";
    int count = 0;
    countLatinLetters(phrase, 0, count);
    std::cout << count << std::endl;

return 0;
}