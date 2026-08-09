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

    if [ -z $value ] ; then
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

    if [ -z $value ] ; then
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
