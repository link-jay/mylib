#
# ~/.bash_profile
#

[[ -f ~/.bashrc ]] && . ~/.bashrc

if [[ -z "$TMUX" ]] && shopt -q login_shell; then
	tmux new-session -A -s main
fi
