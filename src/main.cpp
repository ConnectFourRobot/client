#include <iostream>
#include "../include/GameHandler.hpp"
#include "../include/util/InputParser.hpp"

static void printHelp(){
	std::cout << "-i --ip\t IP-Adress (default 127.0.0.1)" << std::endl;
	std::cout << "-p --port\t Port (default 7777)" << std::endl;
	std::cout << "-h --help\t print help" << std::endl;
}

int main(int argc, char **argv) {

    // Default parameter
    std::string ip = "127.0.0.1";
    unsigned short port = 7777;

    InputParser input(argc, argv);
    if(input.cmdOptionExists("-h") || input.cmdOptionExists("--help")) {
        printHelp();
        return 0;
    }

    if(input.cmdOptionExists("-i") || input.cmdOptionExists("--ip")) {
        std::string option = input.getCmdOption("-i");
        ip = option;
    }

    if(input.cmdOptionExists("-p") || input.cmdOptionExists("--port")) {
        std::string option = input.getCmdOption("-p");
        port = std::stoi(option, nullptr);;
    }

    GameHandler *gameHandler = new GameHandler(ip, port);
    gameHandler->run();
    return 0;
}