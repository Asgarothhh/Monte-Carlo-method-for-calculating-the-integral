#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

const int SIZE = 5;

double f(double x)
{
    return x / (1 + pow(x, 2));
}

double monteCarloIntegralSolver(double xMin, double xMax, double yMin, double yMax, int N)
{
    int inBox = 0;
    for (int i = 0; i < N; i++)
    {
        double rnd1 = (double)rand() / (double)RAND_MAX;
        double rnd2 = (double)rand() / (double)RAND_MAX;

        double xCoord = xMin + rnd1 * (xMax - xMin);
        double yCoord = yMin + rnd2 * (yMax - yMin);

        double value = f(xCoord);

        if (value >= yCoord)
            inBox++;
    }

    double density = (double)inBox / N;
    return (xMax - xMin) * (yMax - yMin) * density;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int N[SIZE] = { 100, 500, 1000, 3000, 10000 };
    double trapezoidMethod[SIZE] = { 0.458046, 0.45812, 0.458141, 0.458144, 0.458145 };
    double error[SIZE];
    double integralValue[SIZE];
    double xMin, xMax, yMin=0, yMax;
    cout << "\tВычисление значения интеграла методом Монте-Карло";
    cout << "\n\nВведите значение левой границы интегрирования: ";
    cin >> xMin;
    cout << "\nВведите значение правой границы интегрирования: ";
    cin >> xMax;
    cout << "\nВведите высоту прямоугольника, в пределах которого будут генерироваться точки: ";
    cin >> yMax;

    for (int i = 0; i < SIZE; i++)
    {
        int n = N[i];
        integralValue[i] = monteCarloIntegralSolver(xMin, xMax, yMin, yMax, n);
        error[i] = fabs(integralValue[i] - trapezoidMethod[i]) / trapezoidMethod[i];
    }

    cout << endl;

    for (int i = 0; i < SIZE; i++)
    {
        cout << "\n" << i+1 << ") Число сгенерированных точек: " << N[i];
        cout << "\nЗначение интеграла: " << integralValue[i];
        cout << "\nВеличина абсолютной ошибки: " << error[i] << endl;
    }

    cout << endl;
    system("pause");
    return 0;
}