#pragma once

#include "exception/Exception.hpp"

namespace factory
{
class Facade;
}

namespace process
{
// cree un module process
class Process
{
public:
    // cree le type d'un module
    enum class MODULE_TYPE
    {
        INCONNU,
        HELP,
        TEST,
        SERVER_BOOST,
    };

    // cree la structure d'un module
    struct Module
    {
        MODULE_TYPE m_type;
        std::string m_name;
        std::string m_description;

        // cree un constructeur de module par defaut
        Module();
        // cree un constructeur de module par donnees
        Module( MODULE_TYPE _type, const std::string& _name, const std::string& _description );
        // cree un constructeur de module par copie
        Module( const Module& _module );
        // cree un operateur d'affectation de module
        Module& operator=( const Module& _module );
        // cree un operateur d'egalite entre deux modules
        bool operator==( const Module& _module ) const;
        // cree un operateur de difference entre deux modules
        bool operator!=( const Module& _module ) const;
    };

    // cree une lsite de structure de module
    struct ModuleList : public std::vector<Module>
    {
        // charge un module par son nom
        bool loadModuleByName( const std::string& _name, Module& _module ) const;
        // charge un module par son type
        bool loadModuleByType( const MODULE_TYPE& _type, Module& _module ) const;
    };

    // cree un type pour un argument cli
    using Arg = std::string;
    // cree un type pour une liste d'arguments cli
    using ArgList = std::vector<Arg>;

#ifdef UNIT_TEST
public:
    // cree un constructeur de process par defaut
    explicit Process( const ArgList& _arg_list ) : m_arg_list( _arg_list )
    {
        initModuleListe();
        if ( !loadModule( m_module ) )
        {
            throw exception::Exception( "Le chargement du module a echoue.|function={process::Process::Process()}" );
        }
    }
#endif

public:
    // cree un constructeur de process par donnees
    explicit Process( int _argc, char** _argv );
    // cree un destructeur de process
    ~Process();
    // execute le process
    void run();
    // recupere le module
    Module& getModule();
    // recupere le module
    const Module& getModule() const;
    // recupere la liste des modules
    ModuleList& getModuleListe();
    // recupere la liste des modules
    const ModuleList& getModuleListe() const;
    // recupere la liste des arguments cli
    ArgList& getArgListe();
    // recupere la liste des arguments cli
    const ArgList& getArgListe() const;

private:
    // initialise la lsite des modules
    void initModuleListe();
    // charge la liste des arguments cli
    void loadArguments( int _argc, char** _argv, ArgList& _arg_list ) const;
    // charge le module a partir des arguments cli
    bool loadModule( Module& _module ) const;
    // recupere la description du module
    std::string getDescription( const MODULE_TYPE& _type ) const;
    // affiche l'aide
    void runHelp() const;

private:
    Module     m_module;
    ArgList    m_arg_list;
    ModuleList m_module_list;
};
} // namespace process
