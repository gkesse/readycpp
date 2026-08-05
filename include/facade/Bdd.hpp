#pragma once

#include "facade/Facade.hpp"

namespace facade
{
    // cree un module facade
    class Bdd : public Facade
    {
    public:
        // cree un constructeur de facade bdd par donnees
        explicit Bdd(process::Process &_process);
        // cree un destructeur de facade bdd
        ~Bdd();
        // execute la facade bdd
        void run() override;
    };
}
