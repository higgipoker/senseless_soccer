
rmdir /S /Q Debug;
rmdir /S /Q Release;

mkdir Debug
mkdir Release
cd Debug
cmake ../ -DCMAKE_INSTALL_PREFIX=c:\sfml -DCMAKE_BUILD_TYPE=Debug;

cd ../Release;
cmake ../ -DCMAKE_INSTALL_PREFIX=c:\sfml -DCMAKE_BUILD_TYPE=Release;


