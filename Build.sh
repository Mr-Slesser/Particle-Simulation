#!/bin/bash
echo "[1] Build & Run"
echo "[2] Build"
echo "[3] Clean"
echo "[4] Generate"
echo "[5] Generate (XCode)"
echo "[6] Commit"

read -p "Enter selection :> " sel

case $sel in
    1)
        ./Scripts/Build-Run.sh
        ;;
    2)
        ./Scripts/Build.sh
        ;;
    3)
        ./Scripts/Clean.sh
        ;;
    4)
        ./Scripts/Generate.sh
        ;;
    5)
        ./Scripts/GenerateXCode.sh
        ;;
    6)
        ./Scripts/Commit.sh
        ;;
esac