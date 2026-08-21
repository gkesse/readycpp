#include "tools/string/Tools.hpp"

namespace tools::string
{
// cree un constructeur de tools par defaut
Tools::Tools() {}

// cree un destructeur de tools
Tools::~Tools() {}

// verifie si une chaine contient une autre chaine
bool Tools::contains( const std::string& _this, const std::string& _string ) const
{
    return ( _this.find( _string ) != std::string::npos );
}
} // namespace tools::string
