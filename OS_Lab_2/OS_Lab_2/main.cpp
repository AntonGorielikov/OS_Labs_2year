#include <iostream>
#include <Windows.h>

#define EXECUTABLE_LOCATION "sub_process.exe"

int main(int argc, char** argv)
{
    int number_of_processes;
    if ((argc != 2) ||
        (number_of_processes = atoi(argv[1])) <= 0)
    {
        std::cout << "Usage : " << argv[0] << " <number of processes>" << std::endl
                  << "Number of processes cannot be negative or 0" << std::endl;
        return 0;
    }

    PROCESS_INFORMATION *process_info = new PROCESS_INFORMATION[number_of_processes]();
    STARTUPINFO info = {};
    info.cb = sizeof(info);
    
    for (int i = 0; i < number_of_processes; ++i)
    {
        std::cout << "Creating process, number=" << i << std::endl;
        if (!CreateProcess(EXECUTABLE_LOCATION, //exe location
                           NULL,                //cmd command
                           NULL,                //security attributes for process
                           NULL,                //security attributes for thread
                           FALSE,               //inherit handles?
                           CREATE_NO_WINDOW,    //creation flags
                           NULL,                //enviroment varibles block
                           NULL,                //process directory
                           &info,
                           &process_info[i]))
        {
            std::cout << "Process creation failed, code : " << (int)GetLastError() << std::endl;
            return 0;
        }
    }

    for (int i = 0; i < number_of_processes; ++i)
    {
        WaitForSingleObject(process_info[i].hProcess, INFINITE);

        int time_elapsed;
        GetExitCodeProcess(process_info[i].hProcess, (LPDWORD)&time_elapsed);
        
        std::cout << "Process " << i << " : time elapsed - " << time_elapsed / 1e6 << " msec" << std::endl;
    }

    return 0;
}