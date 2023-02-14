//
// Created by Mehdi on 14/02/2023.
//

#include "unableToOpenFileException.h"
#include "string"

unableToOpenFileException::unableToOpenFileException(std::string filePath) : cause(filePath) {}

// Le constructeur de copie. Il est utilisé par le mécanisme
// des exceptions :
unableToOpenFileException::unableToOpenFileException(const unableToOpenFileException &source) : cause(source.cause) {}