# definit la version minimale de cmake
cmake_minimum_required(VERSION 3.10.0)
# definit le nom du projet et la version
project(readycpp VERSION 0.1.0 LANGUAGES C CXX)

# definit les standards c++
set(CMAKE_CXX_STANDARD 11)
# active les standards c++
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# definit l'option WITH_DEBUG pour activer le mode debug
option(WITH_DEBUG "Active le mode debug" ON)

# ajoute le module CTest pour les tests unitaires
include(CTest)
# active le module CTest pour les tests unitaires
enable_testing()

# inclut les dependances du projet
include(cmake/include.cmake)

# definit le nom du projet pour le module CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# definit la version du projet pour le module CPack
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# definit l'adresse email du contact pour le module CPack
set(CPACK_PACKAGE_CONTACT "Gerard KESSE <contact@readydev.com>")
# definit le mainteneur du package pour le module CPack
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Gerard KESSE")
# definit l'architecture du package pour le module CPack
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "arm64")
# definit le générateur de package pour le module CPack
set(CPACK_GENERATOR "TGZ;ZIP;DEB")
# ajoute le module CPack pour la création du package
include(CPack)

# ajoute les sous-repertoires de projet
add_subdirectory(src)
add_subdirectory(tests)
