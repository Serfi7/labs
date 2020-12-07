#pragma once

#include "iostream"

class Exception
{
private:
    std::string message;

public:
    Exception(std::string msg = "Exception")
    {
       this->message = msg;
    }

    std::string Message() {
        return this->message;
    }
};
