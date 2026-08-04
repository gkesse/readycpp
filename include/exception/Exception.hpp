#pragma once

#include <string>
#include <exception>

namespace exception
{
    // cree un module exception
    class Exception : public std::exception
    {
    public:
        // cree un constructeur d'exception par defaut
        explicit Exception();
        // cree un constructeur d'exception par donnees
        explicit Exception(const std::string &_msg);
        // cree un destructeur d'exception
        ~Exception();
        // recupere le message d'exception
        const char *what() const noexcept override;

    private:
        std::string m_msg;
    };
}
