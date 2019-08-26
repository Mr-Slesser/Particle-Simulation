#!/bin/bash
echo "[1] Build & Run"
echo "[2] Build"
echo "[3] Generate"
echo "[4] Clean"
echo "[5] Commit"

read -p "Enter selection :> " sel

case $sel in
    1)
        ./Scripts/Build-Run.sh
        ;;
    2)
        ./Scripts/Build.sh
        ;;
    3)
        ./Scripts/Generate.sh
        ;;
    4)
        ./Scripts/Clean.sh
        ;;
    5)
        ./Scripts/Commit.sh
        ;;
esac