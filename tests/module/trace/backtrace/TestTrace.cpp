#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <module/trace/backtrace/Trace.hpp>

namespace module::trace::backtrace
{
// cree la classe de fixture
class TestTraceBacktrace : public ::testing::Test
{
protected:
    // initialise le test avant son execution
    void SetUp() override {}
    // nettoye le test apres son execution
    void TearDown() override {}
};

// teste l'affichage de la pile des appels
TEST_F( TestTraceBacktrace, Test_Affichage_Pile_Appels )
{
    // affiche la pile des appels
    Trace::print();
}
} // namespace module::trace::backtrace
