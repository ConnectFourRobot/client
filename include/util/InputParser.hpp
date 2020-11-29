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
public:
    /** constructor */
    InputParser(int &argc, char **argv);

    /** */
    const std::string& getCmdOption(const std::string &option) const;

    /** */
    bool cmdOptionExists(const std::string &option) const;

    std::string useStringCmdOption(const char * letter, const char * option, const char * defaultValue) const;
    int useIntCmdOption(const char * letter, const char * option, const char * defaultValue) const;
};
#endif
