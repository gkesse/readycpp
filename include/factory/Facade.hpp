#pragma once

#include "facade/Facade.hpp"
#include "process/Process.hpp"

#ifdef UNIT_TEST
#include <gtest/gtest_prod.h>
#endif

#include <functional>
#include <map>
#include <memory>

namespace factory
{
// cree un module facade
class Facade
{
#ifdef UNIT_TEST
    friend class TestFacadeFactory;
    FRIEND_TEST( TestFacadeFactory, Test_Chargement_Factory );
#endif

public:
    using Process     = process::Process;
    using MODULE_TYPE = process::Process::MODULE_TYPE;
    using sFacade     = std::shared_ptr<facade::Facade>;
    using FactoryFunc = std::function<sFacade()>;
    using FactoryMap  = std::map<MODULE_TYPE, FactoryFunc>;

public:
    // cree un constructeur de facade par donnees
    explicit Facade( Process& _process );
    // cree un destructeur de facade
    ~Facade();
    // cree la facade
    sFacade create();

private:
    // initialise la factory map
    void initFactoryMap();
    // charge la factory fonction
    bool loadFactoryFunc( FactoryFunc& _factory_func ) const;

private:
    Process&    m_process;
    FactoryMap  _factory_map;
    FactoryFunc m_factory_func;
};
} // namespace factory
