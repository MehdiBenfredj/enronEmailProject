//
// Created by Mehdi on 14/02/2023.
//

#ifndef NEWENRONMAIL_UNABLETOOPENFILEEXCEPTION_H
#define NEWENRONMAIL_UNABLETOOPENFILEEXCEPTION_H
#include "string"
#include "exception"

class unableToOpenFileException : std::exception {
public:
    std::string cause;  // Entier spécifiant la cause de l'exception.
    // Le constructeur. Il appelle le constructeur de cause.
    unableToOpenFileException(std::string filePath);

    // Le constructeur de copie. Il est utilisé par le mécanisme
    // des exceptions :
    unableToOpenFileException(const unableToOpenFileException &source);

    virtual char * what ();
};


#endif //NEWENRONMAIL_UNABLETOOPENFILEEXCEPTION_H
