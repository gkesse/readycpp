#include "factory/facade/server/Boost.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace facade::server
{
// cree la classe de fixture
class TestFacadeServerBoost : public ::testing::Test
{
protected:
    // initialise le test avant son execution
    void SetUp() override {}
    // nettoye le test apres son execution
    void TearDown() override {}
};

DEFINE_TESTS_FACADE( TestFacadeServerBoost, server::Boost, Boost, "server_boost" )
DEFINE_TESTS_FACADE_CALL_METHOD( TestFacadeServerBoost, server::Boost, "server_boost", "run", onRun )
} // namespace facade::server
