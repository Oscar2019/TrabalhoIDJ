#include "Error.h"
#include <iostream>

// Construtor vazio do erro
EngineRuntimeError::EngineRuntimeError() : std::runtime_error(""), fileName(""), lineNumber(0){

}

// Cria o erro
EngineRuntimeError::EngineRuntimeError(const char * file, int line, std::string &&msg) : std::runtime_error(std::string("[" + std::string(file) + "#" + std::to_string(line) + "]" + msg)), fileName(file), lineNumber(line) {

}

// Cria o erro
EngineRuntimeError::EngineRuntimeError(const char * file, int line, std::string &msg) : std::runtime_error(std::string("[" + std::string(file) + "#" + std::to_string(line) + "]" + msg)), fileName(file), lineNumber(line){

}

// exibe o erro
const char* EngineRuntimeError::what(){
    return std::runtime_error::what();
}