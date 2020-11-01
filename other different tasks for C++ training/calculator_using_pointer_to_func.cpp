#include <iostream>

char chooseOperation()
{
    char operationType;
    do
    {
        std::cout << "\nPlease enter operation (+, -, * or /): ";
        std::cin >> operationType;
    }
    while (operationType != '+' && operationType != '-' &&
            operationType != '*' && operationType != '/');

    return operationType;
}

int getInteger()
{
   std::cout << "Enter an integer: ";
   int integerValue;
   std::cin >> integerValue;
   if (std::cin.fail())
        std::cin.clear();
   std::cin.ignore(32767, '\n');

   return integerValue;
}

int add(int x, int y)
{
    return x + y;
}

int subtract(int x, int y)
{
    return x - y;
}

int divide(int x, int y)
{
    return x / y;
}

int multiply(int x, int y)
{
    return x * y;
}
/* Realization using switch-case, without struct and static array:

arithmeticFcn getArithmeticFcn(char operationType)
{
    switch(operationType)
    {
    default: //"add" is stated by default
    case '+':
        return add;
    case '-':
        return subtract;
    case '*':
        return multiply;
    case '/':
        return divide;
    }
}
*/

typedef int (*arithmeticFcn)(int, int);

struct arithmeticStruct
{
    char operationType;
    arithmeticFcn func;
};

static arithmeticStruct arithmeticArray[]{
    {'+', add},
    {'-', subtract},
    {'*', multiply},
    {'/', divide}
};

arithmeticFcn getArithmeticFcn(char operation)
{
    for (auto &element : arithmeticArray)
    {
        if (element.operationType == operation)
            return element.func;
    }

    return arithmeticArray[0].func; //"add" by default
}

int main()
{
    int x = getInteger();
    int y = getInteger();;
    char operatinType = chooseOperation();

    arithmeticFcn func = getArithmeticFcn(operatinType);

    std::cout << x << " " << operatinType << " " << y << " = " << func(x,y);
}
