#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <sstream>

struct Process {
    std::vector<int> allocation;
    std::vector<int> maximum;
    std::vector<int> need;
    bool finished;
};

// Read data from file and store it in the processes and available vectors
void readDataFromFile(const std::string& filename, std::vector<Process>& processes, std::vector<int>& available) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Process process;
        int a, b, c;
        iss >> a >> b >> c;
        process.allocation = {a, b, c};
        iss >> a >> b >> c;
        process.maximum = {a, b, c};
        process.need = {process.maximum[0] - process.allocation[0],
                        process.maximum[1] - process.allocation[1],
                        process.maximum[2] - process.allocation[2]};
        process.finished = false;
        processes.push_back(process);
    }
    file.close();

    // Assuming the available resources are at the end of the file
    // Adjust if the format of your input file is different
    available = processes.back().allocation;
    processes.pop_back(); // Remove the last "process" which actually holds the available resources
}

// Check if all processes are finished
bool checkCompletion(const std::vector<Process>& processes) {
    for (const auto& process : processes) {
        if (!process.finished) return false;
    }
    return true;
}

// Find a safe sequence if it exists
bool findSafeSequence(std::vector<Process>& processes, std::vector<int>& available, std::vector<int>& safeSequence) {
    while (!checkCompletion(processes)) {
        bool progress = false;
        for (int i = 0; i < processes.size(); ++i) {
            if (!processes[i].finished && 
                std::inner_product(begin(processes[i].need), end(processes[i].need), begin(available), true, std::logical_and<>(), std::less_equal<>())) {
                std::transform(begin(available), end(available), begin(processes[i].allocation), begin(available), std::plus<>());
                processes[i].finished = true;
                safeSequence.push_back(i);
                progress = true;
                break;
            }
        }
        if (!progress) {
            return false; // No progress means deadlock
        }
    }
    return true;
}

int main() {
    std::vector<Process> processes;
    std::vector<int> available;
    std::vector<int> safeSequence;

    readDataFromFile("input.txt", processes, available);

    bool isSafe = findSafeSequence(processes, available, safeSequence);
    
    if (isSafe) {
        std::cout << "System is in a safe state.\nSafe sequence is: ";
        for (int pid : safeSequence) {
            std::cout << "P" << pid << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "System is not in a safe state." << std::endl;
    }

    return 0;
}
