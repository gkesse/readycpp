#pragma once

// teste le nombre de methodes
// teste la position de la methode inconnue
// teste la position de la methode d'aide
// teste l'execution de la methode d'aide
// teste la creation d'une facade invalide
#define DEFINE_TESTS_FACADE( _fixture, _namespace, _classname, _facade )                                                                                                                               \
    /* teste le nombre de methodes */                                                                                                                                                                  \
    TEST_F( _fixture, Test_Nombre_Methodes )                                                                                                                                                           \
    {                                                                                                                                                                                                  \
        /* cree les types personnalises */                                                                                                                                                             \
        using Process = process::Process;                                                                                                                                                              \
        using Facade  = facade::_namespace;                                                                                                                                                            \
                                                                                                                                                                                                       \
        /* cree le process */                                                                                                                                                                          \
        Process process( { "setup", _facade } );                                                                                                                                                       \
                                                                                                                                                                                                       \
        /* cree la facade */                                                                                                                                                                           \
        Facade facade( process );                                                                                                                                                                      \
                                                                                                                                                                                                       \
        /* teste le nombre de methodes */                                                                                                                                                              \
        EXPECT_TRUE( facade.getMethodListe().size() >= 2 );                                                                                                                                            \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* teste la position de la methode inconnue */                                                                                                                                                     \
    TEST_F( _fixture, Test_Position_Methode_Inconnue )                                                                                                                                                 \
    {                                                                                                                                                                                                  \
        /* cree les types personnalises */                                                                                                                                                             \
        using Process     = process::Process;                                                                                                                                                          \
        using Facade      = facade::_namespace;                                                                                                                                                        \
        using Method      = facade::_namespace::Method;                                                                                                                                                \
        using METHOD_TYPE = facade::_namespace::METHOD_TYPE;                                                                                                                                           \
                                                                                                                                                                                                       \
        /* cree la methode inconnue */                                                                                                                                                                 \
        const Method DEF_METHOD_INCONNU = { METHOD_TYPE::INCONNU, "inconnu", "La methode est inconnue." };                                                                                             \
                                                                                                                                                                                                       \
        /* cree le process */                                                                                                                                                                          \
        Process process( { "setup", _facade } );                                                                                                                                                       \
                                                                                                                                                                                                       \
        /* cree la facade */                                                                                                                                                                           \
        Facade facade( process );                                                                                                                                                                      \
                                                                                                                                                                                                       \
        /* teste la methode inconnue */                                                                                                                                                                \
        EXPECT_TRUE( facade.getMethodListe().at( 0 ) == DEF_METHOD_INCONNU );                                                                                                                          \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* teste la position de la methode d'aide */                                                                                                                                                       \
    TEST_F( _fixture, Test_Position_Methode_Aide )                                                                                                                                                     \
    {                                                                                                                                                                                                  \
        /* cree les types personnalises */                                                                                                                                                             \
        using Process     = process::Process;                                                                                                                                                          \
        using Facade      = facade::_namespace;                                                                                                                                                        \
        using Method      = facade::_namespace::Method;                                                                                                                                                \
        using METHOD_TYPE = facade::_namespace::METHOD_TYPE;                                                                                                                                           \
                                                                                                                                                                                                       \
        /* cree la methode inconnue */                                                                                                                                                                 \
        const Method DEF_METHOD_HELP = { METHOD_TYPE::HELP, "help", "Affiche l'aide." };                                                                                                               \
                                                                                                                                                                                                       \
        /* cree le process */                                                                                                                                                                          \
        Process process( { "setup", _facade } );                                                                                                                                                       \
                                                                                                                                                                                                       \
        /* cree la facade */                                                                                                                                                                           \
        Facade facade( process );                                                                                                                                                                      \
                                                                                                                                                                                                       \
        /* teste la methode inconnue */                                                                                                                                                                \
        EXPECT_TRUE( facade.getMethodListe().at( 1 ) == DEF_METHOD_HELP );                                                                                                                             \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* teste l'execution de la methode d'aide */                                                                                                                                                       \
    TEST_F( _fixture, Test_Execution_Methode_Aide )                                                                                                                                                    \
    {                                                                                                                                                                                                  \
        /* cree les types personnalises */                                                                                                                                                             \
        using Process = process::Process;                                                                                                                                                              \
        using Facade  = facade::_namespace;                                                                                                                                                            \
                                                                                                                                                                                                       \
        /* definit l'entete du menu d'aide */                                                                                                                                                          \
        const std::string DEF_HELP_MENU_HEADER = "Usage: readycpp <module> <method> [params]";                                                                                                         \
                                                                                                                                                                                                       \
        /* definit le module du menu d'aide */                                                                                                                                                         \
        const std::string DEF_HELP_MENU_MODULE = "<module>  : Indique le module (" _facade ").";                                                                                                       \
                                                                                                                                                                                                       \
        /* cree le process */                                                                                                                                                                          \
        Process process( { "setup", _facade } );                                                                                                                                                       \
                                                                                                                                                                                                       \
        /* cree la facade */                                                                                                                                                                           \
        Facade facade( process );                                                                                                                                                                      \
                                                                                                                                                                                                       \
        /* initialise la capture de la sortie standard */                                                                                                                                              \
        testing::internal::CaptureStdout();                                                                                                                                                            \
                                                                                                                                                                                                       \
        /* affiche la methode d'aide */                                                                                                                                                                \
        facade.run();                                                                                                                                                                                  \
                                                                                                                                                                                                       \
        /* recupere la capture de la sortie standard */                                                                                                                                                \
        std::string output = testing::internal::GetCapturedStdout();                                                                                                                                   \
                                                                                                                                                                                                       \
        /* cree un tools_string */                                                                                                                                                                     \
        tools::string::Tools tools_string;                                                                                                                                                             \
                                                                                                                                                                                                       \
        /* teste l'execution de la methode */                                                                                                                                                          \
        EXPECT_TRUE( tools_string.contains( output, DEF_HELP_MENU_HEADER ) );                                                                                                                          \
        EXPECT_TRUE( tools_string.contains( output, DEF_HELP_MENU_MODULE ) );                                                                                                                          \
    }                                                                                                                                                                                                  \
                                                                                                                                                                                                       \
    /* teste la creation d'une facade invalide */                                                                                                                                                      \
    TEST_F( _fixture, Test_Creation_Facade_Invalide )                                                                                                                                                  \
    {                                                                                                                                                                                                  \
        /* cree les types personnalises */                                                                                                                                                             \
        using Process = process::Process;                                                                                                                                                              \
        using Facade  = facade::_namespace;                                                                                                                                                            \
                                                                                                                                                                                                       \
        /* definit le message d'erreur de l'exception */                                                                                                                                               \
        const std::string DEF_MESSAGE_ERREUR_EXCEPTION = "Le chargement de la methode a echoue.|function={facade::" #_namespace "::" #_classname "()}";                                                \
        {                                                                                                                                                                                              \
            try                                                                                                                                                                                        \
            {                                                                                                                                                                                          \
                /* cree le process */                                                                                                                                                                  \
                Process process( { "setup" } );                                                                                                                                                        \
                /* cree la facade */                                                                                                                                                                   \
                Facade facade( process );                                                                                                                                                              \
                FAIL() << "Exception attendue (execption::Exception) non levee.";                                                                                                                      \
            }                                                                                                                                                                                          \
            catch ( const exception::Exception& e )                                                                                                                                                    \
            {                                                                                                                                                                                          \
                /* teste l'exception levee */                                                                                                                                                          \
                EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );                                                                                                                \
            }                                                                                                                                                                                          \
            catch ( const std::exception& e )                                                                                                                                                          \
            {                                                                                                                                                                                          \
                /* teste l'exception levee */                                                                                                                                                          \
                EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );                                                                                                                \
                FAIL() << "Exception attendue (execption::Exception) non levee.";                                                                                                                      \
            }                                                                                                                                                                                          \
            catch ( ... )                                                                                                                                                                              \
            {                                                                                                                                                                                          \
                /* teste l'exception levee */                                                                                                                                                          \
                FAIL() << "Exception attendue (execption::Exception) non levee.";                                                                                                                      \
            }                                                                                                                                                                                          \
        }                                                                                                                                                                                              \
        {                                                                                                                                                                                              \
            try                                                                                                                                                                                        \
            {                                                                                                                                                                                          \
                /* cree le process */                                                                                                                                                                  \
                Process process( { "setup", _facade, "no_run" } );                                                                                                                                     \
                /* cree la facade */                                                                                                                                                                   \
                Facade facade( process );                                                                                                                                                              \
                FAIL() << "Exception attendue (execption::Exception) non levee.";                                                                                                                      \
            }                                                                                                                                                                                          \
            catch ( const exception::Exception& e )                                                                                                                                                    \
            {                                                                                                                                                                                          \
                /* teste l'exception levee */                                                                                                                                                          \
                EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );                                                                                                                \
            }                                                                                                                                                                                          \
            catch ( const std::exception& e )                                                                                                                                                          \
            {                                                                                                                                                                                          \
                /* teste l'exception levee */                                                                                                                                                          \
                EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );                                                                                                                \
                FAIL() << "Exception attendue (execption::Exception) non levee.";                                                                                                                      \
            }                                                                                                                                                                                          \
            catch ( ... )                                                                                                                                                                              \
            {                                                                                                                                                                                          \
                /* teste l'exception levee */                                                                                                                                                          \
                FAIL() << "Exception attendue (execption::Exception) non levee.";                                                                                                                      \
            }                                                                                                                                                                                          \
        }                                                                                                                                                                                              \
    }

// teste l'appel d'une methode d'une facade
#define DEFINE_TESTS_FACADE_CALL_METHOD( _fixture, _namespace, _facade, _method, _callback )                                                                                                           \
    /* teste l'appel d'une methode d'une facade */                                                                                                                                                     \
    TEST_F( _fixture, Test_Appel_Facade_Methode_##_callback )                                                                                                                                          \
    {                                                                                                                                                                                                  \
        /* cree les types personnalises */                                                                                                                                                             \
        using Process = process::Process;                                                                                                                                                              \
        using Facade  = facade::_namespace;                                                                                                                                                            \
        using Factory = factory::facade::_namespace;                                                                                                                                                   \
                                                                                                                                                                                                       \
        /* cree le mock de facade */                                                                                                                                                                   \
        class MockFacade : public Facade                                                                                                                                                               \
        {                                                                                                                                                                                              \
        public:                                                                                                                                                                                        \
            explicit MockFacade( Process& _process ) : facade::_namespace( _process ) {}                                                                                                               \
                                                                                                                                                                                                       \
        public:                                                                                                                                                                                        \
            MOCK_METHOD( void, _callback, (), ( override ) );                                                                                                                                          \
        };                                                                                                                                                                                             \
                                                                                                                                                                                                       \
        /* cree le process */                                                                                                                                                                          \
        Process process( { "setup", _facade, _method } );                                                                                                                                              \
        /* cree la facade */                                                                                                                                                                           \
        MockFacade facade( process );                                                                                                                                                                  \
        /* cree la factory */                                                                                                                                                                          \
        Factory factory( facade );                                                                                                                                                                     \
                                                                                                                                                                                                       \
        /* teste l'execution de la facade run */                                                                                                                                                       \
        EXPECT_CALL( facade, _callback() ).Times( 1 );                                                                                                                                                 \
                                                                                                                                                                                                       \
        /* execute la facade */                                                                                                                                                                        \
        factory.run();                                                                                                                                                                                 \
    }

// teste la creation d'une factory facade invalide
#define DEFINE_TESTS_FACADE_FACTORY( _fixture, _namespace, _classname, _facade )                                                                                                                       \
    /* teste la creation d'une factory facade invalide */                                                                                                                                              \
    TEST_F( _fixture, Test_Creation_Factory_Invalide )                                                                                                                                                 \
    {                                                                                                                                                                                                  \
        /* cree les types personnalises */                                                                                                                                                             \
        using Process = process::Process;                                                                                                                                                              \
        using Facade  = ::facade::_namespace;                                                                                                                                                          \
        using Factory = factory::facade::_namespace;                                                                                                                                                   \
                                                                                                                                                                                                       \
        /* definit le message d'erreur de l'exception */                                                                                                                                               \
        const std::string DEF_MESSAGE_ERREUR_EXCEPTION = "Le chargement de la factory a echoue.|function={factory::facade::" #_namespace "::" #_classname "()}";                                       \
                                                                                                                                                                                                       \
        {                                                                                                                                                                                              \
            try                                                                                                                                                                                        \
            {                                                                                                                                                                                          \
                /* cree le process */                                                                                                                                                                  \
                Process process( { "setup", _facade } );                                                                                                                                               \
                /* cree la facade */                                                                                                                                                                   \
                Facade facade( process );                                                                                                                                                              \
                /* cree la factory */                                                                                                                                                                  \
                Factory factory( facade );                                                                                                                                                             \
                FAIL() << "Exception attendue (execption::Exception) non levee.";                                                                                                                      \
            }                                                                                                                                                                                          \
            catch ( const exception::Exception& e )                                                                                                                                                    \
            {                                                                                                                                                                                          \
                /* teste l'exception levee */                                                                                                                                                          \
                EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );                                                                                                                \
            }                                                                                                                                                                                          \
            catch ( const std::exception& e )                                                                                                                                                          \
            {                                                                                                                                                                                          \
                /* teste l'exception levee */                                                                                                                                                          \
                EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );                                                                                                                \
                FAIL() << "Exception attendue (execption::Exception) non levee.";                                                                                                                      \
            }                                                                                                                                                                                          \
            catch ( ... )                                                                                                                                                                              \
            {                                                                                                                                                                                          \
                /* teste l'exception levee */                                                                                                                                                          \
                FAIL() << "Exception attendue (execption::Exception) non levee.";                                                                                                                      \
            }                                                                                                                                                                                          \
        }                                                                                                                                                                                              \
    }

// teste l'appel d'une methode d'une factory facade
#define DEFINE_TESTS_FACADE_FACTORY_CALL_METHOD( _fixture, _namespace, _facade, _method, _callback )                                                                                                   \
    /* teste l'appel d'une methode d'une facade */                                                                                                                                                     \
    TEST_F( _fixture, Test_Appel_Facade_Methode_##_callback )                                                                                                                                          \
    {                                                                                                                                                                                                  \
        /* cree les types personnalises */                                                                                                                                                             \
        using Process = process::Process;                                                                                                                                                              \
        using Facade  = ::facade::_namespace;                                                                                                                                                          \
        using Factory = factory::facade::_namespace;                                                                                                                                                   \
                                                                                                                                                                                                       \
        /* cree le mock de facade */                                                                                                                                                                   \
        class MockFacade : public Facade                                                                                                                                                               \
        {                                                                                                                                                                                              \
        public:                                                                                                                                                                                        \
            explicit MockFacade( Process& _process ) : ::facade::_namespace( _process ) {}                                                                                                             \
                                                                                                                                                                                                       \
        public:                                                                                                                                                                                        \
            MOCK_METHOD( void, _callback, (), ( override ) );                                                                                                                                          \
        };                                                                                                                                                                                             \
                                                                                                                                                                                                       \
        /* cree le process */                                                                                                                                                                          \
        Process process( { "setup", _facade, _method } );                                                                                                                                              \
        /* cree la facade */                                                                                                                                                                           \
        MockFacade facade( process );                                                                                                                                                                  \
        /* cree la factory */                                                                                                                                                                          \
        Factory factory( facade );                                                                                                                                                                     \
                                                                                                                                                                                                       \
        /* teste l'execution de la facade run */                                                                                                                                                       \
        EXPECT_CALL( facade, _callback() ).Times( 1 );                                                                                                                                                 \
                                                                                                                                                                                                       \
        /* execute la facade */                                                                                                                                                                        \
        factory.run();                                                                                                                                                                                 \
    }
