#include "module/trace/boost/Trace.hpp"
#include "tools/string/Tools.hpp"

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
TEST_F( TestTraceBoosttrace, Test_Affichage_Pile_Appels )
{
    // definit le fichier du module de trace
    const std::string DEF_TRACE_FILENAME = "src/module/trace/backtrace/Trace.cpp:33";

    // definit la fonction du module de trace
    const std::string DEF_TRACE_FUNCTION = "module::trace::backtrace::Trace::print()";

    // initialise la capture de la sortie standard
    testing::internal::CaptureStdout();

    // affiche la pile des appels
    Trace::print();

    // recupere la capture de la sortie standard
    std::string output = testing::internal::GetCapturedStdout();

    // cree un tools_string
    tools::string::Tools tools_string;

    // teste l'affichage de la pile des appels
    EXPECT_TRUE( tools_string.contains( output, DEF_TRACE_FILENAME ) );
    EXPECT_TRUE( tools_string.contains( output, DEF_TRACE_FUNCTION ) );
}
} // namespace module::trace::boosttrace
