#include "module/trace/backtrace/Trace.hpp"

#include "exception/Exception.hpp"

#include <cstring>
#include <execinfo.h>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace module::trace::backtrace
{
uintptr_t   Trace::m_binary_base = 0;
std::string Trace::m_binary_name = "";

// initialise le nom du binaire
void Trace::setBinaryName( const std::string& _binary_name )
{
    m_binary_name = _binary_name;
}

// affiche la pile des appels
void Trace::print()
{
    if ( m_binary_name.empty() )
    {
        throw exception::Exception( "Le nom du binaire est obligatoire.|function={module::trace::backtrace::Trace::print()}" );
    }

    loadBinaryBase();

    void* buffer[64];
    int   size = ::backtrace( buffer, 64 );

    std::cout << "Stack Trace:" << std::endl;

    for ( int i = 0; i < size; ++i )
    {
        uintptr_t addr      = reinterpret_cast<uintptr_t>( buffer[i] );
        uintptr_t corrected = addr - m_binary_base;

        // ignore les adresses hors du binaire
        if ( corrected == 0 || corrected > 0xFFFFFFFF )
        {
            continue;
        }

        std::cout << "  " << i << ": " << formatAddr2Line( corrected ) << std::endl;
    }
}

// charge l'adresse de base du binaire
void Trace::loadBinaryBase()
{
    dl_iterate_phdr( onLoadBinaryBase, nullptr );
}

// charge l'adresse de base du binaire
int Trace::onLoadBinaryBase( struct dl_phdr_info* info, size_t, void* )
{
    // info->dlpi_name peut être vide pour le binaire principal
    if ( info->dlpi_name && std::strlen( info->dlpi_name ) > 0 )
    {
        if ( std::strstr( info->dlpi_name, "readycpp_tests" ) )
        {
            m_binary_base = info->dlpi_addr;
        }
    }
    else
    {
        // binaire principal : dlpi_name == ""
        m_binary_base = info->dlpi_addr;
    }

    return 0;
}

// formate la trace de sortie
std::string Trace::formatAddr2Line( uintptr_t corrected )
{
    std::stringstream cmd;
    cmd << "addr2line -f -C -e " << m_binary_name << " "
        << "0x" << std::hex << std::setw( 16 ) << std::setfill( '0' ) << corrected;

    FILE* fp = popen( cmd.str().c_str(), "r" );
    if ( !fp )
        return "?? -> ??:?";

    char func[512];
    char fileline[512];

    fgets( func, sizeof( func ), fp );
    fgets( fileline, sizeof( fileline ), fp );
    pclose( fp );

    std::string sfunc( func );
    std::string sfile( fileline );

    sfunc.erase( sfunc.find_last_not_of( "\n" ) + 1 );
    sfile.erase( sfile.find_last_not_of( "\n" ) + 1 );

    return sfile + " -> " + sfunc;
}
} // namespace module::trace::backtrace
