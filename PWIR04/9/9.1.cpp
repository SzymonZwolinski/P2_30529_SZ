#include <thread>
#include <cstdio>
#include <windows.h>
#include <random>
#include <functional>
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1,10);
auto los = std::bind(distribution,generator);
thread_local unsigned int counter = 0;

void increment(int id){
    for(int i = 0;i<10;i++){
        counter++;
        Sleep(300);
    }

    //ten blok wykona się tylko raz mimo, że wątków jest więcej
    if(id == 1){
        printf("%u\n", counter);
    }
}
void _random()
{
    int tab[100];
    for(int i=0;i<100;i++)
    {
        tab[i] = los();
    }
    for(int i =0;i<100;i++)
    {
        printf("%u\n",tab[i]);
    }


}

int main(){

    std::thread t1(increment,1);
    std::thread t2(increment,2);
    std::thread t3(_random);
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
