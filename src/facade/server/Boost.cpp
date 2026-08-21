#include "facade/server/Boost.hpp"

#include "factory/facade/server/Boost.hpp"

namespace facade::server
{
DEFINE_FACADE_METHOD( server::Boost, Boost, MODULE_TYPE::SERVER_BOOST )

// initialise la liste des methodes
void Boost::initMethodListe()
{
    DEFINE_FACADE_ADD_METHOD( METHOD_TYPE::INCONNU, "inconnu", "La methode est inconnue." );
    DEFINE_FACADE_ADD_METHOD( METHOD_TYPE::HELP, "help", "Affiche l'aide." );
    DEFINE_FACADE_ADD_METHOD( METHOD_TYPE::RUN, "run", "Execute le serveur." );
}

// affiche l'aide
void Boost::runHelp()
{
    std::cout << std::endl;
    std::cout << "Usage: readycpp <module> <method> [params]" << std::endl;
    std::cout << std::endl;
    std::cout << "  - Description des arguments:" << std::endl;
    std::cout << "      - <module>  : Indique le module (server_boost)." << std::endl;
    std::cout << "      - <method>  : Indique la methode (obligatoire)." << std::endl;
    std::cout << "      - [params]  : Indique les parametres (optionnels)." << std::endl;
    std::cout << std::endl;
    std::cout << "  - Liste des methodes disponibles:" << std::endl;
    std::cout << "      - help      : " << getDescription( METHOD_TYPE::HELP ) << std::endl;
    std::cout << "      - run       : " << getDescription( METHOD_TYPE::RUN ) << std::endl;
    std::cout << std::endl;
}

// execute la methode run
void Boost::onRun()
{
    std::cout << "Execution de la methode : Boost::onRun()..." << std::endl;
}
} // namespace facade::server
