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
    local tests_failed=0

    while IFS= read -r -d '' test_script_file; do
        bash "$test_script_file"
        local return_code=$?

        if [[ $return_code -ne 0 ]]; then
            tests_failed=1
        fi
    done < <(find "$tests_dir" -type f -name "*.sh" -print0)

    return $tests_failed
}
