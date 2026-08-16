#!/bin/bash
set -e

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname $(dirname $0))))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/log.sh"

cmd_main()
{
    log_info "🔍 L'execution des tests bash est en cours..."
    set +e
    bash cmd/cmd.sh tests run_bash
    local return_code=$?
    set -e

    if [[ $return_code -ne 0 ]]; then
        log_error "❌ L'execution des tests bash a echoue..."
        exit 1
    fi

    log_info "✔️  L'execution des tests c++ est termine avec succes..."
    exit 0
}

cmd_main
