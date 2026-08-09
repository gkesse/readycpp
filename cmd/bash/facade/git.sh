#!/bin/bash

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname "$0")))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/args.sh"
source "$root_dir/cmd/bash/module/log.sh"
source "$root_dir/cmd/bash/module/git.sh"

# affiche l'aide
git_facade_help()
{
    echo
    echo "Usage: git.sh <method> [args]"
    echo
    echo "  - Description des arguments :"
    echo "      - <method>  : La méthode à appeler (obligatoire)."
    echo "      - [args]    : Les arguments cli (optionnels)."
    echo
    echo "  - Liste des méthodes disponibles :"
    echo "      - help              : Affiche l'aide."
    echo "      - config_user_info  : Configure les informations de l'utilisateur."
    echo "      - show_user_info    : Affiche les informations de l'utilisateur."
    echo "      - config_sign_ssh   : Configure les informations de signature des commits en ssh."
    echo
}

# configure les informations de l'utilisateur
git_facade_config_user_info()
{
    echo
    log_info "La configuration des informations de l'utilisateur est en cours..."
    echo
    git_config_user_info
    echo
    log_info "La configuration des informations de l'utilisateur est terminee..."
    echo
}

# affiche les informations de l'utilisateur
git_facade_show_user_info()
{
    echo
    log_info "L'affichage des informations de l'utilisateur est en cours..."
    echo
    git_show_user_info
    echo
    log_info "L'affichage des informations de l'utilisateur est termine..."
    echo
}

# configure les informations de signature des commits en ssh
git_facade_config_sign_ssh()
{
    echo
    log_info "La configuration de la signature des commits en ssh est en cours..."
    echo
    git_config_sign_ssh
    echo
    log_info "La configuration de la signature des commits en ssh est termine..."
    echo
}

# execute le programme principal
git_facade_run()
{
    method=$(args_get_method "$@")

    if [ "$method" = "" ]; then
        git_facade_help
    elif [ "$method" = "config_user_info" ]; then
        git_facade_config_user_info "$@"
    elif [ "$method" = "show_user_info" ]; then
        git_facade_show_user_info "$@"
    elif [ "$method" = "config_sign_ssh" ]; then
        git_facade_config_sign_ssh "$@"
    elif [ "$method" = "help" ]; then
        git_facade_help
    else
        log_error "La méthode est inconnue.|method=$method"
        git_facade_help
    fi
}
