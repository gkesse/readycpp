#include "exception/Exception.hpp"

namespace exception
{
    // cree un constructeur d'exception par defaut
    Exception::Exception()
        : m_msg("Un probleme a ete rencontre.")
    {
    }

    // cree un constructeur d'exception par donnees
    Exception::Exception(const std::string &_msg)
        : m_msg(_msg)
    {
    }

    // cree un destructeur d'exception
    Exception::~Exception()
    {
    }

    // recupere le message d'exception
    const char *Exception::what() const noexcept
    {
        return m_msg.c_str();
    }
}
