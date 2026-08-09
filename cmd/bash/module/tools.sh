#!/bin/bash

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname $(dirname "$0"))))}"

# configure les informations de l'utilisateur
tools_check_config()
{
    local config="$1"
    local is_valid=""

    if ! [ -z "$config" ] && [ "$config" != "inconnu" ] ; then
        is_valid="true"
    fi

    echo "$is_valid"
}
