#include "process/Process.hpp"

#include "factory/facade/Facade.hpp"

#include <algorithm>

// ajoute un module
#define DEF_ADD_MODULE( _type, _name, _description )                                                                                                                                                   \
    do                                                                                                                                                                                                 \
    {                                                                                                                                                                                                  \
        m_module_list.push_back( { _type, _name, _description } );                                                                                                                                     \
    } while ( false );

namespace process
{
// cree un constructeur de module par defaut
Process::Module::Module() : m_type( MODULE_TYPE::INCONNU ), m_name( "inconnu" ), m_description( "Le module est inconnu." ) {}

// cree un constructeur de module
Process::Module::Module( MODULE_TYPE _type, const std::string& _name, const std::string& _description ) : m_type( _type ), m_name( _name ), m_description( _description ) {}

// cree un constructeur de module par copie
Process::Module::Module( const Module& _module )
{
    *this = _module;
}

// cree un operateur d'affectation de module
Process::Module& Process::Module::operator=( const Module& _module )
{
    m_type        = _module.m_type;
    m_name        = _module.m_name;
    m_description = _module.m_description;
    return *this;
}

// cree un operateur d'egalite entre deux modules
bool Process::Module::operator==( const Module& _module ) const
{
    bool est_egal = true;
    est_egal &= ( m_type == _module.m_type );
    est_egal &= ( m_name == _module.m_name );
    est_egal &= ( m_description == _module.m_description );
    return est_egal;
}

// cree un operateur de difference entre deux modules
bool Process::Module::operator!=( const Module& _module ) const
{
    return !( *this == _module );
}

// charge un module par son nom
bool Process::ModuleList::loadModuleByName( const std::string& _name, Module& _module ) const
{
    if ( _name.empty() )
    {
        _module = at( 1 );
        return true;
    }

    auto it = std::find_if( begin(), end(), [&]( const Module& _obj ) { return _obj.m_name == _name; } );

    if ( it != end() && it->m_type != MODULE_TYPE::INCONNU )
    {
        _module = *it;
        return true;
    }

    _module = at( 0 );
    return false;
}

// charge un module par son type
bool Process::ModuleList::loadModuleByType( const MODULE_TYPE& _type, Module& _module ) const
{
    auto it = std::find_if( begin(), end(), [&]( const Module& _obj ) { return _obj.m_type == _type; } );

    if ( it != end() )
    {
        _module = *it;
        return true;
    }

    _module = at( 0 );
    return false;
}

// cree un constructeur de process par donnees
Process::Process( int _argc, char** _argv )
{
    initModuleListe();
    loadArguments( _argc, _argv, m_arg_list );
    if ( !loadModule( m_module ) )
    {
        throw exception::Exception( "Le chargement du module a echoue.|function={process::Process::Process()}" );
    }
}

// cree un destructeur de process
Process::~Process() {}

// execute le process
void Process::run()
{
    if ( m_module == m_module_list.at( 1 ) )
    {
        runHelp();
        return;
    }

    factory::facade::Facade factory_facade( *this );
    factory_facade.create()->run();
}

// recupere le module
Process::Module& Process::getModule()
{
    return m_module;
}

// recupere le module
const Process::Module& Process::getModule() const
{
    return m_module;
}

// recupere la liste des modules
Process::ModuleList& Process::getModuleListe()
{
    return m_module_list;
}

// recupere la liste des modules
const Process::ModuleList& Process::getModuleListe() const
{
    return m_module_list;
}

// recupere la liste des arguments cli
Process::ArgList& Process::getArgListe()
{
    return m_arg_list;
}

// recupere la liste des arguments cli
const Process::ArgList& Process::getArgListe() const
{
    return m_arg_list;
}

// initialise la liste des modules
void Process::initModuleListe()
{
    DEF_ADD_MODULE( MODULE_TYPE::INCONNU, "inconnu", "Le module est inconnu." );
    DEF_ADD_MODULE( MODULE_TYPE::HELP, "help", "Affiche l'aide." );
    DEF_ADD_MODULE( MODULE_TYPE::TEST, "test", "Execute le module de test." );
    DEF_ADD_MODULE( MODULE_TYPE::SERVER_BOOST, "server_boost", "Execute le module de gestion du serveur boost." );
}

// charge le module correspondant à l'argument cli
bool Process::loadModule( Module& _module ) const
{
    if ( m_arg_list.empty() )
    {
        _module = m_module_list.at( 0 );
        return false;
    }

    if ( m_arg_list.at( 0 ).empty() )
    {
        _module = m_module_list.at( 0 );
        return false;
    }

    if ( m_arg_list.size() == 1 )
    {
        _module = m_module_list.at( 1 );
        return true;
    }

    std::string module_name = m_arg_list[1];

    return m_module_list.loadModuleByName( module_name, _module );
}

// recupere la description du module
std::string Process::getDescription( const MODULE_TYPE& _type ) const
{
    Module module;
    if ( !m_module_list.loadModuleByType( _type, module ) )
    {
        throw exception::Exception( "Le chargement du module a echoue.|function={process::Process::getDescription()}" );
    }
    return module.m_description;
}

// affiche l'aide
void Process::runHelp() const
{
    std::cout << std::endl;
    std::cout << "Usage: readycpp <module> <method> [params]" << std::endl;
    std::cout << std::endl;
    std::cout << "  - Description des arguments:" << std::endl;
    std::cout << "      - <module>  : Indique le module (obligatoire)." << std::endl;
    std::cout << "      - <method>  : Indique la methode (obligatoire)." << std::endl;
    std::cout << "      - [params]  : Indique les parametres (optionnels)." << std::endl;
    std::cout << std::endl;
    std::cout << "  - Liste des modules disponibles:" << std::endl;
    std::cout << "      - help          : " << getDescription( MODULE_TYPE::HELP ) << std::endl;
    std::cout << "      - test          : " << getDescription( MODULE_TYPE::TEST ) << std::endl;
    std::cout << "      - server_boost  : " << getDescription( MODULE_TYPE::SERVER_BOOST ) << std::endl;
    std::cout << std::endl;
}

// charge la liste des arguments cli
void Process::loadArguments( int _argc, char** _argv, ArgList& _arg_list ) const
{
    for ( int i = 0; i < _argc; ++i )
    {
        _arg_list.push_back( _argv[i] );
    }
}
} // namespace process
