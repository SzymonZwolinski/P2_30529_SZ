#include <thread>
#include <cstdio>
#include <windows.h>
#include <random>
#include <functional>
std::default_random_engine generator;
std::uniform_int_distribution<int> distribution(1,10);
auto los = std::bind(distribution,generator);
thread_local unsigned int counter = 0;
//unsigned int counter_tab = 0;
thread_local unsigned int counter_tab =0;
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
void _random(int id)
{
    int tab[100];
    for(int i=0;i<100;i++)
    {
        tab[i] = los();
    }
    /*
    for(int i =0;i<100;i++)
    {
        printf("%u\n",tab[i]);
    }*/
    for(int i =(id)*10;i<(id+1)*10;i++)
    {
        counter_tab+=tab[i];
    }
      if(id==1)
    {

        printf("%u\n",counter_tab);
    }
     if(id==2)
    {

        printf("%u\n",counter_tab);
    }
     if(id==3)
    {

        printf("%u\n",counter_tab);
    }

    if(id==4)
    {

        printf("%u\n",counter_tab);
    }
     if(id==5)
    {

        printf("%u\n",counter_tab);
    }
     if(id==6)
    {

        printf("%u\n",counter_tab);
    }

    if(id==7)
    {

        printf("%u\n",counter_tab);
    }
     if(id==8)
    {

        printf("%u\n",counter_tab);
    }
     if(id==9)
    {

        printf("%u\n",counter_tab);
    }

    if(id==10)
    {

        printf("%u\n",counter_tab);
    }
}

int main(){

    //std::thread t1(increment,1);
    //std::thread t2(increment,2);

    std::thread t1(_random,1);
    std::thread t2(_random,2);
    std::thread t3(_random,3);
    std::thread t4(_random,4);
    std::thread t5(_random,5);
    std::thread t6(_random,6);
    std::thread t7(_random,7);
    std::thread t8(_random,8);
    std::thread t9(_random,9);
    std::thread t10(_random,10);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();

    return 0;
}
