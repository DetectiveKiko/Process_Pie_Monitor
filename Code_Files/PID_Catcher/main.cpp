#include "ProcessManager.hpp"
#include "ProcessTree.hpp"

int main()
{
	while (true)
	{
		auto processes = ProcessManager::GetProcesses();
		/*
		 * old way to show the process tree.
		*/
		// for (const auto& process : processes)
		// {
		// 	std::cout << "Process: " << process.name
		// 			  << " | PID: " << process.processID
		// 			  << " | Parent PID: " << process.parentProcessID << std::endl;
		// }

		ProcessTree::Print(processes);

		std::cout << "Enter '0' to terminate the program or any other integer to continue : ";
		int exit;
		std::cin >> exit;
		if (exit == 0){break;}
	}
}