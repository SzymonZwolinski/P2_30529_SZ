#include <cstdio>
#include <thread>
#include <windows.h>
#include <iostream>

int action(int id, int czas) {
    printf("Uruchamiam watek %d\n", id);
    std::cout << "spie: " << czas / 1000 << "sekund\n";
    Sleep(czas); //10*1000 = 10 sekund
    printf("Koncze watek %d\n", id);
    //std::cout << "id watku: " << std::this_thread::get_id() << std::endl<<std::endl;
    return 0;
}


int main() {
    //tworzenie wÄ…tku
    int podCzas;
    std::cout << "Podaj czas uspienia watku 1:\n";
    std::cin >> podCzas;

    std::thread t1(action, 1, podCzas); //konstruktor klasy t1 przyjmuje minimum wskaĹşnik na funckje do wykonania
    std::cout << "Podaj czas uspienia watku 2:\n";
    std::cin >> podCzas;

    std::thread t2(action, 2,podCzas); //funckja ta moĹĽe coĹ› zwracaÄ‡, ale moĹĽe zwaracaÄ‡ teĹĽ void
    std::cout << "Podaj czas uspienia watku 3:\n";
    std::cin >> podCzas;
    std::thread t3(action, 3,podCzas); //dalsze parametry zostanÄ… przekazane do podanej funckji
    
    

    t1.join();  //synchronizacja
    t2.join();  //wÄ…tek gĹ‚Ăłwny ma tu poczekaÄ‡ na te 3 wÄ…tki
    t3.join();  //inaczej program by siÄ™ zakoĹ„czyĹ‚ wczeĹ›niej bo wÄ…tki trwajÄ… minimum 10 sekund

    printf("Koniec programu \r\n");

    return 0;
}