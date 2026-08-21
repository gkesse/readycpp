#include "facade/Facade.hpp"

namespace facade
{
// cree un constructeur de facade par donnees
Facade::Facade( Process& _process ) : m_process( _process ) {}

// cree un destructeur de facade
Facade::~Facade() {}

// recupere le process
Facade::Process& Facade::getProcess()
{
    return m_process;
}
} // namespace facade
