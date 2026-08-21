#include "factory/facade/server/Boost.hpp"

namespace factory::facade::server
{
DEFINE_FACADE_FACTORY( server::Boost, Boost )

// initialise la factory map
void Boost::initFactoryMap()
{
    m_factory_map[METHOD_TYPE::RUN] = [&]() { m_facade.onRun(); };
}
} // namespace factory::facade::server
