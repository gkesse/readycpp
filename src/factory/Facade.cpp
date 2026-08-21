#include "factory/Facade.hpp"

#include "exception/Exception.hpp"
#include "facade/Bdd.hpp"

namespace factory
{
// cree un constructeur de facade par donnees
Facade::Facade( Process& _process ) : m_process( _process )
{
    initFactoryMap();
    if ( !loadFactoryFunc( m_factory_func ) )
    {
        throw exception::Exception( "Le chargement de la factory fonction a echoue." );
    }
}

// cree un destructeur de facade
Facade::~Facade() {}

// cree la facade
Facade::sFacade Facade::create()
{
    return m_factory_func();
}

// initialise la factory map
void Facade::initFactoryMap()
{
    _factory_map[MODULE_TYPE::BDD] = [&]() { return std::make_shared<facade::Bdd>( m_process ); };
}

// charge la factory fonction
bool Facade::loadFactoryFunc( FactoryFunc& _factory_func ) const
{
    if ( _factory_map.count( m_process.m_module.m_type ) )
    {
        _factory_func = _factory_map.at( m_process.m_module.m_type );
        return true;
    }
    return false;
}
} // namespace factory
