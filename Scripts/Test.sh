./Scripts/Clean.sh
./vendor/bin/premake/mac/premake5 gmake
make verbose=1
./bin/Debug-macosx-x86_64/ParticleTest/ParticleTest