#include <iostream>
#include <string>
#include <cstdlib>

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
    std::cout << "Welcome to CSOPESY Emulator!\n";
    std::cout << "\n";
    std::cout << "Developers:\n";
    std::cout << "Clemente, Daniel Gavrie \n";
    std::cout << "Feliciano, Jan Robee \n";
    std::cout << "Mangawang, Felix Melford\n";
    std::cout << "Roque, Dominic Angelo\n";
    std::cout << "\n";
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

        if (command == "initialize") {
            std::cout << "initialize command recognized. Doing something.\n";
        }
        else if (command == "screen") {
            std::cout << "screen command recognized. Doing something.\n";
        }
        else if (command == "scheduler-test") {
            std::cout << "scheduler-test command recognized. Doing something.\n";
        }
        else if (command == "scheduler-stop") {
            std::cout << "scheduler-stop command recognized. Doing something.\n";
        }
        else if (command == "report-util") {
            std::cout << "report-util command recognized. Doing something.\n";
        }
        else if (command == "clear") {
            clearScreen();
        }
        else if (command == "exit") {
            std::cout << "exit command recognized. Closing application.\n";
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
