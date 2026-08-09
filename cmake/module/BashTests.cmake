# definit le nom de la cible
set(DEF_TARGET_NAME readycpp_bash_tests)

# definit la commande d'execution des tests unitaires
set(DEF_TEST_COMMAND_LINE
    "./cmd/cmd.sh tests run_bash"
)

# ajoute les tests unitaires au module CTest
add_test(
    NAME ${DEF_TARGET_NAME}
    COMMAND /bin/bash -c "${DEF_TEST_COMMAND_LINE}"
)

# definit les dependances des tests unitaires
set_tests_properties(${DEF_TARGET_NAME} PROPERTIES
    TIMEOUT 60
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# definit la commande associee a la cible
add_custom_target(${DEF_TARGET_NAME}
    COMMAND ${CMAKE_CTEST_COMMAND} -R bash_tests --output-on-failure -V
)
