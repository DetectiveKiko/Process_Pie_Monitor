#ifndef PROCESSMANAGER_HPP
#define PROCESSMANAGER_HPP

#include <windows.h>
#include <tlhelp32.h>
#include <vector>
#include <string>
#include <iostream>

struct ProcessInfo {
    std::string name;
    DWORD processID;
    DWORD parentProcessID;
};

class ProcessManager {
public:
    static std::vector<ProcessInfo> GetProcesses();
};

#endif //PROCESSMANAGER_HPP
