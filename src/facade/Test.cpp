#include "facade/Test.hpp"

#include "factory/facade/Test.hpp"

namespace facade
{
DEFINE_FACADE_METHOD( Test, Test, MODULE_TYPE::TEST )

// initialise la liste des methodes
void Test::initMethodListe()
{
    DEFINE_FACADE_ADD_METHOD( METHOD_TYPE::INCONNU, "inconnu", "La methode est inconnue." );
    DEFINE_FACADE_ADD_METHOD( METHOD_TYPE::HELP, "help", "Affiche l'aide." );
    DEFINE_FACADE_ADD_METHOD( METHOD_TYPE::RUN, "run", "Execute la methode de test." );
    DEFINE_FACADE_ADD_METHOD( METHOD_TYPE::NO_METHOD, "no_method", "Execute la methode non definie." );
}

// affiche l'aide
void Test::runHelp()
{
    std::cout << std::endl;
    std::cout << "Usage: readycpp <module> <method> [params]" << std::endl;
    std::cout << std::endl;
    std::cout << "  - Description des arguments:" << std::endl;
    std::cout << "      - <module>  : Indique le module (test)." << std::endl;
    std::cout << "      - <method>  : Indique la methode (obligatoire)." << std::endl;
    std::cout << "      - [params]  : Indique les parametres (optionnels)." << std::endl;
    std::cout << std::endl;
    std::cout << "  - Liste des methodes disponibles:" << std::endl;
    std::cout << "      - help      : " << getDescription( METHOD_TYPE::HELP ) << std::endl;
    std::cout << "      - run       : " << getDescription( METHOD_TYPE::RUN ) << std::endl;
    std::cout << std::endl;
}

// execute la methode run
void Test::onRun()
{
    std::cout << "Execution de la facade test." << std::endl;
}
} // namespace facade
