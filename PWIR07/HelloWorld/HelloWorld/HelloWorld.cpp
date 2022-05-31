#include "mpi.h"
#include <iostream>

int main(int argc, char* argv[])
{
	int id, count;
	MPI_Init(&argc, &argv);

	//pobranie id oraz iloœci procesów do zmiennych
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &count);

	//kod procesu komunikuj¹cego siê z u¿ytkownikiem
	if (id == 0) {
		int iteration = 0;
		std::cout << "Podaj ilosc iteracji: " << std::endl;
		std::cin >> iteration;

		MPI_Bcast(&iteration, 1, MPI_INT, 0, MPI_COMM_WORLD); //proces 0 jest nadawc¹

		int* results = new int[count - 1];
		MPI_Request* requests = new MPI_Request[count - 1];
		MPI_Status* statuses = new MPI_Status[count - 1];

		//wywo³ujemy nas³uch od ka¿dego procesu oprócz samego siebie
		//asynchroniczne wywo³anie pozwoli uruchomiæ nas³uch dla ka¿dego
		//procesu bez potrzeby czekania na dane od poprzednika
		for (int32_t i = 0; i < count - 1; i++) {
			MPI_Irecv(&results[i], 1, MPI_DOUBLE, i + 1, 0, MPI_COMM_WORLD, &requests[i]);
		}
		MPI_Waitall(count - 1, requests, statuses);//oczekuje

		//tu mo¿na by by³o coœ zrobiæ z tymi danymi
		//ale to tylko przyk³ad

		printf("Koniec\r\n");

		delete[] results;
		delete[] requests;
		delete[] statuses;
	}
	//kod procesów wynokuj¹cych jakieœ dzia³ania
	else {
		int iteration = 0;

		MPI_Bcast(&iteration, 1, MPI_INT, 0, MPI_COMM_WORLD); //pozosta³e procesy czekaj¹ tu a¿ P0 nada wartoœæ

		//jakieœ operacje
		for (int i = 0; i < iteration; i++) {
			//cos tam
		}

		int dane = 1;
		MPI_Send(&dane, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Finalize();
	return 0;
}