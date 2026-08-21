#include "exception/Exception.hpp"
#include "facade/Test.hpp"
#include "factory/facade/Facade.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace factory::facade
{
// cree la classe de fixture
class TestFactoryFacade : public ::testing::Test
{
protected:
    // initialise le test avant son execution
    void SetUp() override {}
    // nettoye le test apres son execution
    void TearDown() override {}
};

// teste le chargement d'une factory invalide
TEST_F( TestFactoryFacade, Test_Chargement_Factory_Invalide )
{
    // cree les types personnalises
    using Process = process::Process;
    using Factory = factory::facade::Facade;

    // definit le message d'erreur de l'exception
    const std::string DEF_MESSAGE_ERREUR_EXCEPTION = "Le chargement de la factory a echoue.|function={factory::facade::Facade::Facade()}";

    {
        try
        {
            // cree le process
            Process process( { "setup" } );
            // cree la factory
            Factory factory( process );
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

// teste la creation d'une factory valide
TEST_F( TestFactoryFacade, Test_Creation_Factory_Valide )
{
    // cree les types personnalises
    using Process = process::Process;
    using sFacade = std::shared_ptr<::facade::Test>;

    // cree le process
    Process process( { "setup", "test" } );

    // cree la factory facade
    Facade factory( process );

    // cree la facade
    sFacade facade = std::dynamic_pointer_cast<::facade::Test>( factory.create() );

    EXPECT_TRUE( facade != nullptr );
}
} // namespace factory::facade
