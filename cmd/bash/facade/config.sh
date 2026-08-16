#!/bin/bash

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname "$0")))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/args.sh"
source "$root_dir/cmd/bash/module/log.sh"
source "$root_dir/cmd/bash/module/config/ini/config.sh"

# affiche l'aide
config_facade_help()
{
    echo
    echo "Usage: config.sh <method> [args]"
    echo
    echo "  - Description des arguments :"
    echo "      - <method>  : La méthode à appeler (obligatoire)."
    echo "      - [args]    : Les arguments cli (optionnels)."
    echo
    echo "  - Liste des méthodes disponibles :"
    echo "      - help          : Affiche l'aide."
    echo "      - ini           : Installe les configurations ini du projet."
    echo "      - generate_ini  : Genere le fichier de configuration ini du projet."
    echo
}

# initialise les configuration ini du projet
config_facade_init_ini()
{
    echo
    log_info "L'installation des configurations ini du projet est en cours..."
    echo
    config_ini_init
    echo
    log_info "L'installation des configurations ini du projet est terminee..."
    echo
}

# genere le fichier de configuration ini du projet
config_facade_generate_ini()
{
    echo
    log_info "La generation des fichiers de configuration du projet est en cours..."
    echo
    config_ini_generate
    echo
    log_info "La generation des fichiers de configuration du projet est terminee..."
    echo
}

# execute le programme principal
config_facade_run()
{
    method=$(args_get_method "$@")

    if [ "$method" = "" ]; then
        config_facade_help
    elif [ "$method" = "ini" ]; then
        config_facade_init_ini "$@"
    elif [ "$method" = "generate_ini" ]; then
        config_facade_generate_ini "$@"
    elif [ "$method" = "help" ]; then
        config_facade_help
    else
        log_error "La méthode est inconnue.|method=$method"
        config_facade_help
    fi
}
