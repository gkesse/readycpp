#!/bin/bash

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname $(dirname $(dirname $(dirname $(dirname "$0")))))))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/config/ini/config.sh"

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

# teste la lecture des valeurs par defaut
test_config_ini_lecture_valeur_par_defaut()
{
    config_ini_test_init_file
    assertEquals "core" "$(config_ini_get_param_file "general" "module")"
    assertEquals "core" "$(config_ini_get_param_file "general" "module" "inconnu")"
    assertEquals "" "$(config_ini_get_param_file "general" "no_key")"
    assertEquals "inconnu" "$(config_ini_get_param_file "general" "no_key" "inconnu")"
    assertEquals "" "$(config_ini_get_param_file "no_section" "no_key")"
    assertEquals "inconnu" "$(config_ini_get_param_file "no_section" "no_key" "inconnu")"
    config_ini_test_remove_file
}

# teste la lecture des donnees du fichier ini
test_config_ini_lecture_donnees()
{
    config_ini_test_init_file
    assertEquals "core" "$(config_ini_get_param_file general module)"
    assertEquals "on" "$(config_ini_get_param_file general debug)"
    assertEquals "localhost" "$(config_ini_get_param_file network host)"
    assertEquals "8080" "$(config_ini_get_param_file network port)"
    assertEquals "8080" "$(config_ini_get_param_file network port)"
    config_ini_test_remove_file
}

# propage le code d'erreur des tests unitaires
oneTimeTearDown()
{
    exit $__shunit_testsFailed
}

# demarre les tests unitaires
. /usr/bin/shunit2
