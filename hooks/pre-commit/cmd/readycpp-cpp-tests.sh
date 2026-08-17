#!/bin/bash
set -e

# definit le repertoire racine du projet
: "${root_dir=$(dirname $(dirname $(dirname $(dirname $0))))}"

# definit les dependances du projet
source "$root_dir/cmd/bash/module/log.sh"

cmd_main()
{
    local BIN="$root_dir/build/tests/readycpp_tests"

    log_info "🔍 L'execution des tests c++ est en cours..."

    if ! [ -f "$BIN" ]; then
        log_error "❌ Le binaire readycpp_tests est introuvable."
        log_warn "Le projet doit etre compile avant de lancer pre-commit."
        exit 1
    fi

    if ! [ -x "$BIN" ]; then
        log_warn "⚠️ Le binaire n'est pas exécutable, correction..."
        chmod +x "$BIN"
    fi

    if ! "$BIN"; then
        log_error "❌ Les tests c++ du projet ont echoue."
        exit 1
    fi

    log_info "✔️  L'execution des tests c++ est terminee avec succes..."
    exit 0
}

cmd_main
