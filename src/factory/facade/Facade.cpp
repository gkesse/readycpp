#include "factory/facade/Facade.hpp"

#include "facade/Test.hpp"
#include "facade/server/Boost.hpp"

namespace factory::facade
{
// cree un constructeur de facade par donnees
Facade::Facade( Process& _process ) : m_process( _process )
{
    initFactoryMap();
    if ( !loadFactoryFunc( m_factory_func ) )
    {
        throw exception::Exception( "Le chargement de la factory a echoue.|function={factory::facade::Facade::Facade()}" );
    }
}

// cree un destructeur de facade
Facade::~Facade() {}

// cree la facade
Facade::sFacade Facade::create()
{
    return m_factory_func();
}

// recupere la map de factory
Facade::FactoryMap& Facade::getFactoryMap()
{
    return m_factory_map;
}

// recupere la map de factory
const Facade::FactoryMap& Facade::getFactoryMap() const
{
    return m_factory_map;
}

// initialise la factory map
void Facade::initFactoryMap()
{
    m_factory_map[MODULE_TYPE::TEST]         = [&]() { return std::make_shared<::facade::Test>( m_process ); };
    m_factory_map[MODULE_TYPE::SERVER_BOOST] = [&]() { return std::make_shared<::facade::server::Boost>( m_process ); };
}

// charge la factory fonction
bool Facade::loadFactoryFunc( FactoryFunc& _factory_func ) const
{
    if ( m_factory_map.count( m_process.getModule().m_type ) )
    {
        _factory_func = m_factory_map.at( m_process.getModule().m_type );
        return true;
    }
    return false;
}
} // namespace factory::facade
