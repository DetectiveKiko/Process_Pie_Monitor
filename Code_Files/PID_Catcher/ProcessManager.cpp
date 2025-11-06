#include "ProcessManager.hpp"

std::vector<ProcessInfo> ProcessManager::GetProcesses() {
    std::vector<ProcessInfo> processes;

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to create process snapshot." << std::endl;
        return processes;
    }

    PROCESSENTRY32 processEntry;
    processEntry.dwSize = sizeof(PROCESSENTRY32);


    if (Process32First(hSnapshot, &processEntry)) {
        do {
            processes.push_back({ processEntry.szExeFile, processEntry.th32ProcessID, processEntry.th32ParentProcessID });
        } while (Process32Next(hSnapshot, &processEntry));
    } else {
        std::cerr << "Failed to retrieve process information." << std::endl;
    }

    CloseHandle(hSnapshot);
    return processes;
}
