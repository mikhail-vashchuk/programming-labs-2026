#include <iostream>
#include <limits>
#include <cctype>

void clearInputLine() 
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void pauseConsole()
{
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int readInt() 
{
    int value;
    while (true) {
        std::cout << "\nEnter your choice (0-4): ";
        if (std::cin >> value && (value >= 0 && value <= 4)) 
        {
            return value;
        } 
        else 
        {
            std::cout << "Error: please enter 0, 1, 2, 3 or 4.\n";
            clearInputLine();
        }
    }
}

int countWords(const char* line) 
{
    int count = 0;
    bool inWord = false;

    for (size_t i = 0; line[i] != '\0'; ++i) 
    {
        if (std::isspace(line[i])) 
        {
            inWord = false;
        } 
        else if (!inWord) 
        {
            inWord = true;
            ++count;
        }
    }

    return count;
}

void changeLine(char* line) 
{
    clearInputLine();
    std::cin.getline(line, 256);
}

int shortestWordLength(const char* line)
{
    int currentLength = 0;
    int minLength = std::numeric_limits<int>::max();

    for (size_t i = 0; line[i] != '\0'; ++i)
    {
        if (std::isspace(static_cast<unsigned char>(line[i])))
        {
            if (currentLength > 0 && currentLength < minLength)
                minLength = currentLength;

            currentLength = 0;
        }
        else
        {
            currentLength++;
        }
    }

    if (currentLength > 0 && currentLength < minLength)
        minLength = currentLength;

    return minLength;
}

int longestWordLength(const char* line) 
{
    int currentLength = 0;
    int maxLength = 0;

    for (size_t i = 0; line[i] != '\0'; ++i)
    {
        if (std::isspace(static_cast<unsigned char>(line[i])))
        {
            if (currentLength > maxLength)
                maxLength = currentLength;

            currentLength = 0;
        }
        else
        {
            currentLength++;
        }
    }

    if (currentLength > maxLength)
        maxLength = currentLength;

    return maxLength;
}

int main() 
{
    char line[256] = "We study C++ programming language first semester.";

     while (true) 
     {
        std::cout << "\nOur line:\n";
        std::cout << line << "\n\n";

        std::cout << "Menu:\n\n";
        std::cout << "1) Word count in the line\n";
        std::cout << "2) The length of the shortest word in the line\n";
        std::cout << "3) The length of the longest word in the line\n";
        std::cout << "4) Change the line\n";
        std::cout << "0) Quit.\n";

        int variant = readInt();

        switch (variant) 
        {
            case 1:
                std::cout << "Word count: " << countWords(line) << "\n";
                pauseConsole();
                break;
            case 2:
                std::cout << "Length of the shortest word: " << shortestWordLength(line) << "\n";
                pauseConsole();
                break;
            case 3:
                std::cout << "Length of the longest word: " << longestWordLength(line) << "\n";
                pauseConsole();
                break;
            case 4:
                std::cout << "Enter a new line:\n";
                changeLine(line);   
                pauseConsole();
                break;  
            case 0:
                std::cout << "Exiting...\n";
                return 0;
        }

    }
    return 0;
}
