#!/bin/bash
#
clear && sh -c 'ls test/scripts/*.sh | while read -r file;do echo "exec:$file";sh -c "$file";echo "";done;'
