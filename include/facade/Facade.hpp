#pragma once

#include "process/Process.hpp"

namespace facade
{
// cree un module facade
class Facade
{
public:
    // cree les types personnalises
    using Process   = process::Process;
    using ArgList   = Process::ArgList;
    using Param     = std::string;
    using ParamList = std::vector<Param>;

public:
    // cree un constructeur de facade par donnees
    explicit Facade( Process& _process );
    // cree un destructeur de facade
    ~Facade();
    // recupere le process
    Process& getProcess();
    // execute la facade
    virtual void run() = 0;

protected:
    // affiche l'aide
    virtual void runHelp() = 0;
    // initialise la liste des methodes
    virtual void initMethodListe() = 0;

protected:
    Process& m_process;
};
} // namespace facade
