#!/bin/bash

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname $(dirname "$0"))))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/log.sh"

# recupere le nom du fichier ini
config_ini_get_filename()
{
    echo "$root_dir/config/ini/config.ini"
}

# cree le repertoire du fichier ini
config_ini_create_directory()
{
    local filename=$(config_ini_get_filename)
    local directory=$(dirname "$filename")

    mkdir -p $directory

    log_info "La creation du repertoire du fichier ini est terminee..."
    log_info "|- directory=$directory"
}

# cree le fichier ini
config_ini_create_file()
{
    local filename=$(config_ini_get_filename)

    if [ ! -f "$filename" ]; then
        touch "$filename"
    fi

    log_info "La creation du fichier ini est terminee..."
    log_info "|- filename=$filename"
}

# lit la valeur d'un parametre a partir du fichier
config_ini_get_param_file() {
    local filename=$(config_ini_get_filename)
    local section="$1"
    local key="$2"
    local default="$3"

    local value=$(awk -F= -v s="$section" -v k="$key" '
        $0=="["s"]"{found=1; next}
        found && $1==k {print $2; exit}
    ' "$filename")

    if [ -z "$value" ] ; then
        value="$default"
    fi

    echo "$value"
}

# lit la valeur d'un parametre a partir du contenu
config_ini_get_param_content() {
    local file_content="$1"
    local section="$2"
    local key="$3"
    local default="$4"

    local value=$(awk -F= -v s="$section" -v k="$key" '
        $0=="["s"]"{found=1; next}
        found && $1==k {print $2; exit}
    ' <<< "$file_content")

    if [ -z "$value" ] ; then
        value="$default"
    fi

    echo "$value"
}

# genere les configurations du fichier ini
config_ini_generate_configs()
{
    local filename="$(config_ini_get_filename)"
    local file_content="$(cat $filename)"

    > $filename
    cat >> $filename <<_EOF_
[git]
username=$(config_ini_get_param_content "$file_content" "git" "username" "inconnu")
email=$(config_ini_get_param_content "$file_content" "git" "email" "inconnu")
editor=$(config_ini_get_param_content "$file_content" "git" "editor" "nano")
_EOF_

    log_info "La generation des configurations du fichier ini est terminee..."
    log_info "|- filename=$filename"
    # cat $filename
}

# genere le fichier ini des configurations
config_ini_generate()
{
    config_ini_create_directory
    config_ini_create_file
    config_ini_generate_configs
}

# initialise les configurations git du projet
config_ini_init_git()
{
    # configure les parametre de l'utilisateur git
    local username=$(config_ini_get_param_file "git" "username" "inconnu")
    local email=$(config_ini_get_param_file "git" "email" "inconnu")
    local editor=$(config_ini_get_param_file "git" "editor" "inconnu")

    # configure la validation des messages de commit
    local pre_commit_src="hooks/pre-commit/config/.pre-commit-config.yaml"
    local pre_commit_dst=".pre-commit-config.yaml"

    # configure la validation des messages de commit
    local commit_msg_src="hooks/commit-msg/cmd/commit-msg"
    local commit_msg_dst=".git/hooks/commit-msg"

    # configure la signature des commits
    local gpg_format="ssh"
    local signing_key="$HOME/.ssh/id_ed25519.pub"
    local gpg_sign="true"


    if [ -z "$username" ] || [ "$username" == "inconnu" ] ; then
        log_error "Le nom d'utilisateur git est inconnu."
        return
    fi
    if [ -z "$email" ] || [ "$email" == "inconnu" ] ; then
        log_error "L'adresse email de l'utilisateur git est inconnue."
        return
    fi
    if [ -z "$editor" ] || [ "$editor" == "inconnu" ] ; then
        log_error "L'editeur des messages de commit git est inconnu."
        return
    fi
    if ! [ -e "$signing_key" ] ; then
        log_error "Le chemin de la cle publique ssh pour git est inconnu."
        return
    fi

    log_info "La configuration de l'utilisateur git est initialisee."
    log_info "|- username=$username"
    log_info "|- email=$email"
    log_info "|- editor=$editor"
    echo

    git config --global user.name "$username"
    git config --global user.email "$email"
    git config --global core.editor "$editor"

    log_info "La validation des fichiers de pre-commit est installee."
    log_info "|- pre_commit_src=$pre_commit_src"
    log_info "|- pre_commit_dst=$pre_commit_dst"
    echo

    if [ -L "$pre_commit_dst" ] ; then
        unlink "$pre_commit_dst"
    fi
    ln -s "$pre_commit_src" "$pre_commit_dst"
    pre-commit run --all-files
    echo
    pre-commit install
    echo

    log_info "La validation du format des messages de commit est initialisee."
    log_info "|- commit_msg_src=$commit_msg_src"
    log_info "|- commit_msg_dst=$commit_msg_dst"
    echo

    if [ -L "$commit_msg_dst" ] ; then
        unlink "$commit_msg_dst"
    fi
    ln -s "$commit_msg_src" "$commit_msg_dst"

    log_info "La signature des commits git est initialisee."
    log_info "|- gpg_format=$gpg_format"
    log_info "|- signing_key=$signing_key"
    log_info "|- gpg_sign=$gpg_sign"
    echo

    git config --global gpg.format "$gpg_format"
    git config --global user.signingkey "$signing_key"
    git config --global commit.gpgsign "$gpg_sign"

    log_info "Les parametres git configures sont affiches."
    log_info "|- username=$(git config user.name)"
    log_info "|- email=$(git config user.email)"
    log_info "|- editor=$(git config core.editor)"
    log_info "|- gpg_format=$(git config gpg.format)"
    log_info "|- signing_key=$(git config user.signingkey)"
    log_info "|- gpg_sign=$(git config commit.gpgsign)"
    echo
}

# initialise les configurations clang-format du projet
config_ini_init_clang_format()
{
    # configure le formatage de code avec clang-format
    local clang_format_src="hooks/clang-format/llvm/.clang-format"
    local clang_format_dst=".clang-format"

    log_info "Le formatage de code avec clang-format est initialise."
    log_info "|- clang_format_src=$clang_format_src"
    log_info "|- clang_format_dst=$clang_format_dst"

    if [ -L "$clang_format_dst" ] ; then
        unlink "$clang_format_dst"
    fi
    ln -s "$clang_format_src" "$clang_format_dst"
}

# initialise les configurations ini du projet
config_ini_init()
{
    config_ini_init_git "$@"
    config_ini_init_clang_format "$@"
}
