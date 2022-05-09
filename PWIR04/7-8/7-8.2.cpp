#include <thread>
#include <cstdio>
#include <windows.h>
#include <mutex>

std::mutex counter_mutex;
unsigned int counter = 0;

void increment(){
    for(;;){
        counter_mutex.lock();
        counter++;
        if(counter==5)
        {
            counter_mutex.unlock();
            break;
        }
        counter_mutex.unlock();
        Sleep(2000);

    }
}

void parity(){
    for(;;){
            if(counter==5)
            {
                break;
            }
        counter_mutex.lock();
        if (counter % 2){
            printf("%u jest nieparzyste\r\n", counter);
        }
        else{
            printf("%u jest parzyste\r\n", counter);
        }
        counter_mutex.unlock();
        Sleep(2000);
    }
}

int main(){
    std::thread inc(increment);
    std::thread par(parity);

    inc.join();
    par.join();

    printf("Done\r\n");

    return 0;
}
