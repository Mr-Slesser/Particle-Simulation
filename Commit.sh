#!/bin/bash
read -p "Enter commit message: " msg
git add .
git commit -m "$msg"
git push origin master --recurse-submodules=on-demand