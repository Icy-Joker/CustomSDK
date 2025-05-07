#!/bin/bash
#
clear && find test/scripts -name "*.sh" -print0 | sort -z | xargs -0 -I{} sh -c 'echo "exec:{}"; sh "{}"; echo'
