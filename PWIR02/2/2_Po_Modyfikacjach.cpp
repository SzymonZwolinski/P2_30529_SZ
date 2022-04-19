#include <cstdio>
#include <thread>
#include <windows.h>
#include <iostream>
#include <vector>

void action(int id) {
    printf("Uruchamiam watek %d\n", id);
    Sleep(5 * 1000); //5 sekund
    printf("Koncze watek %d\n", id);
}

int main() {
    int thread_count;
    std::cout << "Podaj ilosc watkow: ";
    std::cin >> thread_count;

    //alokacja tablicy, ktĂłra bÄ™dzie przechowywaÄ‡ wskaĹşniki na wÄ…tki
    std::vector<std::thread*>threads;// = new std::thread * [thread_count];
    threads.resize(thread_count);

    //otwieranie wÄ…tkĂłw
    for (int i = 0; i < thread_count; i++) {
        threads.at(i) = new std::thread(action, i); //wykorzystuje i jako id danego wÄ…tku
    }

    //watki pracujÄ…, ale trzeba je zsynchronizowaÄ‡
    for (int i = 0; i < thread_count; i++) {
        threads.at(i)->join();
    }

    //alokowaliĹ›my pamiÄ™Ä‡ wiÄ™c pasuje jÄ… zwolniÄ‡
    for (int i = 0; i < thread_count; i++) {
        delete threads.at(i);
    }
    threads.~vector();

    printf("Koniec programu \r\n");

    return 0;
}