#!/bin/bash

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname "$0"))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/args.sh"
source "$root_dir/cmd/bash/module/log.sh"

# definit les facades du projet
source "$root_dir/cmd/bash/facade/config.sh"
source "$root_dir/cmd/bash/facade/cmake.sh"
source "$root_dir/cmd/bash/facade/test.sh"

# affiche l'aide
cmd_help()
{
    echo
    echo "Usage: cmd.sh <module> <method> [args]"
    echo
    echo "  - Description des arguments :"
    echo "      - <module>  : Le module à exécuter (obligatoire)."
    echo "      - <method>  : La méthode à appeler (obligatoire)."
    echo "      - [args]    : Les arguments cli (optionnels)."
    echo
    echo "  - Liste des modules disponibles :"
    echo "      - help      : Affiche l'aide."
    echo "      - config    : Execute le module config."
    echo "      - cmake     : Execute le module cmake."
    echo "      - tests     : Execute le module des tests."
    echo
}

# execute le programme principal
cmd_run()
{
    local module

    module=$(args_get_module "$@")

    if [ "$module" = "" ]; then
        cmd_help
    elif [ "$module" = "config" ]; then
        config_facade_run "$@"
    elif [ "$module" = "cmake" ]; then
        cmake_facade_run "$@"
    elif [ "$module" = "tests" ]; then
        test_facade_run "$@"
    elif [ "$module" = "help" ]; then
        cmd_help
    else
        log_error "Le module est inconnu.|module=$module"
        cmd_help
    fi
}

# execute le programme principal
cmd_run "$@"
