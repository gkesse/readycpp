#pragma once

#include "facade/Facade.hpp"

namespace factory::facade
{
// cree une factory facade
class Facade
{
public:
    // cree les types personnalises
    using Process     = process::Process;
    using MODULE_TYPE = process::Process::MODULE_TYPE;
    using sFacade     = std::shared_ptr<::facade::Facade>;
    using FactoryFunc = std::function<sFacade()>;
    using FactoryMap  = std::map<MODULE_TYPE, FactoryFunc>;

public:
    // cree un constructeur de facade par donnees
    explicit Facade( Process& _process );
    // cree un destructeur de facade
    ~Facade();
    // cree la facade
    sFacade create();
    // recupere la map de factory
    FactoryMap& getFactoryMap();
    // recupere la map de factory
    const FactoryMap& getFactoryMap() const;

private:
    // initialise la factory map
    void initFactoryMap();
    // charge la factory fonction
    bool loadFactoryFunc( FactoryFunc& _factory_func ) const;

private:
    Process&    m_process;
    FactoryMap  m_factory_map;
    FactoryFunc m_factory_func;
};
} // namespace factory::facade
