#include "exception/process/Module.hpp"

namespace exception::process
{
    // cree un constructeur d'exception pour module par defaut
    Module::Module()
        : Exception("Erreur lors du chargement du module.")
    {
    }

    // cree un constructeur d'exception pour module par donnees
    Module::Module(const std::string &_msg)
        : Exception(_msg)
    {
    }

    // cree un destructeur d'exception pour module
    Module::~Module()
    {
    }
}
