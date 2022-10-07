#include <iostream>

#include "stack.h"

int main ()
{
    my_containers::stack<int> stack {};

    long int num = 0;
    std::cin >> num;

    for (int i = 1; i < num + 1; i++)
        stack.push (i);

    long int sum = 0;
    for (int i = 1; i < num + 1; i++)
    {
        sum += stack.top ();
        stack.pop ();
    }

    std::cout << "полученная сумма: " << sum << '\n';
    std::cout << "должно получиться: " << num * (num + 1) / 2 << '\n';

    return 0;
}
