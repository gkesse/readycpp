# definit le nom de la cible
set(DEF_TARGET_NAME readycpp_ctests)

# definit les dependances de la cible
set(DEF_DEPENDS readycpp_tests)

# recupere tous les scripts bash
file(GLOB_RECURSE DEF_BASH_SCRIPTS
    ${CMAKE_SOURCE_DIR}/cmd/bash/tests/*.sh
)

# definit la commande associee a la cible
add_custom_target(${DEF_TARGET_NAME}
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -V
    DEPENDS ${DEF_DEPENDS} ${DEF_BASH_SCRIPTS}
)
