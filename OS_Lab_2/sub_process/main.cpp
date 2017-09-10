#include <iostream>

#include <cmath>
#include <cstdlib>
#include <chrono>

const double EPS_VALUE = 0.01;
const double X_VALUE = 2;
const double B_VALUE = 3;

int main(int argc, char** argv)
{
    double b = 0,
        log_n = 0,
        x = 0,
        eps = 0,
        result = 0,
        step = 0;

    x = X_VALUE;
    b = B_VALUE;
    eps = EPS_VALUE;
    auto before = std::chrono::high_resolution_clock::now();
    while (x <= b)
    {
        result = 0;
        log_n = log(x);
        for (int n(0); fabs(log(x) - result) > fabs(eps); n++)
        {
            step = (1 / (2 * n + 1));
            step *= pow((x + 1) / (x - 1), 2 * n + 1);
            step *= 2;
            result += step;
        }
        std::cout << "log_n(x): " << log_n << "\t" << "teyl.: " << result << std::endl;
        x += 0.1;
    }
    auto after = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(after - before).count();
}