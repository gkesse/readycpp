# definit le nom du projet
project(readycpp_app)

# definit les sources du projet
add_executable(${PROJECT_NAME}
    main.cpp
)

# définit le répertoire d'inclusion pour le projet
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_HOME_DIRECTORY}/include
)

# definit les libraries à lier avec le binaire
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        readycpp_module
        readycpp_process
)

# definit le répertoire d'installation du binaire
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# active le mode debug si l'option WITH_DEBUG est activée
if(WITH_DEBUG)
    target_compile_options(${PROJECT_NAME} PRIVATE -g -rdynamic -fno-omit-frame-pointer)
endif()
