#ifndef PROCESSTREE_HPP
#define PROCESSTREE_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "ProcessManager.hpp"

class ProcessTree {
public:
	static void Print(const std::vector<ProcessInfo>& processes);
};

#endif // PROCESSTREE_HPP