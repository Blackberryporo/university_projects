#include <iostream>
#include <string>
#include <utility>

std::string *getNames(int countNames)
{
    std::string *names = new (std::nothrow) std::string[countNames];
    if (!names)
    {
        std::cout << "Could not allocate memory for array";
        return nullptr;
    }

    for (int i = 0; i < countNames; ++i)
    {
        std::cout << "Enter name #" << i+1 << ": ";
        std::cin >> names[i];
        if (std::cin.fail())
            std::cin.clear();
        std::cin.ignore(32767,'\n');
    }

    return names;
}

void printNames(std::string *names, int count)
{
    for (int i = 0; i < count; ++i)
        std::cout << "Name #" << i+1 << ": " << names[i] << std::endl;
}

std::string *sortNames(std::string *names, int count)
{
    int firstNameIndex;
    for (int i = 0; i < count; ++i)
    {
        firstNameIndex = i;
        for (int j = i; j < count; ++j)
        {
            if (names[j] < names[firstNameIndex])
                firstNameIndex = j;
        }

        std::swap(names[i], names[firstNameIndex]);
    }
    return names;
}

int main()
{
    std::cout << "This program takes an array of strings (names) as input, "
            "sort them in the alphabet order and prints sorted names." << std::endl;

    std::cout << "How many names would you like to enter? ";
    int countNames;
    std::cin >> countNames;
    if (std::cin.fail())
        std::cin.clear();
    std::cin.ignore(32767,'\n');

    std::string *names = getNames(countNames);
    if (!names)
        return 1;

    names = sortNames(names, countNames);
    std::cout << "Here is your sorted list:" << std::endl;
    printNames(names, countNames);

    delete[] names;
    names = nullptr;

    return 0;
}
