#include <iostream>
#include <iomanip>
#include <random>
#include <limits>

// ============================================================
// Input utilities
// ============================================================

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

int readMenu()
{
    int value;
    while (true)
    {
        std::cout << "\nEnter your choice (0-3): ";
        if (std::cin >> value && (value >= 0 && value <= 3))
        {
            return value;
        }

        std::cout << "Error: please enter 0, 1, 2 or 3.\n";
        clearInputLine();
    }
}

int readK()
{
    int k;
    while (true)
    {
        std::cout << "\nEnter K: ";
        if (std::cin >> k)
        {
            return k;
        }

        std::cout << "Error: please enter a number.\n";
        clearInputLine();
    }
}

// ============================================================
// Random generator
// ============================================================

int generateRandom(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// ============================================================
// Array creation / printing
// ============================================================

int* fillRandom(int size)
{
    int* arr = new int[size];

    for (int i = 0; i < size; ++i)
    {
        *(arr + i) = generateRandom(-100, 100);
    }

    return arr;
}

void printArray(const int* arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        std::cout << "[" << (i + 1) << "] "
                  << std::setw(8) << arr[i] << "\n";
    }
    std::cout << std::endl;
}

// ============================================================
// Task 1: Remove all negative two-digit elements [-99; -10]
// ============================================================

void removeNegativeTwoDigit(int*& arr, int& size)
{
    int newSize = 0;

    for (int i = 0; i < size; ++i)
    {
        if (-99 <= *(arr + i) && *(arr + i) <= -10) continue;
        ++newSize;
    }

    int* arr2 = new int[newSize];

    int j = 0;
    for (int i = 0; i < size; ++i)
    {
        if (-99 <= *(arr + i) && *(arr + i) <= -10) continue;
        *(arr2 + j) = *(arr + i);
        ++j;
    }

    delete[] arr;
    arr = arr2;
    size = newSize;
}

// ============================================================
// Prime check (used for Task 2)
// ============================================================

bool isPrime(int x)
{
    if (x < 2) return false;

    int d = 2;
    while (d * d <= x)
    {
        if (x % d == 0) return false;
        ++d;
    }

    return true;
}

// ============================================================
// Task 2: Add K prime numbers to the beginning of the array
// ============================================================

void addKPrimesToFront(int*& arr, int& size, int k)
{
    int newSize = size + k;
    int* arr2 = new int[newSize];

    int candidate = 2;

    // Fill the first k elements with prime numbers
    for (int j = 0; j < k; ++j)
    {
        while (!isPrime(candidate))
        {
            ++candidate;
        }
        *(arr2 + j) = candidate;
        ++candidate;
    }

    // Copy the old array after the inserted primes
    int i = 0;
    for (int j = k; j < newSize; ++j)
    {
        *(arr2 + j) = *(arr + i);
        ++i;
    }

    delete[] arr;
    arr = arr2;
    size = newSize;
}

// ============================================================
// Task 3: Insert 0 after every even element
// ============================================================

void insertZeroAfterEven(int*& arr, int& size)
{
    int newSize = size;

    for (int i = 0; i < size; ++i)
    {
        if (*(arr + i) % 2 == 0) ++newSize;
    }

    int* arr2 = new int[newSize];

    int j = 0;
    for (int i = 0; i < size; ++i)
    {
        *(arr2 + j) = *(arr + i);
        ++j;

        if (*(arr + i) % 2 == 0)
        {
            *(arr2 + j) = 0;
            ++j;
        }
    }

    delete[] arr;
    arr = arr2;
    size = newSize;
}

// ============================================================
// Main
// ============================================================

int main()
{
    int size = 22;
    int* arr = fillRandom(size);

    std::cout << "Input array:\n";
    printArray(arr, size);

    std::cout << "Menu:\n\n";
    std::cout << "1) Remove all negative two-digit elements ([-99; -10]).\n";
    std::cout << "2) Add K prime numbers to the beginning (K is entered from keyboard).\n";
    std::cout << "3) Insert 0 after every even element.\n";
    std::cout << "0) Quit.\n";

    const int variant = readMenu();

    switch (variant)
    {
        case 1:
            std::cout << "\nResult:\n";
            removeNegativeTwoDigit(arr, size);
            printArray(arr, size);
            pauseConsole();
            break;

        case 2:
        {
            const int k = readK();
            std::cout << "\nResult:\n";
            addKPrimesToFront(arr, size, k);
            printArray(arr, size);
            pauseConsole();
            break;
        }

        case 3:
            std::cout << "\nResult:\n";
            insertZeroAfterEven(arr, size);
            printArray(arr, size);
            pauseConsole();
            break;

        case 0:
            std::cout << "Exiting...\n";
            break;
    }

    delete[] arr;
    return 0;
}