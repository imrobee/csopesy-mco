#include "Scheduler.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>

Scheduler::Scheduler() : numCores(4), schedulerType("fcfs"), running(false) {}

void Scheduler::initialize(const std::string& configPath) {
    std::ifstream config(configPath);
    if (!config.is_open()) {
        std::cerr << "Failed to open " << configPath << "\n";
        return;
    }

    std::string line;
    while (std::getline(config, line)) {
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "num-cpu") {
            iss >> numCores;
        }
        else if (key == "scheduler") {
            iss >> schedulerType;
        }
    }

    // Create dummy processes (Only for FCFS HW, # of processes should be determined in config.txt)
    for (int i = 1; i <= 10; ++i) {
        std::ostringstream name;
        name << "Process_" << std::setw(2) << std::setfill('0') << i;
        auto process = std::make_shared<Process>(name.str(), 100);
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            jobQueue.push(process);
        }
    }

    running = true;
    start();
}

void Scheduler::start() {
    coreAvailable.resize(numCores, true);
    for (int i = 0; i < numCores; ++i) {
        cores.emplace_back(&Scheduler::coreWorker, this, i);
    }
    std::thread(&Scheduler::dispatcher, this).detach();
}

void Scheduler::dispatcher() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.notify_all();
    }
}

void Scheduler::coreWorker(int coreId) {
    while (running) {
        std::shared_ptr<Process> proc = nullptr;

        {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait(lock, [&] {
                return !jobQueue.empty() || !running;
                });

            if (!running) break;

            if (!jobQueue.empty() && coreAvailable[coreId]) {
                proc = jobQueue.front();
                jobQueue.pop();
                coreAvailable[coreId] = false;
                runningProcesses[proc->getName()] = proc;
            }
        }

        if (proc) {
            proc->run(coreId);

            {
                std::lock_guard<std::mutex> lock(queueMutex);
                finishedProcesses[proc->getName()] = proc;
                runningProcesses.erase(proc->getName());
                coreAvailable[coreId] = true;
            }
        }
    }
}

void Scheduler::printStatus() {
    int usedCores = 0;
    for (bool available : coreAvailable) {
        if (!available) ++usedCores;
    }

    std::cout << "CPU Utilization: " << (usedCores * 100 / numCores) << "%\n";
    std::cout << "Cores Used: " << usedCores << "\n";
    std::cout << "Cores Available: " << (numCores - usedCores) << "\n";
    std::cout << "________________________________________________________\n\n";

    std::cout << "Running processes:\n\n";
    for (const auto& [name, proc] : runningProcesses) {
        std::cout << name << " | (" << proc->getTimestamp() << ") | ";
        std::cout << "Core:" << proc->getAssignedCore() << " | ";
        std::cout << proc->getCurrentLine() << " / " << proc->getTotalLines() << "\n\n";
    }

    std::cout << "Finished processes:\n\n";
    for (const auto& [name, proc] : finishedProcesses) {
        std::cout << name << " | (" << proc->getTimestamp() << ") | ";
        std::cout << "Finished | " << proc->getTotalLines() << "/" << proc->getTotalLines() << "\n\n";
    }

    std::cout << "________________________________________________________\n";
}

void Scheduler::shutdown() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        running = false;
    }
    cv.notify_all();  // Wake up all waiting threads

    for (auto& thread : cores) {
        if (thread.joinable()) {
            thread.join();  // Wait for worker thread to finish
        }
    }

    cores.clear();
}
