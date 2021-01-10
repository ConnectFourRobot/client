#include "../../include/util/InputParser.hpp"
#include <iostream>

InputParser::InputParser(int &argc, char **argv)
{
    for (int i = 1; i < argc; ++i)
    {
        this->_arguments.push_back(std::string(argv[i]));
    }
    this->helpLetters.reserve(10);
    this->helpCommand.reserve(10);
    this->helpDescription.reserve(10);
    this->helpDefaultValues.reserve(10);
    this->helpLimitTexts.reserve(10);
}

const std::string& InputParser::getCmdOption(const std::string &option) const
{
    std::vector<std::string>::const_iterator itr;
    itr = std::find(this->_arguments.begin(), this->_arguments.end(), option);

    if (itr != this->_arguments.end() && ++itr != this->_arguments.end())
    {
        return *itr;
    }
    static const std::string empty_string("");
    return empty_string;
}

bool InputParser::cmdOptionExists(const std::string &option) const
{
    return std::find(this->_arguments.begin(), this->_arguments.end(), option)
           != this->_arguments.end();
}

std::string InputParser::useStringCmdOption(const char * letter, const char * command, const char * description, const char * defaultValue, const char * limitText)
{
    this->helpLetters.push_back(letter);
    this->helpCommand.push_back(command);
    this->helpDescription.push_back(description);
    this->helpDefaultValues.push_back(defaultValue);
    this->helpLimitTexts.push_back(limitText);
    for (std::vector<std::string>::const_iterator itr = this->_arguments.cbegin(); itr < this->_arguments.end(); itr++)
    {
        if ((*itr == letter || *itr == command) && (itr + 1) != this->_arguments.end())
        {
            return *(itr + 1);
        }
    };
    return defaultValue;
}

int InputParser::useIntCmdOption(const char * letter, const char * command, const char * description, const char * defaultValue, const char * limitText)
{
    std::string result = this->useStringCmdOption(letter, command, description, defaultValue, limitText);
    return std::stoi(result);
}

bool InputParser::useBooleanCmdOption(const char * letter, const char * command, const char * description) {
    this->helpLetters.push_back(letter);
    this->helpCommand.push_back(command);
    this->helpDescription.push_back(description);
    this->helpDefaultValues.push_back("-");
    this->helpLimitTexts.push_back(" ");
    return (this->cmdOptionExists(std::string(letter)) || this->cmdOptionExists(std::string(command)));
}

void InputParser::myStrCpy(char ** to, const char * text, int charCount)
{
    while (*text != '\0' && charCount > 0)
    {
        **to = *text;
        (*to)++;
        text++;
        charCount--;
    }
    while(charCount > 0) {
        **to = ' ';
        (*to)++;
        charCount--;
    }
}

void InputParser::printHelpLine(const char * letter, const char * command, const char * description, const char * defaultValue, const char * limitsText)
{
    const int maxChars = 105;
    char line[maxChars + 1];
    char * linePtr = line;

    //for (int i = 0; i < maxChars; i++) line[i] = ' ';
    line[maxChars] = '\0';

    this->myStrCpy(&linePtr, letter, 4);
    this->myStrCpy(&linePtr, command, 16);
    this->myStrCpy(&linePtr, description, 40);
    this->myStrCpy(&linePtr, defaultValue, 15);
    this->myStrCpy(&linePtr, limitsText, 25);
    *linePtr = '\0';

    std::cout << line << std::endl;
}

void InputParser::printHelp(void)
{
    int commandCount = this->helpCommand.size();
    this->printHelpLine("Comm", "and", "Description", "Default", "Valid Limits");
    this->printHelpLine("-h", "--help", "Print Help", "", "");
    for (int i = 0; i < commandCount; i++)
    {
        this->printHelpLine(this->helpLetters[i], this->helpCommand[i], this->helpDescription[i], this->helpDefaultValues[i], this->helpLimitTexts[i]);
    }
}

bool InputParser::ifHelpThenPrintHelp(void)
{
    if (this->cmdOptionExists("-h") || this->cmdOptionExists("--help"))
    {
        this->printHelp();
        return true;
    }
    return false;
}
