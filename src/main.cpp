#include <iostream>
#include <exception>
#include "../include/GameHandler.hpp"
#include "../include/util/InputParser.hpp"

void greeting(void);
GameHandler * createGameHandler(InputParser input);

void greeting(void) {
        std::cout << "Start VGR_CLIENT compiled at " __DATE__ " - " __TIME__ " with Linux: " <<
        #ifdef __linux__
            "yes"
        #else
            "no"
        #endif
        << std::endl;
}

GameHandler * createGameHandler(int argc, char ** argv) {
        InputParser input(argc, argv);
        std::string ip = input.useStringCmdOption("-i", "--ip", "IP-Address", "127.0.0.1", "IP-v4-only");
        int portRaw = input.useIntCmdOption("-p", "--port", "Port", "7777", "any Port");
        unsigned short port = static_cast<unsigned short>(portRaw);
        int columns = input.useIntCmdOption("-c", "--columns", "The columns/length of the game", "7", "1-127");
        int rows = input.useIntCmdOption("-r", "--rows", "The rows/height of the game","6", "1-127");
        int playerId = input.useIntCmdOption("-w", "--who", "The playerId of this KI-Client", "1", "1 or 2");
        int level = input.useIntCmdOption("-d", "--difficulty", "The difficulty level of this KI-Client", "1", "0=easy, 1=medium, 2=hard");

        if(input.ifHelpThenPrintHelp())
        {
            return nullptr;
        }
        return new GameHandler(ip, port, rows, columns, playerId, level);
}

int main(int argc, char **argv)
{
    try
    {
        greeting();
        GameHandler *gameHandler = createGameHandler(argc, argv);
        if (gameHandler != nullptr) {
            gameHandler->run();
        }
    }
    catch(const std::exception & err)
    {
        std::cerr << "Client terminated due to an std::exception: " << typeid(err).name() << std::endl << err.what() << std::endl;
        return -1;
    }
    catch(const char * err) {
        std::cerr << "Client terminated due to an char* exception" << std::endl << err << std::endl;
        return -1;
    }
    catch(const int err) {
        std::cerr << "Client terminated due to an int exception: " << err << std::endl;
        return -1;
    }
    catch(...) {
        std::cerr << "Client terminated due to an unknown exception " << std::endl;
        return -1;
    }
    return 0;
}
