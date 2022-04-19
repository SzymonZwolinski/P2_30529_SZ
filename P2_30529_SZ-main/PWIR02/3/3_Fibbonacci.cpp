#include <chrono>
#include <cstdio>
#include <windows.h>
#include <iostream>
void fibonacci(int n)
{
    long long a = 0, b = 1;

    for (int i = 0; i < n; i++)
    {
        std::cout << b << std::endl;
        b += a; //pod zmienną b przypisujemy wyraz następny czyli a+b
        a = b - a; //pod zmienną a przypisujemy wartość zmiennej b
    }
}
int main() {
    auto start = std::chrono::steady_clock::now();
    //dĹ‚ugie operacje
    //Sleep(2000);
    fibonacci(40);
    
    

    auto end = std::chrono::steady_clock::now();

    printf("Czas trwania: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    return 0;
}