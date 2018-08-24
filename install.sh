git clone https://github.com/lanzhige/bin-zip.git
cd ./bin-zip
mkdir -p ./build
cd ./build
cmake ..
cmake --build . --config Release
cd ..
cd ..
cp ./bin-zip/build/src/Release/bin-zip.exe ./
cp ./bin-zip/bin/zlib.dll ./
cp ./bin-zip/README.md ./
rm -rf ./bin-zip
