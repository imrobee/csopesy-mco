#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>
#include <vector>
#include "Scheduler.h"

Scheduler scheduler;

void printHeader() {
    std::cout << "  _____   _____   ____   _____   ______   _____ __     __\n";
    std::cout << " / ____| / ____| / __ \\ |  __ \\ |  ____| / ____|\\ \\   / /\n";
    std::cout << "| |     | (___  | |  | || |__) || |__   | (___   \\ \\_/ / \n";
    std::cout << "| |      \\___ \\ | |  | ||  ___/ |  __|   \\___ \\   \\   /  \n";
    std::cout << "| |____  ____) || |__| || |     | |____  ____) |   | |   \n";
    std::cout << " \\_____||_____/  \\____/ |_|     |______||_____/    |_|   \n";
    std::cout << "                                                        \n";
    std::cout << "________________________________________________________\n";
    std::cout << "\n";
    std::cout << "Welcome to CSOPESY Emulator!\n\n";
    std::cout << "Developers:\n";
    std::cout << "Clemente, Daniel Gavrie \n";
    std::cout << "Feliciano, Jan Robee \n";
    std::cout << "Mangawang, Felix Melford\n";
    std::cout << "Roque, Dominic Angelo\n\n";
    std::cout << "Type 'exit' to quit, 'clear' to clear the screen\n";
}

void clearScreen() {
    system("cls");
    printHeader();
}

void enterMainLoop() {
    std::string command;
    printHeader();

    while (true) {
        std::cout << "Enter a command: ";
        std::getline(std::cin, command);

        if (command == "initialize") { // Initialize the processor configuration of the application with config.txt
			std::cout << "Initialize command recognized. Configuring OS Emulator...\n";
            scheduler.initialize("config.txt");
        }
        else if (command == "screen") {
            std::cout << "Screen command recognized. Doing something.\n";
        }
		else if (command.rfind("screen -s ", 0) == 0) { // Starts a process with the given name
            std::cout << "Screen command recognized. Doing something.\n";
        }
        else if (command.rfind("screen -r ", 0) == 0) { // Accesses the process screen anytime
            std::string name = command.substr(10);
            std::ifstream log(name + ".txt"); // Update when processes shouldnt generate .txt files anymore
            if (log.is_open()) {
                std::cout << "Process name: " << name << "\nLogs:\n";
                std::string line;
                while (std::getline(log, line)) {
                    std::cout << line << "\n";
                }
                log.close();
            }
            else {
                std::cout << "Process " << name << " not found.\n"; // Should not be able to see processes that don't exist/are not finished
            }
        }
		else if (command == "screen -ls") { // Lists all processes
            scheduler.printStatus();
        }
		else if (command == "scheduler-start") { // Every X CPU ticks, a new process is created and put into ready queue for CPU scheduler. The freq is set in config.txt
            std::cout << "Scheduler-start command recognized. Doing something.\n";
        }
		else if (command == "scheduler-stop") { // Stops the scheduler from creating new processes
			std::cout << "Scheduler-stop command recognized. Doing something.\n";
        }
        else if (command == "report-util") { // Saves "screen -ls" in csopesy-log.txt
            std::cout << "Report-util command recognized.Generating report...\n";
        }
        else if (command == "clear") { // Clears the screen
            clearScreen();
        }
		else if (command == "exit") { // Exits the application
            std::cout << "Exit command recognized. Closing application.\n";
            scheduler.shutdown();
            break;
        }
        else {
            std::cout << "Unrecognized command.\n";
        }
    }
}

int main() {
    enterMainLoop();
    return 0;
}
