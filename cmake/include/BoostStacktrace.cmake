# ============================================================
#  Boost.Stacktrace (addr2line backend) — ARM / x86 compatible
#  Compatible CMake >= 3.30 (FindBoost removed, CMP0167)
# ============================================================

# Détection architecture (ARM vs x86)
if(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(BOOST_STACKTRACE_LIB "/usr/lib/aarch64-linux-gnu/libboost_stacktrace_addr2line.so")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm")
    set(BOOST_STACKTRACE_LIB "/usr/lib/arm-linux-gnueabihf/libboost_stacktrace_addr2line.so")
else()
    # x86_64
    set(BOOST_STACKTRACE_LIB "/usr/lib/x86_64-linux-gnu/libboost_stacktrace_addr2line.so")
endif()

# Vérification existence
if(NOT EXISTS ${BOOST_STACKTRACE_LIB})
    message(FATAL_ERROR "Boost.Stacktrace addr2line introuvable: ${BOOST_STACKTRACE_LIB}")
endif()

# Import manuel (méthode recommandée CMake >= 3.30)
add_library(boost_stacktrace_addr2line SHARED IMPORTED)

set_target_properties(boost_stacktrace_addr2line PROPERTIES
    IMPORTED_LOCATION "${BOOST_STACKTRACE_LIB}"
    INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)

# Fonction d’inclusion pour ReadyCPP
function(use_boost_stacktrace TARGET)
    target_link_libraries(${TARGET} PRIVATE boost_stacktrace_addr2line)
endfunction()
