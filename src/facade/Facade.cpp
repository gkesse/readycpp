#include "facade/Facade.hpp"

namespace facade
{
// cree un constructeur de facade par donnees
Facade::Facade( process::Process& _process ) : m_process( _process ) {}

// cree un destructeur de facade
Facade::~Facade() {}
} // namespace facade
