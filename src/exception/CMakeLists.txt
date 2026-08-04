# definit le nom du projet
project(readycpp_exception)

# definit les sources du projet
add_library(${PROJECT_NAME}
    Exception.cpp
    process/Module.cpp
)

# définit le répertoire d'inclusion pour le projet
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_HOME_DIRECTORY}/include
)

# active le mode debug si l'option WITH_DEBUG est activée
if(WITH_DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
endif()
