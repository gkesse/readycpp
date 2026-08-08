#!/bin/bash

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname $(dirname "$0"))))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/trace.sh"

# definit les couleurs
RED="\e[31m"
YELLOW="\e[33m"
GREEN="\e[32m"
CYAN="\e[36m"
RESET="\e[0m"

# recupere le nom du fichier de log
config_ini_get_filename()
{
    echo "$root_dir/config/cmd/bash/config.ini"
}

# cree le repertoire de log si il n'existe pas
config_ini_create_directory()
{
    local config_ini_filename=$(config_ini_get_filename)
    mkdir -p "$(dirname "$config_ini_filename")"
}

# lit une valeur d'un parametre a partir d'une section
config_ini_get_param() {
    local file=$(config_ini_get_filename)
    local section="$1"
    local key="$2"

    awk -F= -v s="$section" -v k="$key" '
        $0=="["s"]"{found=1; next}
        found && $1==k {print $2; exit}
    ' "$file"
}
