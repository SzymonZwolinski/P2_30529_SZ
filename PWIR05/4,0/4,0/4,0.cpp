#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <time.h>

#define MATRIX_H 10000
#define MATRIX_W 10000
#define MATRIX 10000
//operators
//+
//-
//*
//&
//|
//^
//&&
//||

uint8_t** matrix;
uint8_t* wektor;
uint32_t sumMatrix() {
    uint32_t sum = 0;

    for (uint32_t i = 0; i < MATRIX_H; i++) {
        for (uint32_t k = 0; k < MATRIX_W; k++) {
            sum += matrix[i][k];
        }
    }

    return sum;
}

uint32_t sumMatrixParallel() {
    uint32_t sum = 0;
    int32_t i;
    int32_t k;

#pragma omp parallel for shared(matrix) private(i, k)
    for (i = 0; i < MATRIX_H; i++) {
        for (k = 0; k < MATRIX_W; k++) {
            sum = sum + matrix[i][k];
        }
    }

    return sum;
}

uint32_t WektorLen()
{
    int32_t length = 0;
    for (int i = 0; i < MATRIX ;i++)
    {
        length += wektor[i];
    }
    return length;
}
uint32_t WektorLenpar()
{
    int32_t length = 0;
    int i;
#pragma omp parallel for shared(matrix) private(i) reduction(+:length)
    for (i = 0; i < MATRIX; i++)
    {
        length += wektor[i];
    }
    return length;
}
int main() {
    srand(time(NULL));

    //alloc matrix
    matrix = (uint8_t**)new uint8_t * [MATRIX_H];
    wektor = (uint8_t*)new uint8_t * [MATRIX];
    for (uint32_t i = 0; i < MATRIX_H; i++)
        matrix[i] = new uint8_t[MATRIX_W];

    //fill matrix random data normal way
    for (uint32_t i = 0; i < MATRIX_H; i++) {
        for (uint32_t k = 0; k < MATRIX_W; k++) {
            matrix[i][k] = (uint16_t)(rand() % 10);
        }
    }

    for (uint32_t i= 0; i < MATRIX; i++)
    {
        wektor[i] = (uint16_t)(rand() % 11);
    }

    auto start = std::chrono::high_resolution_clock::now();
    uint32_t sum = sumMatrix();
    auto end = std::chrono::high_resolution_clock::now();

    printf("Sum calculated normal way: %u in time: %llu ms\r\n", sum,
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();
    sum = sumMatrixParallel();
    end = std::chrono::high_resolution_clock::now();

    printf("Sum calculated parralel way: %u in time: %llu ms\r\n", sum,
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    //
     start = std::chrono::high_resolution_clock::now();
     sum = WektorLen();
     end = std::chrono::high_resolution_clock::now();

    printf("Wektor normalnie: %u in time: %llu ms\r\n", sum,
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    start = std::chrono::high_resolution_clock::now();
    sum = WektorLenpar();
    end = std::chrono::high_resolution_clock::now();

    printf("Wektor parralel: %u in time: %llu ms\r\n", sum,
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());


    for (uint32_t i = 0; i < MATRIX_H; i++) delete[] matrix[i];
    delete[] matrix;

  
   delete[] wektor;
    
    return 0;
}