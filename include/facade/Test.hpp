#pragma once

#include "facade/Facade.hpp"

namespace facade
{
// cree une facade test
class Test : public Facade
{
public:
    // cree le type d'une methode
    enum class METHOD_TYPE
    {
        INCONNU,
        HELP,
        RUN,
        NO_METHOD,
        NO_DESCRIPTION,
    };

    DECLARE_FACADE_METHOD( Test )

public:
    // execute la methode run
    virtual void onRun();
};
} // namespace facade
