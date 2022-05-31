#include "mpi.h"
#include <iostream>

int main(int argc, char* argv[])
{
	int id, count;
	MPI_Init(&argc, &argv);

	//pobranie id oraz ilo�ci proces�w do zmiennych
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &count);

	//kod procesu komunikuj�cego si� z u�ytkownikiem
	if (id == 0) {
		int iteration = 0;
		std::cout << "Podaj ilosc iteracji: " << std::endl;
		std::cin >> iteration;

		MPI_Bcast(&iteration, 1, MPI_INT, 0, MPI_COMM_WORLD); //proces 0 jest nadawc�

		int* results = new int[count - 1];
		MPI_Request* requests = new MPI_Request[count - 1];
		MPI_Status* statuses = new MPI_Status[count - 1];

		//wywo�ujemy nas�uch od ka�dego procesu opr�cz samego siebie
		//asynchroniczne wywo�anie pozwoli uruchomi� nas�uch dla ka�dego
		//procesu bez potrzeby czekania na dane od poprzednika
		for (int32_t i = 0; i < count - 1; i++) {
			MPI_Irecv(&results[i], 1, MPI_DOUBLE, i + 1, 0, MPI_COMM_WORLD, &requests[i]);
		}
		MPI_Waitall(count - 1, requests, statuses);//oczekuje

		//tu mo�na by by�o co� zrobi� z tymi danymi
		//ale to tylko przyk�ad

		printf("Koniec\r\n");

		delete[] results;
		delete[] requests;
		delete[] statuses;
	}
	//kod proces�w wynokuj�cych jakie� dzia�ania
	else {
		int iteration = 0;

		MPI_Bcast(&iteration, 1, MPI_INT, 0, MPI_COMM_WORLD); //pozosta�e procesy czekaj� tu a� P0 nada warto��

		//jakie� operacje
		for (int i = 0; i < iteration; i++) {
			//cos tam
		}

		int dane = 1;
		MPI_Send(&dane, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}