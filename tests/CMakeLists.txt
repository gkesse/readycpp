# definit le nom du projet
project(readycpp_tests)

# active le mode debug de googletests si l'option WITH_DEBUG est activée
if(WITH_DEBUG)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# ajoute le module FetchContent pour télécharger et inclure des dépendances externes
include(FetchContent)

# telecharge le module googletest depuis le dépôt GitHub
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# construit et installe le module googletest
FetchContent_MakeAvailable(googletest)

# definit les sources des tests unitaires
add_executable(${PROJECT_NAME}
    main.cpp
    exception/TestException.cpp
    facade/TestFacade.cpp
    factory/TestFacade.cpp
    module/trace/backtrace/TestTrace.cpp
    process/TestProcess.cpp
)

# définit le répertoire d'inclusion pour le projet
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_HOME_DIRECTORY}/include
)

# definit les libraries à lier avec l'exécutable des tests unitaires
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        readycpp_exception
        readycpp_facade
        readycpp_factory
        readycpp_module
        readycpp_process
        gmock
        gmock_main
        gtest
        gtest_main
)

# ajoute les tests unitaires au module CTest pour qu'ils soient exécutés avec ctest
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

# definit le répertoire d'installation du binaire
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# définit la macro UNIT_TEST pour activer les tests unitaires dans le code source
target_compile_definitions(${PROJECT_NAME} PRIVATE UNIT_TEST)

# active le mode debug si l'option WITH_DEBUG est activée
if(WITH_DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g -rdynamic -fno-omit-frame-pointer)
endif()
