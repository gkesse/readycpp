#pragma once

#ifdef UNIT_TEST
#include <gtest/gtest_prod.h>
#endif

#include <string>
#include <vector>

namespace factory
{
    class Facade;
}

namespace process
{
    // cree un module process
    class Process
    {
#ifdef UNIT_TEST
        friend class TestProcess;
        FRIEND_TEST(TestProcess, Test_Nombre_Modules);
        FRIEND_TEST(TestProcess, Test_Module_Inconnu);
        FRIEND_TEST(TestProcess, Test_Module_Aide);
        FRIEND_TEST(TestProcess, Test_Egalite_Modules);
        FRIEND_TEST(TestProcess, Test_Chargement_Module);
        FRIEND_TEST(TestProcess, Test_Execution_Module);
#endif

        friend class factory::Facade;

    public:
        // cree le type d'un module
        enum class MODULE_TYPE
        {
            INCONNU,
            HELP,
            SERVER_BOOST,
            BDD,
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
            Module(MODULE_TYPE _type, const std::string &_name, const std::string &_description);
            // cree un constructeur de module par copie
            Module(const Module &_module);
            // cree un operateur d'affectation de module
            Module &operator=(const Module &_module);
            // cree un operateur d'egalite entre deux modules
            bool operator==(const Module &_module) const;
            // cree un operateur de difference entre deux modules
            bool operator!=(const Module &_module) const;
        };

        // cree une lsite de structure de module
        struct ModuleList : public std::vector<Module>
        {
            // charge un module par son nom
            bool loadModuleByName(const std::string &_name, Module &_module);
        };

        // cree un type pour un argument cli
        using Arg = std::string;
        // cree un type pour une liste d'arguments cli
        using ArgList = std::vector<Arg>;

#ifdef UNIT_TEST
    public:
        // cree un constructeur de process par defaut
        explicit Process()
        {
            initModuleListe();
            m_module = m_module_list.at(1);
        }
        // initialise le module
        void setModule(const Module &_module) { m_module = _module; }
#endif

    public:
        // cree un constructeur de process par donnees
        explicit Process(int _argc, char **_argv);
        // cree un destructeur de process
        ~Process();
        // execute le process
        void run();

    private:
        // initialise la lsite des modules
        void initModuleListe();
        // charge la liste des arguments cli
        void loadArguments(int _argc, char **_argv, ArgList &_arg_list);
        // charge le module correspondant à l'argument cli
        bool loadModule(Module &_module);
        // affiche l'aide
        virtual void runHelp();

    private:
        Module m_module;
        ArgList m_arg_list;
        ModuleList m_module_list;
    };
}
