#include "../../include/logger/Logger.hpp"
#include <ctime>
#include <sys/stat.h>
#include <sys/types.h>

/////////////////////////////////////////////////////////////////////
//////////////////    Singleton stuff      //////////////////////////
/////////////////////////////////////////////////////////////////////
Logger * Logger::instance = nullptr;

Logger::Logger(): fileNameDebug(""), fileNameError(""), readyDebug(false), readyError(false)
{
    this->iniFileName();
}

Logger & Logger::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Logger();
    }
    return *instance;
}

//////////////////////////////////////////////////////////////////////
////////////////////    Logger stuff        //////////////////////////
//////////////////////////////////////////////////////////////////////
void Logger::iniFileName(void)
{
    const time_t currentTimeT = time(nullptr);
    const unsigned long long currentTime = static_cast<unsigned long long>(currentTimeT);
    this->fileNameDebug[0] = '\0';
    this->fileNameDebug[sizeof(this->fileNameDebug) - 1] = '\0';
    this->fileNameError[0] = '\0';
    this->fileNameError[sizeof(this->fileNameError) - 1] = '\0';
    this->firstLogLine[0] = '\0';
    this->firstLogLine[sizeof(this->firstLogLine) - 1] = '\0';
    snprintf(
        this->fileNameError,
        sizeof(this->fileNameDebug),
        "%s%s%llu%s",
        this->filePath,
        "error",
        currentTime,
        ".log"
    );
    snprintf(
        this->fileNameDebug,
        sizeof(this->fileNameDebug),
        "%s%s%llu%s",
        this->filePath,
        "debug",
        currentTime,
        ".log"
    );
    strftime(
        this->firstLogLine,
        sizeof(this->firstLogLine),
        "Log of VGR-Client. Start at %A, %d.%m.%Y - %H:%M:%S",
        localtime(&currentTimeT)
    );
}

Logger & Logger::setDebugEnabled(bool enableDebug) {
    this->shouldLogDebug = enableDebug;
    return *this;
}

Logger & Logger::logDebug(void)
{
    this->isError = false;
    return *this;
}

Logger & Logger::logError(void)
{
    this->isError = true;
    return *this;
}

Logger & Logger::operator<< (std::ostream & (*manipulator)(std::ostream &))
{
    if (this->shouldLogDebug)
    {
        this->iniStreamDebug();
        this->streamDebug << manipulator;
    }
    if (this->isError)
    {
        this->iniStreamError();
        this->streamError << manipulator;
    }
    if (this->logConsole)
    {
        std::cout << manipulator;
    }
    return *this;
}


void Logger::iniStreamError(void)
{
    if (!this->readyError)
    {
        this->iniDirectory();
        this->streamError.open(this->fileNameError, std::ios_base::app);
        this->streamError << this->firstLogLine << std::endl;
        this->readyError = true;
    }
}

void Logger::iniStreamDebug(void)
{
    if (!this->readyDebug)
    {
        this->iniDirectory();
        this->streamDebug.open(this->fileNameDebug, std::ios_base::app);
        this->streamDebug << this->firstLogLine << std::endl;
        //this->streamDebug << "Log of VGR-Client. Start at " << std::asctime(std::localtime(&time(nullptr))) << std::endl;
        this->readyDebug = true;
    }
}

void Logger::iniDirectory(void)
{
    int errorReturn = 0;
    char dirName[101] {'\0'};
    for (int i = 0; this->filePath[i] != '\0' && i < 100; i++)
    {
        if (this->filePath[i] == '/' && i >= 2)
        {
            dirName[i] = '\0';
            errorReturn = mkdir(dirName,0777);
            if (errorReturn < 0 && errno != EEXIST) {
                std::cout << "Could not create directory \"" << dirName << "\". Terminating program. " << std::endl;
                exit(errno);
            }
        }
        dirName[i] = this->filePath[i];
    }
}
