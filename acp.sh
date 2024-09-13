#!/usr/bin/env zsh

msg="NO_msg"

if [ -n "$1" ] ; then
  msg=$1
fi

git add .
git commit -m "${msg}"
git push