#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

PS1='\[\e[32;1m\]\u@\h \W\[\e[30;0m\]\$ \[\e[0m\]'

PATH="$PATH:~/.local/bin/"

export EDITOR=vim

export PYTHON_HISTORY="/dev/null"
export SQLITE_HISTORY="/dev/null"

export NNN_BMS="r:/;e:/mnt/SteamExt4;h:$HOME;s:/home/.snapshots"

alias ls='ls --color=auto'
alias ll='ls -l'
alias la='ls -a'
alias grep='grep --color=auto'
