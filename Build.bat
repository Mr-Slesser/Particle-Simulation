@echo off

echo [1] Generate
echo [2] Clean
echo [3] Commit

set /p sel="Enter selection :> "

IF "%sel%"=="1" call .\Scripts\Generate.bat
IF "%sel%"=="2" call .\Scripts\Clean.bat
IF "%sel%"=="3" call .\Scripts\Commit.bat