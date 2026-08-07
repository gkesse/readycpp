#!/bin/bash

# affiche la trace de la pile d'appels
trace_print() {
    echo "Stack trace:"
    for ((i=0; i<${#FUNCNAME[@]}; i++)); do
        echo "  $i: ${FUNCNAME[$i]} (${BASH_SOURCE[$i]}:${BASH_LINENO[$i]})"
    done
}
