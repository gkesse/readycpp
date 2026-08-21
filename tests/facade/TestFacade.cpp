#include "facade/Test.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace facade
{
// cree la classe de fixture
class TestFacade : public ::testing::Test
{
protected:
    // initialise le test avant son execution
    void SetUp() override {}
    // nettoye le test apres son execution
    void TearDown() override {}
};

// teste la creation d'une facade invalide
TEST_F( TestFacade, Test_Creation_Facade_Invalide )
{
    // cree les types personnalises
    using Process = process::Process;
    using Facade  = facade::Test;

    // definit le message d'erreur de l'exception
    const std::string DEF_MESSAGE_ERREUR_EXCEPTION = "Le chargement de la methode a echoue.|function={facade::Test::Test()}";

    {
        try
        {
            // cree le process
            Process process( { "setup", "test", "no_run" } );
            // cree la facade
            Facade facade( process );
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch ( const exception::Exception& e )
        {
            // teste l'exception levee
            EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );
        }
        catch ( const std::exception& e )
        {
            // teste l'exception levee
            EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch ( ... )
        {
            // teste l'exception levee
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
    }
}

// teste la lecture d'une description de methode invalide
TEST_F( TestFacade, Test_Lecture_Description_Methode_Invalide )
{
    // cree les types personnalises
    using Process     = process::Process;
    using Facade      = facade::Test;
    using METHOD_TYPE = facade::Test::METHOD_TYPE;

    // definit le message d'erreur de l'exception
    const std::string DEF_MESSAGE_ERREUR_EXCEPTION = "Le chargement de la methode a echoue.|function={facade::Test::getDescription()}";

    {
        try
        {
            // cree le process
            Process process( { "setup", "test" } );
            // cree la facade
            Facade facade( process );
            // teste la lecture de la description
            facade.getDescription( METHOD_TYPE::NO_DESCRIPTION );
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch ( const exception::Exception& e )
        {
            // teste l'exception levee
            EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );
        }
        catch ( const std::exception& e )
        {
            // teste l'exception levee
            EXPECT_TRUE( std::string( e.what() ) == DEF_MESSAGE_ERREUR_EXCEPTION );
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
        catch ( ... )
        {
            // teste l'exception levee
            FAIL() << "Exception attendue (execption::Exception) non levee.";
        }
    }
}

// teste l'egalite entre 2 methodes
TEST_F( TestFacade, Test_Egalite_Methodes )
{
    // cree les types personnalises
    using Method      = facade::Test::Method;
    using METHOD_TYPE = facade::Test::METHOD_TYPE;

    // cree la methode d'aide ok (1, 1)
    const Method DEF_METHOD_HELP_OK_1_1 = { METHOD_TYPE::HELP, "METHOD_NAME_1", "MODULE_DESCRIPTION_1" };

    // cree la methode de run nok (1, 1)
    const Method DEF_METHOD_RUN_NOK_1_1 = { METHOD_TYPE::RUN, "METHOD_NAME_1", "MODULE_DESCRIPTION_1" };

    // cree la methode d'aide nok (2, 1)
    const Method DEF_METHOD_HELP_NOK_2_1 = { METHOD_TYPE::HELP, "METHOD_NAME_2", "MODULE_DESCRIPTION_1" };

    // cree la methode d'aide nok (1, 2)
    const Method DEF_METHOD_HELP_NOK_1_2 = { METHOD_TYPE::HELP, "METHOD_NAME_1", "MODULE_DESCRIPTION_2" };

    // teste l'egalite entre 2 modules
    EXPECT_TRUE( DEF_METHOD_HELP_OK_1_1 == DEF_METHOD_HELP_OK_1_1 );
    EXPECT_TRUE( DEF_METHOD_HELP_OK_1_1 != DEF_METHOD_RUN_NOK_1_1 );
    EXPECT_TRUE( DEF_METHOD_HELP_OK_1_1 != DEF_METHOD_HELP_NOK_2_1 );
    EXPECT_TRUE( DEF_METHOD_HELP_OK_1_1 != DEF_METHOD_HELP_NOK_1_2 );
}

// teste la lecture d'une description de methode valide
TEST_F( TestFacade, Test_Lecture_Description_Methode_Valide )
{
    // cree les types personnalises
    using Process     = process::Process;
    using Facade      = facade::Test;
    using METHOD_TYPE = facade::Test::METHOD_TYPE;

    // definit la description de la methode
    const std::string DEF_DESCRIPTION_RUN = "Execute la methode de test.";

    // cree le process
    Process process( { "setup", "test" } );

    // cree la facade
    Facade facade( process );

    // teste la lecture de la description
    EXPECT_TRUE( facade.getDescription( METHOD_TYPE::RUN ) == DEF_DESCRIPTION_RUN );
}

// teste l'execution d'une facade valide
TEST_F( TestFacade, Test_Execution_Facade_Valide )
{
    // cree les types personnalises
    using Process = process::Process;
    using Facade  = facade::Test;

    // definit le message de sortie
    const std::string DEF_MESSAGE_OUTPUT = "Execution de la facade test.\n";

    // cree le process
    Process process( { "setup", "test", "run" } );

    // cree la facade
    Facade facade( process );

    // initialise la capture de la sortie standard
    testing::internal::CaptureStdout();

    // execute la facade
    facade.run();

    // recupere la capture de la sortie standard
    std::string output = testing::internal::GetCapturedStdout();

    // teste l'execution de la facade
    EXPECT_TRUE( output == DEF_MESSAGE_OUTPUT );
}
} // namespace facade
