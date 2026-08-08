# active ou desactive l'utilisation de la librairie
option(WITH_BOOST_STACKTRACE "Active l'utilisation de librairie Boost.Stacktrace" ON)

# arrete la recherche de la librairie
if(NOT WITH_BOOST_STACKTRACE)
    message(STATUS "La librairie Boost.Stacktrace est desactive (WITH_BOOST_STACKTRACE=OFF)")
    return()
endif()

# definit les chemins de recherche de la librairie selon l'architecture
set(DEF_BOOST_SEARCH_PATHS
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/aarch64-linux-gnu
    /usr/lib/arm-linux-gnueabihf
    ${CMAKE_INSTALL_PREFIX}/lib
)

# recherche la librairie dans les chemins selon l'architecture
find_library(DEF_BOOST_STACKTRACE_ADDR2LINE
    NAMES boost_stacktrace_addr2line
    PATHS ${DEF_BOOST_SEARCH_PATHS}
    NO_DEFAULT_PATH
)

# recherche la librairie dans les chemins par defaut
if(NOT DEF_BOOST_STACKTRACE_ADDR2LINE)
    find_library(DEF_BOOST_STACKTRACE_ADDR2LINE
        NAMES boost_stacktrace_addr2line
    )
endif()

# affiche une erreur fatale si la librairie est introuvable
if(NOT DEF_BOOST_STACKTRACE_ADDR2LINE)
    message(FATAL_ERROR "Le module Boost.Stacktrace est introuvable.")
endif()

# importe la librairie
add_library(boost_stacktrace_addr2line SHARED IMPORTED)
set_target_properties(boost_stacktrace_addr2line PROPERTIES
    IMPORTED_LOCATION "${DEF_BOOST_STACKTRACE_ADDR2LINE}"
    INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)

# lie la librairie a la cible
function(use_boost_stacktrace TARGET)
    target_link_libraries(${TARGET} PRIVATE boost_stacktrace_addr2line)
endfunction()
