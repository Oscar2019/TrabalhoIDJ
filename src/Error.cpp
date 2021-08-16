#include "Error.h"
#include <iostream>

EngineRuntimeError::EngineRuntimeError() : std::runtime_error(""), fileName(""), lineNumber(0){

}

EngineRuntimeError::EngineRuntimeError(const char * file, int line, std::string &&msg) : std::runtime_error(std::string("[" + std::string(file) + "#" + std::to_string(line) + "]" + msg)), fileName(file), lineNumber(line) {

}

EngineRuntimeError::EngineRuntimeError(const char * file, int line, std::string &msg) : std::runtime_error(std::string("[" + std::string(file) + "#" + std::to_string(line) + "]" + msg)), fileName(file), lineNumber(line){

}

const char* EngineRuntimeError::what(){
    return std::runtime_error::what();
}