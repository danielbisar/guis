# Building skia and run guis in docker

Building skia on is suprisingly complex. It should be easier to use the scripts under `../docker/dev-image`.
You need a working docker installation (not tested on Windows without WSL2).

```
cd docker/dev-image

# build the docker image, might take some time, since it clones and builds harfbuzz and skia
./build.sh

# note: this will create a new container, use docker exec ... to use an existing container
# it will also need xauth installed to query the session cookie, otherwise no gui application can run from inside
# the container

# starts the container, clones guis and builds it
./run.sh
```

# OBSOLETE STEP BY STEP INSTRUCTIONS

sudo apt install libfreetype6-dev libglib2.0-dev libcairo2-dev meson pkg-config gtk-doc-tools generate-ninja

# we need a root folder to contain everything
mkdir skia
cd skia

# you cannot use libharfbuzz-dev since it doesn't contain hb-subset.h
git clone git@github.com:harfbuzz/harfbuzz.git
cd harfbuzz

meson build
meson compile -C build
cd build
# note somehow change installation path to /usr/...
# otherwise you must create ln -s /usr/local/include/harfbuzz /usr/include/harfbuzz
# and same for the libs
sudo ninja install

# as described here https://skia.org/docs/user/download/
git clone 'https://chromium.googlesource.com/chromium/tools/depot_tools.git'
export PATH="${PWD}/depot_tools:${PATH}"

git clone https://skia.googlesource.com/skia.git
cd skia
git checkout chrome/m101

python3 tools/git-sync-deps
source "./third_party/externals/emsdk/emsdk_env.sh
echo 'script_executable = "python3"' >> ./.gn

gn gen out/static --args='is_debug=false is_official_build=true cc="clang-14" cxx="clang++-14"'
ninja -C out/Static/

## Offizial documentation

https://skia.org/docs/user/build/

VERY HELPFUL: https://gist.github.com/Ard2148810/37a12c8642da824882098092a55bccea?msclkid=8d61dccca86d11ec92e1822fda5348f7

https://harfbuzz.github.io/building.html?msclkid=4f478291a87211ec905300cd1dadcea0
