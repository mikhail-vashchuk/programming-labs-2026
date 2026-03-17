#include <iostream>
#include <cstring>
#include <cctype>
#include <limits>

struct Movie
{
    char title[50];
    char director[50];
    char country[30];
    char location[30];
    double profit;
};

void printOneMovie(Movie movies[], int i)
{
    std::cout << "Title: " << movies[i].title;
    std::cout << "\nDirector: " << movies[i].director;
    std::cout << "\nCountry: " << movies[i].country;
    std::cout << "\nLocation: " << movies[i].location;
    std::cout << "\nProfit: " << movies[i].profit << " mln $" << std::endl;
}

void printAllMovies(Movie movies[], int n)
{
    std::cout << "\nCurrent list of movies:\n";
    for (int i = 0; i < n; i++)
    {
        std::cout << "\n" << i + 1 << ") ";
        printOneMovie(movies, i);
    }
}

void clearInputLine()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void readLine(char name[], int size)
{
    while (true)
    {
        std::cin.getline(name, size);

        if (std::cin.fail())
        {
            std::cout << "Error: the line is too long.\n";
            clearInputLine();
            continue;
        }

        if (strlen(name) == 0)
        {
            std::cout << "Error: a line can't be empty.\n";
            continue;
        }

        return;
    }
}

void searchAndPrintByDirector(Movie movies[], int n, char name[])
{
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(name, movies[i].director) == 0)
        {
            std::cout << j + 1 << ") ";
            printOneMovie(movies, i);
            std::cout << "\n";
            j++;
        }
    }

    if (j == 0)
    {
        std::cout << "No movies by this director were found.\n";
    }
}

double readDouble()
{
    double x;
    while (true)
    {
        if (std::cin >> x)
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cout << "Enter a number.\n";
        clearInputLine();
    }
}

void moviesByProfitAndLocation(Movie movies[], int n, double N)
{
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (movies[i].profit > N && strcmp(movies[i].location, "Hollywood") == 0)
        {
            std::cout << j + 1 << ") ";
            printOneMovie(movies, i);
            std::cout << "\n";
            j++;
        }
    }

    if (j == 0)
    {
        std::cout << "No movies were found.\n";
    }
}

void sortByTitle(Movie movies[], int n)
{
    for (int i = 1; i < n; i++)
    {
        Movie key = movies[i];
        int j = i - 1;

        while (j >= 0 && strcmp(movies[j].title, key.title) > 0)
        {
            movies[j + 1] = movies[j];
            j--;
        }

        movies[j + 1] = key;
    }
}

int readInt()
{
    int x;
    while (true)
    {
        if (std::cin >> x && (x >= 0 && x <= 4))
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return x;
        }
        std::cout << "Enter a digit between 0 and 4.\n";
        clearInputLine();
    }
}

int main()
{
    Movie movies[] =
    {
        {"New York, New York", "Martin Scorsese", "USA", "Hollywood", 16.4},
        {"Taxi Driver", "Martin Scorsese", "USA", "New York", 28.3},
        {"Raging Bull", "Martin Scorsese", "USA", "Hollywood", 23.4},
        {"Fight Club", "David Fincher", "USA", "Hollywood", 101.2},
        {"Se7en", "David Fincher", "USA", "Hollywood", 327.3},
        {"Once Upon a Time in Hollywood", "Quentin Tarantino", "USA", "Hollywood", 377.6},
        {"Inglourious Basterds", "Quentin Tarantino", "Germany", "Berlin", 321.5},
        {"The Dreamers", "Bernardo Bertolucci", "Italy", "Paris", 15.3},
        {"La Dolce Vita", "Federico Fellini", "Italy", "Rome", 19.5},
        {"Amelie", "Jean-Pierre Jeunet", "France", "Paris", 174.2}
    };

    printAllMovies(movies, 10);

    int choice;

    do
    {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1 - Show all movies\n";
        std::cout << "2 - Find movies by director\n";
        std::cout << "3 - Find movies with profit greater than N\n";
        std::cout << "4 - Sort movies by title\n";
        std::cout << "0 - Exit\n";
        std::cout << "Choose option: ";

        choice = readInt();

        switch (choice)
        {
            case 1:
                printAllMovies(movies, 10);
                break;

            case 2:
            {
                std::cout << "\nEnter director's name: ";
                char name[50];
                readLine(name, 50);
                std::cout << "\nAll movies made by " << name << ":\n";
                searchAndPrintByDirector(movies, 10, name);
                break;
            }

            case 3:
            {
                std::cout << "\nEnter N number of profit, and I will show all films that made more profit than this number: ";
                double N = readDouble();
                std::cout << "\nAll films that made more profit than " << N << " mln $ and were shot in Hollywood:\n";
                moviesByProfitAndLocation(movies, 10, N);
                break;
            }

            case 4:
                sortByTitle(movies, 10);
                std::cout << "Movies sorted alphabetically.\n";
                printAllMovies(movies, 10);
                break;

            case 0:
                std::cout << "Program finished.\n";
                break;

            default:
                std::cout << "Wrong option. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}