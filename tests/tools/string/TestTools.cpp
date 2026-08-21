#include "tools/string/Tools.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace tools::string
{
// cree la classe de fixture
class TestToolsString : public ::testing::Test
{
protected:
    // initialise le test avant son execution
    void SetUp() override {}
    // nettoye le test apres son execution
    void TearDown() override {}
};

// teste chaine contient une autre chaine
TEST_F( TestToolsString, Test_Chaine_Contient_Chaine )
{
    // cree un tools_string
    tools::string::Tools tools_string;

    // teste chaine contient une autre chaine
    EXPECT_TRUE( tools_string.contains( "Bonjour tout le monde", "tout" ) == true );
    EXPECT_TRUE( tools_string.contains( "Bonjour tout le monde", "Tout" ) == false );
}
} // namespace tools::string
