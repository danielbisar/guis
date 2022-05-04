#!/bin/bash
apt update
apt upgrade -y
apt install -y libfreetype6-dev libglib2.0-dev libcairo2-dev meson pkg-config gtk-doc-tools generate-ninja git libjpeg-dev libgl-dev libicu-dev libwebp-dev

cd
mkdir -p src/skia
cd src/skia
git clone https://github.com/harfbuzz/harfbuzz.git
cd harfbuzz
meson build
meson compile -C build
cd build
ninja install
ln -s /usr/local/include/harfbuzz /usr/include/

cd ../..

git clone 'https://chromium.googlesource.com/chromium/tools/depot_tools.git'
export PATH="${PWD}/depot_tools:${PATH}"

git clone https://skia.googlesource.com/skia.git
cd skia
git checkout chrome/m101

python3 tools/git-sync-deps
source "./third_party/externals/emsdk/emsdk_env.sh"
echo 'script_executable = "python3"' >>./.gn

#
#vim gn/toolchain/BUILD.gn
#-> replace occurences of python by python3

gn gen out/static --args='is_debug=false is_official_build=true'
ninja -C out/static/

cd ../..
cd guis
./build.sh
