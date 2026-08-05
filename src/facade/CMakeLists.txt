# definit le nom du projet
project(readycpp_facade)

# definit les sources du projet
add_library(${PROJECT_NAME}
    Bdd.cpp
    Facade.cpp
)

# définit le répertoire d'inclusion pour le projet
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_HOME_DIRECTORY}/include
)

# definit les libraries à lier avec l'exécutable des tests unitaires
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        readycpp_process
)

# active le mode debug si l'option WITH_DEBUG est activée
if(WITH_DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g)
endif()
