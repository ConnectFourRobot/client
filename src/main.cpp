#include <iostream>
#include <iomanip>
#include <exception>
#include "../include/GameHandler.hpp"
#include "../include/util/InputParser.hpp"

#define helpTextCell(text, size) std::setfill(' ') << std::setw(size) << std::left << text
#define helpText(command, description, defaultValue, validLimits) std::cout \
 << helpTextCell(command, 15) \
 << helpTextCell(description, 40) \
 << helpTextCell(defaultValue, 15) \
 << helpTextCell(validLimits, 15) \
 << std::endl; std::cout.flush();

static void printHelp()
{
    helpText("Command", "Description", "Default", "Valid Limits");
    helpText("-i --ip", "IP-Address", "127.0.0.1", "IP-v4-only");
    helpText("-p --port", "Port", "7777", "any Port");
    helpText("-h --help", "Print Help", "", "");
    helpText("-c --columns", "The columns/length of the game", "7", "1-127");
    helpText("-r --rows", "The rows/height of the game", "6", "1-127");
    helpText("-w --who", "The playerId of this KI-Client", "1", "1 or 2");
    helpText("-l --level", "The difficulty level of this KI-Client", "1", "0=easy, 1=medium, 2=hard");

    //reset iomanip to default outputstream
    std::cout.copyfmt(std::ios(0));
}

int main(int argc, char **argv)
{
    try
    {
        // Default parameter
        InputParser input(argc, argv);
        std::string ip = input.useStringCmdOption("-i", "--ip", "127.0.0.1");
        int portRaw = input.useIntCmdOption("-p", "--port", "7777");
        unsigned short port = static_cast<unsigned short>(portRaw);
        int columns = input.useIntCmdOption("-c", "--columns", "7");
        int rows = input.useIntCmdOption("-r", "--rows", "6");
        int playerId = input.useIntCmdOption("-w", "--who", "1");
        int level = input.useIntCmdOption("-l", "--level", "1");
        if(input.cmdOptionExists("-h") || input.cmdOptionExists("--help"))
        {
            printHelp();
            return 0;
        }

        GameHandler *gameHandler = new GameHandler(ip, port, rows, columns, playerId, level);
        gameHandler->run();
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
