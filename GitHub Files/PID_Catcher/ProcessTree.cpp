#include "ProcessTree.hpp"


void PrintTreeRecursive(const std::unordered_map<DWORD, std::vector<ProcessInfo>>& childrenMap, DWORD parentPID, int indent, std::unordered_set<DWORD>& printedProcesses)
{
    // If the current parent PID has no children, return early
    if (childrenMap.find(parentPID) == childrenMap.end()) return;

    // Traverse through each child of the given parent
    for (const auto& proc : childrenMap.at(parentPID)) {
        // If this process has already been printed, skip it
        if (printedProcesses.find(proc.processID) != printedProcesses.end()) continue;

        // Mark the current process as printed
        printedProcesses.insert(proc.processID);

        // Print the process with appropriate indentation
        std::cout << std::string(indent, ' ') << "|-- " << proc.name << " (PID: " << proc.processID << ")" << std::endl;

        // Recursively print the children of this process
        PrintTreeRecursive(childrenMap, proc.processID, indent + 4, printedProcesses);  // Increase indent for child processes
    }
}

void ProcessTree::Print(const std::vector<ProcessInfo>& processes)
{
    std::unordered_map<DWORD, std::vector<ProcessInfo>> childrenMap;

    // Build a map of child processes, keyed by parent process ID
    for (const auto& proc : processes) {
        childrenMap[proc.parentProcessID].push_back(proc);
    }

    // Set to track printed processes and avoid duplicates
    std::unordered_set<DWORD> printedProcesses;

    // Print the tree header
    std::cout << std::endl << "===== Process Tree =====" << std::endl;

    // Loop through all processes to find root processes (PID == 0)
    // and start printing from each process
    for (const auto& proc : processes) {
        if (proc.parentProcessID == 0 && printedProcesses.find(proc.processID) == printedProcesses.end()) {
            // Only print root processes once
            std::cout << "|-- " << proc.name << " (PID: " << proc.processID << ")" << std::endl;
            // Mark root process as printed
            printedProcesses.insert(proc.processID);
            // Start recursion for children of root process
            PrintTreeRecursive(childrenMap, proc.processID, 4, printedProcesses);  // Indent for child processes
        }
    }

    // This ensures any process with children is also handled
    for (const auto& proc : processes) {
        // Ensure all non-root processes are printed, including their children
        if (proc.parentProcessID != 0 && printedProcesses.find(proc.processID) == printedProcesses.end()) {
            std::cout << "|-- " << proc.name << " (PID: " << proc.processID << ")" << std::endl;
            printedProcesses.insert(proc.processID);
            PrintTreeRecursive(childrenMap, proc.processID, 4, printedProcesses);
        }
    }
}
