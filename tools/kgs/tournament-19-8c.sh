#!/bin/bash
# Script for playing Fuego in a tournament on 19x19 KGS on a machine with
# 8 cores / 8 GB

FUEGO="../../build/opt/fuegomain/fuego"
NAME=Fuego19

usage() {
  cat >&2 <<EOF
Usage: $0 [options]
Options:
  -h Print help and exit
EOF
}

MAXGAMES_OPTION=""
while getopts "h" O; do
case "$O" in
  h)   usage; exit 0;;
  [?]) usage; exit 1;;
esac
done

shift $(($OPTIND - 1))
if [ $# -gt 0 ]; then
  usage
  exit 1
fi


echo "Enter KGS password for $NAME:"
read PASSWORD

GAMES_DIR="games/tournament/$NAME"
mkdir -p "$GAMES_DIR"

cat <<EOF >config-tournament-19-8c.gtp
# This file is auto-generated by tournament-19-8c.sh. Do not edit.

go_param debug_to_comment 1
go_param auto_save $GAMES_DIR/$NAME-

# Use 7.3 GB for both trees (search and the init tree used for reuse_subtree)
uct_max_memory 7300000000
uct_param_player reuse_subtree 1
uct_param_player ponder 1

# Set KGS rules (Chinese, positional superko)
go_rules kgs

sg_param time_mode real
uct_param_search number_threads 8
uct_param_search lock_free 1
EOF

cat >tmp.cfg <<EOF
name=$NAME
password=$PASSWORD
room=Computer Go
mode=tournament
verbose=t
engine=$FUEGO --size 19 --config config-tournament-19-8c.gtp
reconnect=t
EOF
java -jar kgsGtp.jar tmp.cfg && rm -f tmp.cfg

#-----------------------------------------------------------------------------
