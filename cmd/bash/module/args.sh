#!/bin/bash

# recupere le module a executer
args_get_module()
{
    echo "$1"
}

# recupere la methode a executer
args_get_method()
{
    echo "$2"
}

# recupere les parametres a executer
args_get_params()
{
    shift 2
    echo "$@"
}
