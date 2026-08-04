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
log_get_filename()
{
    echo "$root_dir/logs/cmd/bash/logs.log"
}

# cree le repertoire de log si il n'existe pas
log_create_directory()
{
    local log_filename=$(log_get_filename)
    mkdir -p "$(dirname "$log_filename")"
}

# trace le message de log avec le niveau et le message
log_trace_filename()
{
    local level="$1"
    local msg="$2"
    local ts="$3"
    local log_filename=$(log_get_filename)

    log_create_directory
    echo "$ts [$level] $msg" >> "$log_filename"
}

# ecrit un message de log avec le niveau et le message
log_write()
{
    local level="$1"
    local msg="$2"
    local ts=$(date '+%Y-%m-%d %H:%M:%S')

    case "$level" in
        INFO)
            echo -e "${CYAN}$ts [INFO]${RESET} $msg"
            ;;
        WARN)
            echo -e "${YELLOW}$ts [WARN]${RESET} $msg"
            ;;
        ERROR)
            echo -e "${RED}$ts [ERROR]${RESET} $msg"
            ;;
        DEBUG)
            [[ $DEBUG ]] && echo -e "${GREEN}$ts [DEBUG]${RESET} $msg"
            ;;
        *)
            echo -e "$ts [UNKNOWN] $msg"
            ;;
    esac

    log_trace_filename "$level" "$msg" "$ts"
}

# ecrit un message de log de niveau INFO
log_info()
{
    log_write "INFO" "$1"
}

# ecrit un message de log de niveau WARN
log_warn()
{
    log_write "WARN" "$1"
}

# ecrit un message de log de niveau ERROR
log_error()
{
    log_write "ERROR" "$1"
    trace_print
}

# ecrit un message de log de niveau DEBUG
log_debug()
{
    log_write "DEBUG" "$1"
}
