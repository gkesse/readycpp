#pragma once

#include <string>

namespace tools::string
{
// cree un module tools
class Tools
{
public:
    // cree un constructeur de tools par defaut
    explicit Tools();
    // cree un destructeur de process
    ~Tools();
    // verifie si une chaine contient une autre chaine
    bool contains( const std::string& _this, const std::string& _string ) const;
};
} // namespace tools::string
