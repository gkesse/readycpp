#pragma once

#include "facade/Facade.hpp"

namespace facade::server
{
// cree un module facade
class Boost : public Facade
{
public:
    // cree le type d'une methode
    enum class METHOD_TYPE
    {
        INCONNU,
        HELP,
        RUN,
    };

    DECLARE_FACADE_METHOD( Boost )

public:
    // execute la methode run
    virtual void onRun();
};
} // namespace facade::server
