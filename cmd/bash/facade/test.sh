#!/bin/bash

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname $(dirname "$0"))))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/args.sh"
source "$root_dir/cmd/bash/module/log.sh"

# affiche l'aide
test_facade_help()
{
    echo
    echo "Usage: test_facade.sh <method> [args]"
    echo
    echo "  - Description des arguments :"
    echo "      - <method>  : La méthode à appeler (obligatoire)."
    echo "      - [args]    : Les arguments cli (optionnels)."
    echo
    echo "  - Liste des méthodes disponibles :"
    echo "      - help      : Affiche l'aide."
    echo "      - run       : Demarre les tests."
    echo
}

# demarre les tests
test_facade_run_tests()
{
    for test in $root_dir/cmd/bash/tests/*.sh; do
        log_info "L'execution du test est en cours...|start=$(basename $test)"
        echo
        bash "$test"
        echo
        log_info "L'execution du test est termine...|end=$(basename $test)"
    done
}

# execute le programme principal
test_facade_run()
{
    method=$(args_get_method "$@")

    if [ "$method" = "" ]; then
        test_facade_help
    elif [ "$method" = "run" ]; then
        test_facade_run_tests "$@"
    elif [ "$method" = "help" ]; then
        test_facade_help
    else
        log_error "La méthode est inconnue.|method=$method"
        test_facade_help
    fi
}
