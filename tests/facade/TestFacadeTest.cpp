#include "factory/facade/Test.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace facade
{
// cree la classe de fixture
class TestFacadeTest : public ::testing::Test
{
protected:
    // initialise le test avant son execution
    void SetUp() override {}
    // nettoye le test apres son execution
    void TearDown() override {}
};

DEFINE_TESTS_FACADE( TestFacadeTest, Test, Test, "test" )
DEFINE_TESTS_FACADE_CALL_METHOD( TestFacadeTest, Test, "test", "run", onRun )

// teste l'utilisation d'une facade differente
TEST_F( TestFacadeTest, Test_Utilisation_Facade_Differente )
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
            Process process( { "setup", "server_boost" } );
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

// teste l'execution de la facade run
TEST_F( TestFacadeTest, Test_Execution_Facade_Run )
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
