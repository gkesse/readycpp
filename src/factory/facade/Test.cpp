#include "factory/facade/Test.hpp"

namespace factory::facade
{
DEFINE_FACADE_FACTORY( Test, Test )

// initialise la factory map
void Test::initFactoryMap()
{
    m_factory_map[METHOD_TYPE::RUN] = [&]() { m_facade.onRun(); };
}
} // namespace factory::facade
