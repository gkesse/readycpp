#pragma once

// declare la structure d'une methode
#define DECLARE_FACADE_METHOD( _classname )                                                                                                                                                            \
public:                                                                                                                                                                                                \
    /* cree les types personnalises */                                                                                                                                                                 \
    using Process     = process::Process;                                                                                                                                                              \
    using MODULE_TYPE = process::Process::MODULE_TYPE;                                                                                                                                                 \
                                                                                                                                                                                                       \
    /* cree la structure d'une methode */                                                                                                                                                              \
    struct Method                                                                                                                                                                                      \
    {                                                                                                                                                                                                  \
        METHOD_TYPE m_type;                                                                                                                                                                            \
        std::string m_name;                                                                                                                                                                            \
        std::string m_description;                                                                                                                                                                     \
                                                                                                                                                                                                       \
        /* cree un constructeur de module par defaut */                                                                                                                                                \
        Method();                                                                                                                                                                                      \
        /* cree un constructeur de module par donnees */                                                                                                                                               \
        Method( METHOD_TYPE _type, const std::string& _name, const std::string& _description );                                                                                                        \
        /* cree un constructeur de module par copie */                                                                                                                                                 \
        Method( const Method& _method );                                                                                                                                                               \
        /* cree un operateur d'affectation de module */                                                                                                                                                \
        Method& operator=( const Method& _method );                                                                                                                                                    \
        /* cree un operateur d'egalite entre deux modules */                                                                                                                                           \
        bool operator==( const Method& _method ) const;                                                                                                                                                \
        /* cree un operateur de difference entre deux modules */                                                                                                                                       \
        bool operator!=( const Method& _method ) const;                                                                                                                                                \
    };                                                                                                                                                                                                 \
                                                                                                                                                                                                       \
    /* cree une lsite de structure de methode */                                                                                                                                                       \
    struct MethodList : public std::vector<Method>                                                                                                                                                     \
    {                                                                                                                                                                                                  \
        /* charge une methode par son nom */                                                                                                                                                           \
        bool loadMethodByName( const std::string& _name, Method& _method ) const;                                                                                                                      \
        /* charge une methode par son type */                                                                                                                                                          \
        bool loadMethodByType( const METHOD_TYPE& _type, Method& _method ) const;                                                                                                                      \
    };                                                                                                                                                                                                 \
                                                                                                                                                                                                       \
public:                                                                                                                                                                                                \
    /* cree un constructeur de facade par donnees */                                                                                                                                                   \
    explicit _classname( Process& _process );                                                                                                                                                          \
    /* cree un destructeur de facade */                                                                                                                                                                \
    ~_classname();                                                                                                                                                                                     \
    /* execute la facade */                                                                                                                                                                            \
    void run() override;                                                                                                                                                                               \
    /* recupere la methode */                                                                                                                                                                          \
    Method& getMethod();                                                                                                                                                                               \
    /* recupere la methode */                                                                                                                                                                          \
    const Method& getMethod() const;                                                                                                                                                                   \
    /* recupere la liste des methodes */                                                                                                                                                               \
    MethodList& getMethodListe();                                                                                                                                                                      \
    /* recupere la liste des methodes */                                                                                                                                                               \
    const MethodList& getMethodListe() const;                                                                                                                                                          \
    /* recupere la description de la methode */                                                                                                                                                        \
    std::string getDescription( const METHOD_TYPE& _type ) const;                                                                                                                                      \
                                                                                                                                                                                                       \
private:                                                                                                                                                                                               \
    /* charge la methode a partir des arguments cli */                                                                                                                                                 \
    bool loadMethod( Method& _method );                                                                                                                                                                \
                                                                                                                                                                                                       \
protected:                                                                                                                                                                                             \
    /* affiche l'aide */                                                                                                                                                                               \
    void runHelp() override;                                                                                                                                                                           \
    /* initialise la liste des methodes */                                                                                                                                                             \
    void initMethodListe() override;                                                                                                                                                                   \
                                                                                                                                                                                                       \
private:                                                                                                                                                                                               \
    Method     m_method;                                                                                                                                                                               \
    MethodList m_method_list;

// definit la structure d'une methode
#define DEFINE_FACADE_METHOD( _namespace, _classname, _module_type )                                                                                                                                   \
    /* cree un constructeur de methode par defaut */                                                                                                                                                   \
    _namespace::Method::Method() : m_type( METHOD_TYPE::INCONNU ), m_name( "inconnu" ), m_description( "Le methode est inconnu." ) {}                                                                  \
                                                                                                                                                                                                       \
    /* cree un constructeur de methode */                                                                                                                                                              \
    _namespace::Method::Method( METHOD_TYPE _type, const std::string& _name, const std::string& _description ) : m_type( _type ), m_name( _name ), m_description( _description ) {}                    \
                                                                                                                                                                                                       \
    /* cree un constructeur de methode par copie */                                                                                                                                                    \
    _namespace::Method::Method( const Method& _method )                                                                                                                                                \
    {                                                                                                                                                                                                  \
        *this = _method;                                                                                                                                                                               \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* cree un operateur d'affectation de methode */                                                                                                                                                   \
    _classname::Method& _namespace::Method::operator=( const Method& _method )                                                                                                                         \
    {                                                                                                                                                                                                  \
        m_type        = _method.m_type;                                                                                                                                                                \
        m_name        = _method.m_name;                                                                                                                                                                \
        m_description = _method.m_description;                                                                                                                                                         \
        return *this;                                                                                                                                                                                  \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* cree un operateur d'egalite entre deux methodes */                                                                                                                                              \
    bool _namespace::Method::operator==( const Method& _method ) const                                                                                                                                 \
    {                                                                                                                                                                                                  \
        bool est_egal = true;                                                                                                                                                                          \
        est_egal &= ( m_type == _method.m_type );                                                                                                                                                      \
        est_egal &= ( m_name == _method.m_name );                                                                                                                                                      \
        est_egal &= ( m_description == _method.m_description );                                                                                                                                        \
        return est_egal;                                                                                                                                                                               \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* cree un operateur de difference entre deux methodes */                                                                                                                                          \
    bool _namespace::Method::operator!=( const Method& _method ) const                                                                                                                                 \
    {                                                                                                                                                                                                  \
        return !( *this == _method );                                                                                                                                                                  \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* charge une methode par son nom */                                                                                                                                                               \
    bool _namespace::MethodList::loadMethodByName( const std::string& _name, Method& _method ) const                                                                                                   \
    {                                                                                                                                                                                                  \
        if ( _name.empty() )                                                                                                                                                                           \
        {                                                                                                                                                                                              \
            _method = at( 1 );                                                                                                                                                                         \
            return true;                                                                                                                                                                               \
        }                                                                                                                                                                                              \
                                                                                                                                                                                                       \
        auto it = std::find_if( begin(), end(), [&]( const Method& _obj ) { return _obj.m_name == _name; } );                                                                                          \
                                                                                                                                                                                                       \
        if ( it != end() && it->m_type != METHOD_TYPE::INCONNU )                                                                                                                                       \
        {                                                                                                                                                                                              \
            _method = *it;                                                                                                                                                                             \
            return true;                                                                                                                                                                               \
        }                                                                                                                                                                                              \
                                                                                                                                                                                                       \
        _method = at( 0 );                                                                                                                                                                             \
        return false;                                                                                                                                                                                  \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* charge une methode par son type */                                                                                                                                                              \
    bool _namespace::MethodList::loadMethodByType( const METHOD_TYPE& _type, Method& _method ) const                                                                                                   \
    {                                                                                                                                                                                                  \
        auto it = std::find_if( begin(), end(), [&]( const Method& _obj ) { return _obj.m_type == _type; } );                                                                                          \
                                                                                                                                                                                                       \
        if ( it != end() )                                                                                                                                                                             \
        {                                                                                                                                                                                              \
            _method = *it;                                                                                                                                                                             \
            return true;                                                                                                                                                                               \
        }                                                                                                                                                                                              \
                                                                                                                                                                                                       \
        _method = at( 0 );                                                                                                                                                                             \
        return false;                                                                                                                                                                                  \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* cree un constructeur de facade par donnees */                                                                                                                                                   \
    _namespace::_classname( Process& _process ) : Facade( _process )                                                                                                                                   \
    {                                                                                                                                                                                                  \
        initMethodListe();                                                                                                                                                                             \
        if ( !loadMethod( m_method ) )                                                                                                                                                                 \
        {                                                                                                                                                                                              \
            throw exception::Exception( "Le chargement de la methode a echoue.|function={facade::" #_namespace "::" #_classname "()}" );                                                               \
        }                                                                                                                                                                                              \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* cree un destructeur de facade */                                                                                                                                                                \
    _namespace::~_classname() {}                                                                                                                                                                       \
                                                                                                                                                                                                       \
    /* execute la facade */                                                                                                                                                                            \
    void _namespace::run()                                                                                                                                                                             \
    {                                                                                                                                                                                                  \
        if ( m_method == m_method_list.at( 1 ) )                                                                                                                                                       \
        {                                                                                                                                                                                              \
            runHelp();                                                                                                                                                                                 \
            return;                                                                                                                                                                                    \
        }                                                                                                                                                                                              \
                                                                                                                                                                                                       \
        factory::facade::_namespace factory( *this );                                                                                                                                                  \
        factory.run();                                                                                                                                                                                 \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* recupere la methode */                                                                                                                                                                          \
    _classname::Method& _namespace::getMethod()                                                                                                                                                        \
    {                                                                                                                                                                                                  \
        return m_method;                                                                                                                                                                               \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* recupere la methode */                                                                                                                                                                          \
    const _classname::Method& _namespace::getMethod() const                                                                                                                                            \
    {                                                                                                                                                                                                  \
        return m_method;                                                                                                                                                                               \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* recupere la liste des methodes */                                                                                                                                                               \
    _classname::MethodList& _namespace::getMethodListe()                                                                                                                                               \
    {                                                                                                                                                                                                  \
        return m_method_list;                                                                                                                                                                          \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* recupere la liste des methodes */                                                                                                                                                               \
    const _classname::MethodList& _namespace::getMethodListe() const                                                                                                                                   \
    {                                                                                                                                                                                                  \
        return m_method_list;                                                                                                                                                                          \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* recupere la description de la methode */                                                                                                                                                        \
    std::string _namespace::getDescription( const METHOD_TYPE& _type ) const                                                                                                                           \
    {                                                                                                                                                                                                  \
        Method method;                                                                                                                                                                                 \
        if ( !m_method_list.loadMethodByType( _type, method ) )                                                                                                                                        \
        {                                                                                                                                                                                              \
            throw exception::Exception( "Le chargement de la methode a echoue.|function={facade::" #_namespace "::getDescription()}" );                                                                \
        }                                                                                                                                                                                              \
        return method.m_description;                                                                                                                                                                   \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* charge la methode a partir des arguments cli */                                                                                                                                                 \
    bool _namespace::loadMethod( Method& _method )                                                                                                                                                     \
    {                                                                                                                                                                                                  \
        if ( m_process.getModule().m_type != _module_type )                                                                                                                                            \
        {                                                                                                                                                                                              \
            _method = m_method_list.at( 0 );                                                                                                                                                           \
            return false;                                                                                                                                                                              \
        }                                                                                                                                                                                              \
                                                                                                                                                                                                       \
        if ( m_process.getArgListe().size() == 2 )                                                                                                                                                     \
        {                                                                                                                                                                                              \
            _method = m_method_list.at( 1 );                                                                                                                                                           \
            return true;                                                                                                                                                                               \
        }                                                                                                                                                                                              \
                                                                                                                                                                                                       \
        if ( m_process.getArgListe().size() == 2 )                                                                                                                                                     \
        {                                                                                                                                                                                              \
            _method = m_method_list.at( 1 );                                                                                                                                                           \
            return true;                                                                                                                                                                               \
        }                                                                                                                                                                                              \
                                                                                                                                                                                                       \
        std::string method_name = m_process.getArgListe()[2];                                                                                                                                          \
                                                                                                                                                                                                       \
        return m_method_list.loadMethodByName( method_name, _method );                                                                                                                                 \
    }

// ajoute une methode a la liste
#define DEFINE_FACADE_ADD_METHOD( _type, _name, _description )                                                                                                                                         \
    do                                                                                                                                                                                                 \
    {                                                                                                                                                                                                  \
        m_method_list.push_back( { _type, _name, _description } );                                                                                                                                     \
    } while ( false );

// declare la factory facade
#define DECLARE_FACADE_FACTORY( _namespace, _classname )                                                                                                                                               \
public:                                                                                                                                                                                                \
    /* cree les types personnalises */                                                                                                                                                                 \
    using Facade      = ::facade::_namespace;                                                                                                                                                          \
    using METHOD_TYPE = ::facade::_namespace::METHOD_TYPE;                                                                                                                                             \
    using FactoryFunc = std::function<void()>;                                                                                                                                                         \
    using FactoryMap  = std::map<METHOD_TYPE, FactoryFunc>;                                                                                                                                            \
                                                                                                                                                                                                       \
public:                                                                                                                                                                                                \
    /* cree un constructeur de facade par donnees */                                                                                                                                                   \
    explicit _classname( Facade& _facade );                                                                                                                                                            \
    /* cree un destructeur de facade */                                                                                                                                                                \
    ~_classname();                                                                                                                                                                                     \
    /* execute la methode */                                                                                                                                                                           \
    void run();                                                                                                                                                                                        \
    /* recupere la factory fonction */                                                                                                                                                                 \
    FactoryFunc& getFactoryFunc();                                                                                                                                                                     \
    /* recupere la factory fonction */                                                                                                                                                                 \
    const FactoryFunc& getFactoryFunc() const;                                                                                                                                                         \
                                                                                                                                                                                                       \
private:                                                                                                                                                                                               \
    /* initialise la factory map */                                                                                                                                                                    \
    void initFactoryMap();                                                                                                                                                                             \
    /* charge la factory fonction */                                                                                                                                                                   \
    bool loadFactoryFunc( FactoryFunc& _factory_func ) const;                                                                                                                                          \
                                                                                                                                                                                                       \
private:                                                                                                                                                                                               \
    Facade & m_facade;                                                                                                                                                                                 \
    FactoryMap  m_factory_map;                                                                                                                                                                         \
    FactoryFunc m_factory_func;

// definit la factory facade
#define DEFINE_FACADE_FACTORY( _namespace, _classname )                                                                                                                                                \
    /* cree un constructeur de facade par donnees */                                                                                                                                                   \
    _namespace::_classname( Facade& _facade ) : m_facade( _facade )                                                                                                                                    \
    {                                                                                                                                                                                                  \
        initFactoryMap();                                                                                                                                                                              \
        if ( !loadFactoryFunc( m_factory_func ) )                                                                                                                                                      \
        {                                                                                                                                                                                              \
            throw exception::Exception( "Le chargement de la factory a echoue.|function={factory::facade::" #_namespace "::" #_classname "()}" );                                                      \
        }                                                                                                                                                                                              \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* cree un destructeur de facade */                                                                                                                                                                \
    _namespace::~_classname() {}                                                                                                                                                                       \
                                                                                                                                                                                                       \
    /* execute la methode */                                                                                                                                                                           \
    void _namespace::run()                                                                                                                                                                             \
    {                                                                                                                                                                                                  \
        m_factory_func();                                                                                                                                                                              \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* recupere la factory fonction */                                                                                                                                                                 \
    _classname::FactoryFunc& _namespace::getFactoryFunc()                                                                                                                                              \
    {                                                                                                                                                                                                  \
        return m_factory_func;                                                                                                                                                                         \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* recupere la factory fonction */                                                                                                                                                                 \
    const _classname::FactoryFunc& _namespace::getFactoryFunc() const                                                                                                                                  \
    {                                                                                                                                                                                                  \
        return m_factory_func;                                                                                                                                                                         \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* charge la factory fonction */                                                                                                                                                                   \
    bool _namespace::loadFactoryFunc( FactoryFunc& _factory_func ) const                                                                                                                               \
    {                                                                                                                                                                                                  \
        if ( m_factory_map.count( m_facade.getMethod().m_type ) )                                                                                                                                      \
        {                                                                                                                                                                                              \
            _factory_func = m_factory_map.at( m_facade.getMethod().m_type );                                                                                                                           \
            return true;                                                                                                                                                                               \
        }                                                                                                                                                                                              \
        return false;                                                                                                                                                                                  \
    }
