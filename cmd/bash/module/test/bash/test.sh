#!/bin/bash

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname $(dirname $(dirname $(dirname "$0"))))))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/log.sh"

# recupere le repertoire des tests
test_bash_get_directory()
{
    echo "$root_dir/cmd/bash/tests"
}

# execute tous les tests unitaires
test_bash_run_tests()
{
    local tests_dir=$(test_bash_get_directory)

    find $tests_dir -type f -name "*.sh" -print0 | while IFS= read -r -d '' test_script_file; do
        echo
        log_info "L'execution du test est en cours...|start=$test_script_file"
        echo
        bash "$test_script_file"
        echo
        log_info "L'execution du test est termine...|end=$test_script_file"
        echo
    done
}
