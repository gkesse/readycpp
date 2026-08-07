#!/bin/bash

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname "$0")))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/args.sh"
source "$root_dir/cmd/bash/module/log.sh"

# affiche l'aide
cmake_facade_help()
{
    echo
    echo "Usage: cmake.sh <method> [args]"
    echo
    echo "  - Description des arguments :"
    echo "      - <method>  : La méthode à appeler (obligatoire)."
    echo "      - [args]    : Les arguments cli (optionnels)."
    echo
    echo "  - Liste des méthodes disponibles :"
    echo "      - help      : Affiche l'aide."
    echo "      - build     : Construit le projet."
    echo
}

# construit le projet
cmake_facade_build()
{
    log_info "La construction du projet est en cours..."
    echo
    cmake --build $root_dir/build --target all
    echo
    log_info "La construction du projet est terminee..."
}

# execute le programme principal
cmake_facade_run()
{
    method=$(args_get_method "$@")

    if [ "$method" = "" ]; then
        cmake_facade_help
    elif [ "$method" = "build" ]; then
        cmake_facade_build "$@"
    elif [ "$method" = "help" ]; then
        cmake_facade_help
    else
        log_error "La méthode est inconnue.|method=$method"
        cmake_facade_help
    fi
}
