#pragma once

#include "macro/facade/macro.hpp"
#include "macro/tests/facade/macro.hpp"
#include "tools/string/Tools.hpp"

#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace exception
{
// cree un module exception
class Exception : public std::exception
{
public:
    // cree un constructeur d'exception par defaut
    explicit Exception();
    // cree un constructeur d'exception par donnees
    explicit Exception( const std::string& _msg );
    // cree un destructeur d'exception
    ~Exception();
    // recupere le message d'exception
    const char* what() const noexcept override;

private:
    std::string m_msg;
};
} // namespace exception
