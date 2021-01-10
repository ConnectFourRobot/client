#ifndef LOGGER_HPP
#define LOGGER_HPP

#define LOG Logger::getInstance().logDebug()
#define LOG_ERROR Logger::getInstance().logError()

#include <fstream>
#include <string>
#include <iostream>

class Logger {

// Singleton stuff first
protected:
    /** Singleton Design Pattern instance */
    static Logger * instance;

    /** Singleton Constructor */
    Logger();

    /** Copy Constructor forbidden */
    Logger(const Logger &) = delete;

    /** Assignment forbidden */
    Logger & operator=(const Logger &) = delete;

public:
    /** Singleton Creator */
    static Logger & getInstance();

// Logger
protected:
    /** The path of the logs. Home directory sign ~ does NOT work! Root directory must exist! */
    const char * filePath = "./logs/client/";
    //const char * filePath = "/home/ott/logs/client/";

    /** The first line of the logs. It is cached, because debug and error log should have the same first line. */
    char firstLogLine[70];

    /** The File Name incl path for debug file. */
    char fileNameDebug[50];

    /** The File Name incl path for error file. */
    char fileNameError[50];

    /** Debug file output stream. The destructor writes the file. */
    std::ofstream streamDebug;

    /** Error file output stream. The destructor writes the file. */
    std::ofstream streamError;

    /** Is the Debug Stream opened yet */
    bool readyDebug = false;

    /** Is the Error Stream opened yet */
    bool readyError = false;

    /** Flag if Debug should not be ignored */
    bool shouldLogDebug = true;

    /** Toggle, if current data are error data */
    bool isError = false;

    /** Should all debug data also be printed to console */
    const bool logConsole = true;

protected:
    /** set file names */
    void iniFileName(void);

    /** open debug stream if not opened yet */
    void iniStreamDebug(void);

    /** open error stream if not opened yet */
    void iniStreamError(void);

    /** create directory */
    void iniDirectory(void);
public:
    /** enable debug logger */
    Logger & setDebugEnabled(bool enableDebug);

    /** start debug log */
    Logger & logDebug(void);

    /** start error log */
    Logger & logError(void);

    /** append log text */
    template <typename T>
    Logger & operator<< (T text);

    /** append log manipulator like std::endl */
    Logger & operator<< (std::ostream & (*manipulator)(std::ostream &));
};

template <typename T = const char *>
Logger & Logger::operator<<(T text)
{
    if (this->shouldLogDebug)
    {
        this->iniStreamDebug();
        this->streamDebug << text;
    }
    if (this->isError)
    {
        this->iniStreamError();
        this->streamError << text;
    }
    if (this->logConsole)
    {
        std::cout << text;
    }
    return *this;
}

#endif // LOGGER_HPP
