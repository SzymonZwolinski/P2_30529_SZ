#include <iostream>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <assert.h>
#include <windows.h>
#include <omp.h>
#include <vector>
#include <cmath>

using namespace std;

void wait(int x) {
    Sleep(x);
}

vector<double> wspolrzedne_A(double x1, double y1)
{
    vector<double> A;
    A.push_back(x1);
    A.push_back(y1);
    return A;
}

vector<double> wspolrzedne_B(double x2, double y2)
{
    vector<double> B;
    B.push_back(x2);
    B.push_back(y2);
    return B;
}

vector<double> wspolrzedne_wektora(vector<double> (*A)(double, double), vector<double> (*B)(double, double), double x1, double y1, double x2, double y2)
{
    try {
        if (A(x1, y1).size() != 2 || B(x2, y2).size() != 2) throw 1;
        vector<double> AB;
        AB.push_back(A(x1, y1)[0] - B(x2, y2)[0]);
        AB.push_back(A(x1, y1)[1] - B(x2, y2)[1]);
        return AB;
    }
    catch (int x) {
        cout << "wyjatek "<< x << " dlugosc wektora inna od 2";
    }
}

double dlugosc_wektora(vector<double>(*A)(double, double), vector<double>(*B)(double, double), double x1, double y1, double x2, double y2)
{
    try {
        if (A(x1, y1).size() != 2 || B(x2, y2).size() != 2) throw 2;
        vector<double> ab;
        ab.push_back(A(x1, y1)[0] - B(x2, y2)[0]);
        ab.push_back(A(x1, y1)[1] - B(x2, y2)[1]);
        if (ab.size() != 2) throw 3;

        double dlugosc = sqrt(ab[0] * ab[0] + ab[1] * ab[1]);
        cout << endl << "dlugosc wektora =" << dlugosc << endl;
        return dlugosc;
    }
    catch (int x) {
        cout << "wyjatek " << x << " dlugosc wektora inna od 2";
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel num_threads(4) default(shared)
    {
#pragma omp sections
        {
#pragma omp section
            {
                wspolrzedne_A(-3, 8);
                wait(1000);
            }
#pragma omp section
            {
                wspolrzedne_B(5, 2);
                wait(1000);
            }
#pragma omp section
            {
                wspolrzedne_wektora(&wspolrzedne_A, &wspolrzedne_B, -3, 8, 5, 2);
                wait(2000);
            }
#pragma omp section
            {
                dlugosc_wektora(&wspolrzedne_A, &wspolrzedne_B, -3, 8, 5, 2);
                wait(2000);
            }
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    printf("Parallel normal way %llu ms\r\n",
        std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());

    return 0;
}
