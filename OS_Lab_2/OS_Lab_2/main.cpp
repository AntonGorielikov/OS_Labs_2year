#include <iostream>
#include <Windows.h>

#define EXECUTABLE_LOCATION "sub_process.exe"

int main(int argc, char** argv)
{
    int number_of_processes = 0;
    int process_to_suspend = 0;
    int process_to_kill = 0;
    int process_to_realtime = 0;
    std::cout << "Enter number of processes: ";
    std::cin >> number_of_processes;
    std::cout << "Enter process to suspend (or -1 for not suspending): ";
    std::cin >> process_to_suspend;
    std::cout << "Enter process to kill (that's bad, i know, but what can i do / -1 for not killing): ";
    std::cin >> process_to_kill;
    std::cout << "Enter process, whose priority will be changed to realtime: ";
    std::cin >> process_to_realtime;

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
        if (process_to_suspend == i + 1)
        {
            std::cout << "Suspending process..." << std::endl;
            SuspendThread(process_info[i].hThread);
        }
        if (process_to_realtime == i + 1)
        {
            std::cout << "Increasing priority..." << std::endl;
            SetPriorityClass(process_info[i].hProcess, REALTIME_PRIORITY_CLASS);
        }
    }

    std::cout << "Resuming process num=" << process_to_suspend << std::endl;
    ResumeThread(process_info[process_to_suspend].hThread);

    std::cout << "Killing thread num=" << process_to_kill << std::endl;
    TerminateProcess(process_info[process_to_kill].hThread, 0);

    for (int i = 0; i < number_of_processes; ++i)
    {
        WaitForSingleObject(process_info[i].hProcess, INFINITE);

        int time_elapsed;
        GetExitCodeProcess(process_info[i].hProcess, (LPDWORD)&time_elapsed);
        
        std::cout << "Process " << i << " : time elapsed - " << time_elapsed / 1e4 << " msec" << std::endl;
    }

    system("pause");
    return 0;
}