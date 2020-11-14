#ifndef INPUTPARSER_HPP
#define INPUTPARSER_HPP

#include <vector>
#include <string>
#include <algorithm>

class InputParser
{
private:
    std::vector<std::string> _arguments;
public:
    InputParser(int &argc, char **argv);
    const std::string& getCmdOption(const std::string &option) const;
    bool cmdOptionExists(const std::string &option) const;
};
#endif
