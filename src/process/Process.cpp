#include "process/Process.hpp"

#include "exception/process/Module.hpp"

#include <algorithm>

#define DEF_ADD_MODULE(_type, _name, _description) \
    m_module_list.push_back({_type, _name, _description})

namespace process
{
    // cree un constructeur de process par defaut
    Process::Process()
    {
        initModuleListe();
        m_module = m_module_list.at(0);
    }

    // cree un constructeur de process par donnees
    Process::Process(int _argc, char **_argv)
    {
        initModuleListe();
        loadArguments(_argc, _argv, m_arg_list);
        if (!loadModule(m_module))
        {
            throw exception::process::Module("Erreur lors du chargement du module.");
        }
    }

    // cree un destructeur de process
    Process::~Process()
    {
    }

    // initialise la liste des modules
    void Process::initModuleListe()
    {
        DEF_ADD_MODULE(MODULE_TYPE::INCONNU, "inconnu", "Le module est inconnu.");
        DEF_ADD_MODULE(MODULE_TYPE::HELP, "help", "Affiche l'aide.");
        DEF_ADD_MODULE(MODULE_TYPE::BDD, "bdd", "Execute le module de gestion de la base de données.");
    }

    // charge le module correspondant à l'argument cli
    bool Process::loadModule(Module &_module)
    {
        if (m_arg_list.size() < 1)
        {
            return false;
        }

        std::string module_name = m_arg_list[0];

        return m_module_list.loadModuleByName(module_name, _module);
    }

    // charge la liste des arguments cli
    void Process::loadArguments(int _argc, char **_argv, ArgList &_arg_list)
    {
        for (int i = 0; i < _argc; ++i)
        {
            m_arg_list.push_back(_argv[i]);
        }
    }

    // cree un constructeur de module par defaut
    Process::Module::Module()
        : m_type(MODULE_TYPE::INCONNU),
          m_name("inconnu"),
          m_description("Le module est inconnu.")
    {
    }

    // cree un constructeur de module
    Process::Module::Module(MODULE_TYPE _type, const std::string &_name, const std::string &_description)
        : m_type(_type), m_name(_name), m_description(_description)
    {
    }

    // cree un constructeur de module par copie
    Process::Module::Module(const Module &_module)
    {
        *this = _module;
    }

    // cree un operateur d'affectation de module
    Process::Module &Process::Module::operator=(const Module &_module)
    {
        m_type = _module.m_type;
        m_name = _module.m_name;
        m_description = _module.m_description;
        return *this;
    }

    // cree un operateur d'egalite entre deux modules
    bool Process::Module::operator==(const Module &_module) const
    {
        bool est_egal = true;
        est_egal &= (m_type == _module.m_type);
        est_egal &= (m_name == _module.m_name);
        est_egal &= (m_description == _module.m_description);
        return est_egal;
    }

    // cree un operateur de difference entre deux modules
    bool Process::Module::operator!=(const Module &_module) const
    {
        return !(*this == _module);
    }

    // charge un module par son nom
    bool Process::ModuleList::loadModuleByName(const std::string &_name, Module &_module)
    {
        auto it = std::find_if(begin(), end(), [&](const Module &_obj)
                               { return _obj.m_name == _name; });
        if (it != end() && it->m_type != MODULE_TYPE::INCONNU)
        {
            _module = *it;
            return true;
        }

        _module = at(0);
        return false;
    }
}
