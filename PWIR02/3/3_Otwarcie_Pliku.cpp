#include <chrono>
#include <cstdio>
#include <windows.h>
#include <fstream>  

int main() {
    auto start = std::chrono::steady_clock::now();
    //dĹ‚ugie operacje
    //Sleep(2000);
    std::fstream fs;
    fs.open ("test.txt");
    if (fs.is_open())
    {
        printf("Otworzono plik");
        fs.close();
    }
    

    auto end = std::chrono::steady_clock::now();

    printf("Czas trwania: %llu\n", std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    return 0;
}