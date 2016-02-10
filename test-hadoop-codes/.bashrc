# .bashrc

# User specific aliases and functions

# Source global definitions
if [ -f /etc/bashrc ]; then
	. /etc/bashrc

  # A couple of default aliases.
  alias j='jobs -l'
  alias po=popd
  alias rm='rm -i' 
  alias cp='cp -i' 
  alias del='rm -i' 
  alias mv='mv -i' 
  alias pu=pushd
  alias ls='ls -F'

  if [ -f ~/.bash_aliases ]; then
    source ~/.bash_aliases
  fi

fi
