#ifndef INPUTPARSER_HPP
#define INPUTPARSER_HPP

#include <vector>
#include <string>
#include <algorithm>

/** parser for main arguments */
class InputParser
{
private:
    std::vector<std::string> _arguments;

    //help texts
    std::vector<const char *> helpLetters;
    std::vector<const char *> helpCommand;
    std::vector<const char *> helpDescription;
    std::vector<const char *> helpDefaultValues;
    std::vector<const char *> helpLimitTexts;
    void printHelp(void);
    void printHelpLine(const char * letter, const char * command, const char * description, const char * defaultValue, const char * limitsText);

    /** copy char array without terminating 0 */
    void myStrCpy(char ** to, const char * text, int charCount);

public:
    /** constructor */
    InputParser(int &argc, char **argv);

    /** */
    const std::string& getCmdOption(const std::string &option) const;

    /** */
    bool cmdOptionExists(const std::string &option) const;

    std::string useStringCmdOption(const char * letter, const char * command, const char * description, const char * defaultValue, const char * limitText);
    int useIntCmdOption(const char * letter, const char * command, const char * description, const char * defaultValue, const char * limitText);

    bool ifHelpThenPrintHelp(void);
};
#endif
