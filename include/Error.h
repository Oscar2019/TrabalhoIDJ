#pragma once
#include <stdexcept>
#include <string>

#define EngineRuntimeError_Line(arg) EngineRuntimeError(__FILE__, __LINE__, arg);
class EngineRuntimeError : std::runtime_error{
    public:
        EngineRuntimeError();
        EngineRuntimeError(const char *, int line, std::string &&msg);
        EngineRuntimeError(const char *, int line, std::string &msg);
        virtual const char* what();
    private:
        std::string fileName;
        int lineNumber;
};