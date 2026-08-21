#include "process/Process.hpp"
#include "tools/string/Tools.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace process
{
// cree la classe de fixture
class TestProcess : public ::testing::Test
{
protected:
    // initialise le test avant son execution
    void SetUp() override {}
    // nettoye le test apres son execution
    void TearDown() override {}
};

// teste la creation d'un process invalide
TEST_F( TestProcess, Test_Creation_Process_Invalide )
{
    // definit le message d'erreur de l'exception
    const std::string DEF_MESSAGE_ERREUR_EXCEPTION = "Le chargement du module a echoue.|function={process::Process::Process()}";

    {
        try
        {
            // cree le module process
            Process process( {} );
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch ( const exception::Exception& e )
        {
            // teste la capture de l'exception levee
            EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );
        }
        catch ( const std::exception& e )
        {
            // teste la capture de l'exception levee
            EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch ( ... )
        {
            // teste la capture de l'exception levee
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
    }
    {
        try
        {
            // cree le module process
            Process process( { "" } );
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch ( const exception::Exception& e )
        {
            // teste la capture de l'exception levee
            EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );
        }
        catch ( const std::exception& e )
        {
            // teste la capture de l'exception levee
            EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch ( ... )
        {
            // teste la capture de l'exception levee
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
    }
}

// teste le nombre de modules
TEST_F( TestProcess, Test_Nombre_Modules )
{
    // cree le module process
    Process process( { "setup" } );

    // teste le nombre de modules
    EXPECT_TRUE( process.getModuleListe().size() >= 3 );
}

// teste la position du module inconnu
TEST_F( TestProcess, Test_Position_Module_Inconnu )
{
    //  cree les types personnalises
    using Module      = Process::Module;
    using MODULE_TYPE = Process::MODULE_TYPE;

    // cree le module inconnu
    Module DEF_MODULE_INCONNU = { MODULE_TYPE::INCONNU, "inconnu", "Le module est inconnu." };

    // cree le module process
    Process process( { "setup" } );

    // teste le module inconnu
    EXPECT_TRUE( process.getModuleListe().at( 0 ) == DEF_MODULE_INCONNU );
}

// teste la position du module d'aide
TEST_F( TestProcess, Test_Position_Module_Aide )
{
    //  cree les types personnalises
    using Module      = Process::Module;
    using MODULE_TYPE = Process::MODULE_TYPE;

    // cree le module d'aide
    Module DEF_MODULE_HELP = { MODULE_TYPE::HELP, "help", "Affiche l'aide." };

    // cree le module process
    Process process( { "setup" } );

    // teste le module d'aide
    EXPECT_TRUE( process.getModuleListe().at( 1 ) == DEF_MODULE_HELP );
}

// teste la position du module de test
TEST_F( TestProcess, Test_Position_Module_Test )
{
    //  cree les types personnalises
    using Module      = Process::Module;
    using MODULE_TYPE = Process::MODULE_TYPE;

    // cree le module de test
    Module DEF_MODULE_TEST = { MODULE_TYPE::TEST, "test", "Execute le module de test." };

    // cree le module process
    Process process( { "setup" } );

    // teste le module de test
    EXPECT_TRUE( process.getModuleListe().at( 2 ) == DEF_MODULE_TEST );
}

// teste l'affichage du menu d'aide
TEST_F( TestProcess, Test_Affichage_Menu_Aide )
{
    //  cree les types personnalises
    using Module = Process::Module;

    // definit l'entete du menu d'aide
    const std::string DEF_HELP_MENU_HEADER = "Usage: readycpp <module> <method> [params]";

    // definit le module du menu d'aide
    const std::string DEF_HELP_MENU_MODULE = "<module>  : Indique le module (obligatoire).";

    // cree le process
    Process process( { "setup" } );

    // initialise la capture de la sortie standard
    testing::internal::CaptureStdout();

    // affiche l'aide
    process.run();

    // recupere la capture de la sortie standard
    std::string output = testing::internal::GetCapturedStdout();

    // cree un tools_string
    tools::string::Tools tools_string;

    // teste l'execution de la methode
    EXPECT_TRUE( tools_string.contains( output, DEF_HELP_MENU_HEADER ) );
    EXPECT_TRUE( tools_string.contains( output, DEF_HELP_MENU_MODULE ) );
}

// teste l'egalite entre 2 modules
TEST_F( TestProcess, Test_Egalite_Modules )
{
    // cree les types personnalises
    using Module      = Process::Module;
    using MODULE_TYPE = Process::MODULE_TYPE;

    // cree le module d'aide ok (1, 1)
    const Module DEF_MODULE_HELP_OK_1_1 = { MODULE_TYPE::HELP, "MODULE_NAME_1", "MODULE_DESCRIPTION_1" };

    // cree le module de test nok (1, 1)
    const Module DEF_MODULE_TEST_NOK_1_1 = { MODULE_TYPE::TEST, "MODULE_NAME_1", "MODULE_DESCRIPTION_1" };

    // cree le module d'aide nok (2, 1)
    const Module DEF_MODULE_HELP_NOK_2_1 = { MODULE_TYPE::HELP, "MODULE_NAME_2", "MODULE_DESCRIPTION_1" };

    // cree le module d'aide nok (1, 2)
    const Module DEF_MODULE_HELP_NOK_1_2 = { MODULE_TYPE::HELP, "MODULE_NAME_1", "MODULE_DESCRIPTION_2" };

    // teste l'egalite entre 2 modules
    EXPECT_TRUE( DEF_MODULE_HELP_OK_1_1 == DEF_MODULE_HELP_OK_1_1 );
    EXPECT_TRUE( DEF_MODULE_HELP_OK_1_1 != DEF_MODULE_TEST_NOK_1_1 );
    EXPECT_TRUE( DEF_MODULE_HELP_OK_1_1 != DEF_MODULE_HELP_NOK_2_1 );
    EXPECT_TRUE( DEF_MODULE_HELP_OK_1_1 != DEF_MODULE_HELP_NOK_1_2 );
}

// teste le chargement d'un module valide
TEST_F( TestProcess, Test_Chargement_Module_Valide )
{
    // cree les types personnalises
    using MODULE_TYPE = Process::MODULE_TYPE;
    using Module      = Process::Module;

    // definit le module d'aide
    const Module DEF_MODULE_HELP = { MODULE_TYPE::HELP, "help", "Affiche l'aide." };
    // definit le module de test
    const Module DEF_MODULE_TEST = { MODULE_TYPE::TEST, "test", "Execute le module de test." };

    {
        // cree le process
        Process process( { "setup" } );
        // teste le chargement du module d'aide
        EXPECT_TRUE( process.getModule() == DEF_MODULE_HELP );
    }
    {
        // cree le process
        Process process( { "setup", "help" } );
        // teste le chargement du module d'aide
        EXPECT_TRUE( process.getModule() == DEF_MODULE_HELP );
    }
    {
        // cree le process
        Process process( { "setup", "test" } );
        // teste le chargement du module de test
        EXPECT_TRUE( process.getModule() == DEF_MODULE_TEST );
    }
}

// teste le chargement d'un module invalide
TEST_F( TestProcess, Test_Chargement_Module_Invalide )
{
    // definit le message d'erreur de l'exception
    const std::string DEF_MESSAGE_ERREUR_EXCEPTION = "Le chargement du module a echoue.|function={process::Process::Process()}";

    {
        try
        {
            // cree le process
            Process process( { "setup", "inconnu" } );
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch ( const exception::Exception& e )
        {
            // teste la capture de l'exception levee
            EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );
        }
        catch ( const std::exception& e )
        {
            // teste la capture de l'exception levee
            EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch ( ... )
        {
            // teste la capture de l'exception levee
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
    }
    {
        try
        {
            // cree le process
            Process process( { "setup", "no_module" } );
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch ( const exception::Exception& e )
        {
            // teste la capture de l'exception levee
            EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );
        }
        catch ( const std::exception& e )
        {
            // teste la capture de l'exception levee
            EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch ( ... )
        {
            // teste la capture de l'exception levee
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
    }
}
} // namespace process
