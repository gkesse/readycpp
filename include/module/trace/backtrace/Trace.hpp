#pragma once

#include <link.h>
#include <string>

namespace module::trace::backtrace
{
    // cree un module trace
    class Trace
    {
    public:
        // initialise le nom du binaire
        static void setBinaryName(const std::string &_binary_name);
        // affiche la pile des appels
        static void print();

    private:
        // charge l'adresse de base du binaire
        static void loadBinaryBase();
        // charge l'adresse de base du binaire
        static int onLoadBinaryBase(dl_phdr_info *info, size_t, void *);
        // formate la trace de sortie
        static std::string formatAddr2Line(uintptr_t corrected);

    private:
        static uintptr_t m_binary_base;
        static std::string m_binary_name;
    };
}
