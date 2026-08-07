#include <module/trace/boost/Trace.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace module::trace::boosttrace
{
    // cree la classe de fixture
    class TestTraceBoosttrace : public ::testing::Test
    {
    protected:
        // initialise le test avant son execution
        void SetUp() override {}
        // nettoye le test apres son execution
        void TearDown() override {}
    };

    // teste l'affichage de la pile des appels
    TEST_F(TestTraceBoosttrace, Test_Affichage_Pile_Appels)
    {
        // affiche la pile des appels
        Trace::print();
    }
}
