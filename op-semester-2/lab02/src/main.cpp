#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <random>
#include <limits>

void clearInputLine() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
} 

// ============================
// Random integer generator
// ============================

int generateRandom(int min, int max)
{
    // use an integer distribution for whole numbers
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

// ============================
// Form matrix
// ============================

int** formMatr(int size_row, int size_col) 
{
  int** matr = new int*[size_row];
  for (int i = 0; i < size_row; i++) matr[i] = new int[size_col];
  return matr;
}

// ============================
// Fill matrix
// ============================

void fillMatr(int** matr, int size_row, int size_col, int min, int max) 
{
  for (int i = 0; i < size_row; i++)
    for (int j = 0; j < size_col; j++) {
      matr[i][j] = generateRandom(min, max);
    }
}

// ============================
// Print matrix
// ============================

void printMatrix(int** matr, int size_row, int size_col) 
{
  for (int i = 0; i < size_row; i++) {
    for (int j = 0; j < size_col; j++) 
    std::cout << std::setw(5) << matr[i][j];
    std::cout << "\n";
  }
  std::cout << "\n";
}

// ============================
// Delete matrix
// ============================

void deleteMatr(int** matr, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matr[i];
    }
    delete[] matr;
}

// ============================
// Task 2.2. Find element with maximum value, swap the first row with the row that contains this element
// ============================

void maxElementFinderAndSwapper (int** matr, int size_row, int size_col)
{
    int maxIndex;
    int maxElement = std::numeric_limits<int>::lowest();
    for (int i = 0; i < size_row; i++) {
        for (int j = 0; j < size_col; j++) {
            if (matr[i][j] > maxElement) 
            {
                maxElement = matr[i][j];
                maxIndex = i;
            }
        }
    }
    std::cout << "Maximum element: " << maxElement << "\n";
    std::cout << "Maximum Index: " << maxIndex + 1 << "\n";

// swap
    int t;
    for (int j = 0; j < size_col; j++) {
        t = matr[0][j];
        matr[0][j] = matr[maxIndex][j];
         matr[maxIndex][j] = t;
    }

}

// ============================
// Task 2.3. Add K number of rows before the matrix
// ============================

int** addKRows (int** matr, int size_row, int size_col, int K)
{
    int** modifiedMatr = new int*[size_row];
    for (int i = 0; i < size_row; i++) modifiedMatr[i] = new int[size_col];

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < size_col; j++) 
        {
        modifiedMatr[i][j] = generateRandom(-100, 100);
        }
    }

    for (int i = K; i < size_row; i++) {
        for (int j = 0; j < size_col; j++) 
        {
            modifiedMatr [i][j] = matr [i-K][j];
        }
    }

    return modifiedMatr;
}

// ============================
// Task 2.3. Add K number of rows before the matrix
// ============================

int** addLColumns (int** matr, int size_row, int size_col, int L)
{
    int** modifiedMatr = new int*[size_row];
    for (int i = 0; i < size_row; i++) modifiedMatr[i] = new int[size_col];

    for (int i = 0; i < size_row; i++) {
        for (int j = 0; j < L; j++) 
        {
        modifiedMatr[i][j] = generateRandom(-100, 100);
        }
    }

    for (int i = 0; i < size_row; i++) {
        for (int j = L; j < size_col; j++) 
        {
            modifiedMatr [i][j] = matr [i][j-L];
        }
    }

    return modifiedMatr;
}

// ============================
// Read Int for task 2.3
// ============================

int readInt ()
{
    int K;
    while (true) {
        if (std::cin >> K) return K;
        std::cout << "Error. Enter a digit.\n";
        clearInputLine();
    }
}

// ============================
// Task 2.4. Fill the part of your matrix according to the task and sort it
// ============================

bool inArea (int i, int j, int size_row, int size_col) 
{
            if ((j >= i && j < size_col/2) || (j >= size_col/2 && i >= j))
        {
            return true;
        }
        else return false;
}

void fillAndSortMatrix(int** matr, int size_row, int size_col, int variant) 
{
    for (int i = 0; i < size_row; i++) {
        for (int j = 0; j < size_col; j++) {
            if (!(inArea(i, j, size_row, size_col))) {
                matr[i][j] = variant;
            }
        }
    }

    int temporary;

    for (int o = 0; o < size_row; o++) {
        for (int k = 0; k < size_col; k++) {
            if (!(inArea(o, k, size_row, size_col))) continue;

            int minRow = o;
            int minCol = k;

            for (int i = 0; i < size_row; i++) {
                for (int j = 0; j < size_col; j++) {
                    if (!(inArea(i, j, size_row, size_col))) continue;
                    if ((i > o) || (j > k && i == o))
                        if (matr[i][j] < matr[minRow][minCol]) {
                            minRow = i;
                            minCol = j;
                        }
                }
            }

            temporary = matr[o][k];
            matr[o][k] = matr[minRow][minCol];
            matr[minRow][minCol] = temporary;
        }
    }
}

// ============================
// main
// ============================

int main() 
{
    int size_row = 7, size_col = 8;
    int** matr = formMatr(size_row, size_col);

    fillMatr(matr, size_row, size_col, -100, 100);
    printMatrix(matr, size_row, size_col);

    std::cout << "\n";

    //Taks 2.2
    maxElementFinderAndSwapper (matr, size_row, size_col);
    printMatrix(matr, size_row, size_col);

    //Task 2.3.1
    std::cout << "Enter K number of rows: ";
    int K = readInt();

    int oldSize_row = size_row;
    size_row = size_row + K;
    int ** modifiedMatrRows = addKRows (matr, size_row, size_col, K);

    deleteMatr(matr, oldSize_row);
    matr = modifiedMatrRows;

    printMatrix(matr, size_row, size_col);

    //Task 2.3.2
    std::cout << "Enter L number of columns: ";
    int L = readInt();

    int oldSize_col = size_col;
    size_col = size_col + L;
    int ** modifiedMatrColumns = addLColumns (matr, size_row, size_col, L);

    deleteMatr(matr, size_row);
    matr = modifiedMatrColumns;

    printMatrix(matr, size_row, size_col);

    //Task 2.4
    std::cout << "Enter preferred digit (variant) and see magic happen: ";
    int variant = readInt();

    fillAndSortMatrix (matr, size_row, size_col, variant);
    printMatrix(matr, size_row, size_col);

    return 0;
}