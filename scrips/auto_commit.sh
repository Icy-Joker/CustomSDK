#!/bin/bash
#
git diff --diff-filter=M --name-only | while read -r file; do
  echo $file;
  git add $file;
  git commit -m "auto commit :$file"
done
