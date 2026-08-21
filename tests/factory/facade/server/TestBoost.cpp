#include "exception/Exception.hpp"
#include "factory/facade/server/Boost.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace factory::facade::server
{
// cree la classe de fixture
class TestFactoryFacadeServerBoost : public ::testing::Test
{
protected:
    // initialise le test avant son execution
    void SetUp() override {}
    // nettoye le test apres son execution
    void TearDown() override {}
};

DEFINE_TESTS_FACADE_FACTORY( TestFactoryFacadeServerBoost, server::Boost, Boost, "server_boost" )
DEFINE_TESTS_FACADE_FACTORY_CALL_METHOD( TestFactoryFacadeServerBoost, server::Boost, "server_boost", "run", onRun )
} // namespace factory::facade::server
