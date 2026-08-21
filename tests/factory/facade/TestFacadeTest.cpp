#include "factory/facade/Test.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace factory::facade
{
// cree la classe de fixture
class TestFactoryFacadeTest : public ::testing::Test
{
protected:
    // initialise le test avant son execution
    void SetUp() override {}
    // nettoye le test apres son execution
    void TearDown() override {}
};

DEFINE_TESTS_FACADE_FACTORY( TestFactoryFacadeTest, Test, Test, "test" )
DEFINE_TESTS_FACADE_FACTORY_CALL_METHOD( TestFactoryFacadeTest, Test, "test", "run", onRun )

// teste la creation d'une factory pour une methode non definie
TEST_F( TestFactoryFacadeTest, Test_Creation_Factory_Methode_Non_Definie )
{
    // cree les types personnalises
    using Process = process::Process;
    using Facade  = ::facade::Test;
    using Factory = factory::facade::Test;

    // definit le message d'erreur de l'exception
    const std::string DEF_MESSAGE_ERREUR_EXCEPTION = "Le chargement de la factory a echoue.|function={factory::facade::Test::Test()}";

    {
        try
        {
            // cree le process
            Process process( { "setup", "test", "no_method" } );
            // cree la facade
            Facade facade( process );
            // cree la factory
            Factory factory( facade );
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
} // namespace factory::facade
