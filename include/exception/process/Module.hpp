#pragma once

#include "exception/Exception.hpp"

namespace exception::process
{
    // cree une exception pour module
    class Module : public exception::Exception
    {
    public:
        // cree un constructeur d'exception pour module par defaut
        explicit Module();
        // cree un constructeur d'exception pour module par donnees
        explicit Module(const std::string &_msg);
        // cree un destructeur d'exception pour module
        ~Module();
    };
}
