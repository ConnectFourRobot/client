#include "../../include/util/InputParser.hpp"

InputParser::InputParser(int &argc, char **argv) {
    for (int i = 1; i < argc; ++i){
        this->_arguments.push_back(std::string(argv[i]));
    }
}

const std::string& InputParser::getCmdOption(const std::string &option) const{
    std::vector<std::string>::const_iterator itr;
    itr = std::find(this->_arguments.begin(), this->_arguments.end(), option);

    if (itr != this->_arguments.end() && ++itr != this->_arguments.end()) {
        return *itr;
    }
    static const std::string empty_string("");
    return empty_string;
}

bool InputParser::cmdOptionExists(const std::string &option) const {
    return std::find(this->_arguments.begin(), this->_arguments.end(), option)
        != this->_arguments.end();
}
