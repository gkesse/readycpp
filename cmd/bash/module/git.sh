#!/bin/bash

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname $(dirname "$0"))))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/log.sh"
source "$root_dir/cmd/bash/module/tools.sh"
source "$root_dir/cmd/bash/module/config/ini/config.sh"

# affiche les informations de l'utilisateur
git_show_user_info()
{
    local config_username="$(config_ini_get_param_file "git" "username")"
    local config_email="$(config_ini_get_param_file "git" "email")"
    local config_editor="$(config_ini_get_param_file "git" "editor")"

    local git_username="$(git config --global "user.name")"
    local git_email="$(git config --global "user.email")"
    local git_editor="$(git config --global "core.editor")"

    log_info "La recuperation du nom de l'utilisateur est terminee..."
    log_info "|- config_username=$config_username"
    log_info "|- git_username=$git_username"

    log_info "La recuperation de l'email de l'utilisateur est terminee..."
    log_info "|- config_email=$config_email"
    log_info "|- git_email=$git_email"

    log_info "La recuperation de l'editeur des messages de commit est terminee..."
    log_info "|- config_editor=$config_editor"
    log_info "|- git_editor=$git_editor"
}

# configure les informations de l'utilisateur
git_config_user_info()
{
    local git_username="$(config_ini_get_param_file "git" "username")"
    local git_email="$(config_ini_get_param_file "git" "email")"
    local git_editor="$(config_ini_get_param_file "git" "editor")"

    log_info "La recuperation des informations de l'utilisateur est terminee..."

    if [ -z "$(tools_check_config "$git_username")" ] ; then
        log_error "Le nom de l'utilisateur n'est pas defini."
        return
    fi
    if [ -z "$(tools_check_config "$git_email")" ] ; then
        log_error "L'email de l'utilisateur n'est pas definie."
        return
    fi
    if [ -z "$(tools_check_config "$git_editor")" ] ; then
        log_error "L'editeur des messages de commit n'est pas defini."
        return
    fi

    git config --global user.name "$git_username"
    git config --global user.email "$git_email"
    git config --global core.editor "$git_editor"

    git_show_user_info
}

# configure les informations de signature des commits en ssh
git_config_sign_ssh()
{
    local gpg_format="ssh"
    local user_signing_key="$HOME/.ssh/id_ed25519.pub"
    local commit_gpg_sign="true"

    if ! [ -e "$user_signing_key" ] ; then
        log_error "La cle publique ssh est obligatoire."
        return
    elif
        log_info "La cle publique ssh a ete trouvee."
    fi

    git config --global gpg.format "$gpg_format"
    git config --global user.signingkey "$user_signing_key"
    git config --global commit.gpgsign "$commit_gpg_sign"
}
