#!/bin/bash
branch=$(git symbolic-ref --short HEAD)
read -p "Enter commit message: " msg
git add .
git commit -m "$msg"
git push origin $branch --recurse-submodules=on-demand