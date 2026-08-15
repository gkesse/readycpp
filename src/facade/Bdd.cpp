#include "facade/Bdd.hpp"

#include <iostream>
#include <module/trace/backtrace/Trace.hpp>

namespace facade
{
// cree un constructeur de facade par donnees
Bdd::Bdd( process::Process& _process ) : Facade( _process ) {}

// cree un destructeur de facade
Bdd::~Bdd() {}

// execute la facade
void Bdd::run()
{
    module::trace::backtrace::Trace::print();
    std::cout << "void Bdd::run()............" << std::endl;
}
} // namespace facade
