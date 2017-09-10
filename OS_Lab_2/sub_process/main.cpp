#include <iostream>

#include <cmath>
#include <cstdlib>
#include <chrono>

#include <Windows.h>

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
    SYSTEMTIME sys_time;
    FILETIME temp_ft;
    ULARGE_INTEGER time_before,
                   time_after;

    GetSystemTime(&sys_time);
    SystemTimeToFileTime(&sys_time, &temp_ft);
    time_before.LowPart = temp_ft.dwLowDateTime;
    time_before.HighPart = temp_ft.dwHighDateTime;
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
    GetSystemTime(&sys_time);
    SystemTimeToFileTime(&sys_time, &temp_ft);
    time_after.LowPart = temp_ft.dwLowDateTime;
    time_after.HighPart = temp_ft.dwHighDateTime;
    int time = int(time_after.QuadPart - time_before.QuadPart);
    return time;
}