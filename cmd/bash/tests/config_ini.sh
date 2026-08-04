#!/bin/bash

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname $(dirname "$0"))))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/config_ini.sh"

# definit le chemin du fichier ini
config_ini_get_filename()
{
    local current_dir="$(dirname $0)"
    local filename="$current_dir/config.ini"
    echo $filename
}

# initialise le contenu du fichier ini
config_ini_test_init_file()
{
    local current_dir="$(dirname $0)"
    local filename="$current_dir/config.ini"

cat <<_EOF_ > $filename
[general]
module=core
debug=on

[network]
host=localhost
port=8080
_EOF_
}

# supprime le fichier ini
config_ini_test_remove_file()
{
    local current_dir="$(dirname $0)"
    local filename="$current_dir/config.ini"
    rm -f $filename
}

# teste la modification du nom du fichier ini
test_config_ini_filename()
{
    local current_dir="$(dirname $0)"
    local filename="$current_dir/config.ini"
    assertEquals "$filename" "$(config_ini_get_filename)"
}

# teste la lecture des donnees du fichier ini
test_config_ini_read_data()
{
    config_ini_test_init_file
    assertEquals "core" "$(config_ini_get_param general module)"
    assertEquals "on" "$(config_ini_get_param general debug)"
    assertEquals "localhost" "$(config_ini_get_param network host)"
    assertEquals "8080" "$(config_ini_get_param network port)"
    config_ini_test_remove_file
}

# demarre les tests unitaires
. /usr/bin/shunit2
