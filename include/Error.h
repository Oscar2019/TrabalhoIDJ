#pragma once
#include <stdexcept>
#include <string>

/**
 * @brief Macro que coloca a msg com o arquivo e a linha
 * 
 */
#define EngineRuntimeError_Line(arg) EngineRuntimeError(__FILE__, __LINE__, arg);

/**
 * @brief Classe responsável por armazenar um erro com o come de arquivo e a linha
 * 
 */
class EngineRuntimeError : std::runtime_error{
    public:
        /**
         * @brief Constrói um erro vázio
         * 
         */
        EngineRuntimeError();
        /**
         * @brief Constrói um erro com o formato "[ \p file # \p line ] \p msg ", onde  \p file é uma string com o nome do arquivo,   \p line á linha e   \p msg é a mensagem da exceção
         * 
         * @param file 
         * @param line 
         * @param msg 
         */
        EngineRuntimeError(const char *file, int line, std::string &&msg);
        /**
         * @brief Constrói um erro com o formato "[ \p file # \p line ] \p msg ", onde  \p file é uma string com o nome do arquivo,   \p line á linha e   \p msg é a mensagem da exceção
         * 
         * @param file 
         * @param line 
         * @param msg 
         */
        EngineRuntimeError(const char *file, int line, std::string &msg);
        /**
         * @brief Retorna a string com a mensagem de erro
         * 
         * @return const char* 
         */
        virtual const char* what();
    private:
        /**
         * @brief Nome do arquivo
         * 
         */
        std::string fileName;
        /**
         * @brief Número da linha
         * 
         */
        int lineNumber;
};