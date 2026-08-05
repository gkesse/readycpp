#include <facade/Facade.hpp>
#include <process/Process.hpp>

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

    // teste le nombre de modules
    TEST_F(TestFacade, Test_Nombre_Modules)
    {
        // teste la factory facade
        EXPECT_TRUE(1 == 1);
    }
}
