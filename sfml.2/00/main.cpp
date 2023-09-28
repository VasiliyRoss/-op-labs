#include <iostream>

int main()
{
    // в цикле от 1 до 100

    for (int num = 1; num <= 100; num++)
    {
        if ((num % 3 == 0) && (num % 5 == 0))
        {
            std::cout << "FizzBuzz" << std::endl;
        }
        else if (num % 3 == 0)
        {
            std::cout << "Fizz" << std::endl;
        }
        else if (num % 5 == 0)
        {
            std::cout << "Buzz" << std::endl;
        }
        else
        {
            std::cout << num << std::endl;
        }
        //  - если число кратно и 3, и 5, вывести FizzBuzz
        //  - иначе если число кратно 3, вывести Fizz
        //  - иначе если число кратно 5, вывести Buzz
        //  - иначе вывести число
    }
}