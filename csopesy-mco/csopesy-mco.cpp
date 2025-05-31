#include <iostream>
#include <string>
#include <cstdlib>
#include <map>
#include <ctime>
#include <iomanip>
#include <sstream>

// Struct to represent a screen
struct Screen {
    std::string name;
    int currentLine = 0;
    int totalLines = 100; //Temp
    std::string timestamp;
};

// Map to store screen sessions
std::map<std::string, Screen> screens;

std::string getCurrentTimestamp() {
    auto now = std::time(nullptr);
    std::tm localTime;

#ifdef _WIN32
    localtime_s(&localTime, &now); // Windows secure version
#else
    localtime_r(&now, &localTime); // POSIX (Linux/macOS)
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%m/%d/%Y, %I:%M:%S %p");
    return oss.str();
}

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
    //printHeader();
}

void drawScreen(const Screen& screen) {
    clearScreen();
    std::cout << "=== SCREEN: " << screen.name << " ===\n";
    std::cout << "Process Name: " << screen.name << "\n";
    std::cout << "Instruction: " << screen.currentLine << " / " << screen.totalLines << "\n";
    std::cout << "Created At: " << screen.timestamp << "\n\n";
    std::cout << "Type 'exit' to return to main menu.\n";

    std::string input;
    while (true) {
        std::cout << screen.name << " > ";
        std::getline(std::cin, input);
        if (input == "exit") {
            clearScreen();
            printHeader();
            return;
        }
        else {
            std::cout << "Unrecognized command inside screen. Type 'exit' to return.\n";
        }
    }
}

void enterMainLoop() {
    std::string command;
    printHeader();

    while (true) {
        //printHeader();
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
        else if (command.rfind("screen -s ", 0) == 0) {
            std::string name = command.substr(10);
            if (screens.find(name) == screens.end()) {
                Screen newScreen;
                newScreen.name = name;
                newScreen.timestamp = getCurrentTimestamp();
                screens[name] = newScreen;
                drawScreen(screens[name]);
            }
            else {
                std::cout << "Screen with name '" << name << "' already exists.\n";
            }
        }
        else if (command.rfind("screen -r ", 0) == 0) {
            std::string name = command.substr(10);
            if (screens.find(name) != screens.end()) {
                drawScreen(screens[name]);
            }
            else {
                std::cout << "No screen found with name '" << name << "'.\n";
            }
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
