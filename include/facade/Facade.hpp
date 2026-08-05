#pragma once

#include <process/Process.hpp>

namespace facade
{
    // cree un module facade
    class Facade
    {
    public:
        // cree un constructeur de facade par donnees
        explicit Facade(process::Process &_process);
        // cree un destructeur de facade
        ~Facade();
        // execute la facade
        virtual void run() = 0;

    protected:
        process::Process &m_process;
    };
}
