Offizial documentation

https://skia.org/docs/user/build/

VERY HELPFUL: https://gist.github.com/Ard2148810/37a12c8642da824882098092a55bccea?msclkid=8d61dccca86d11ec92e1822fda5348f7

Tried on Ubuntu 21.04

# clone and compile harfbuzz
git clone git@github.com:harfbuzz/harfbuzz.git
cd harfbuzz

https://harfbuzz.github.io/building.html?msclkid=4f478291a87211ec905300cd1dadcea0
sudo apt install gcc g++ libfreetype6-dev libglib2.0-dev libcairo2-dev meson pkg-config gtk-doc-tools
meson build
meson compile -C build
# ????? sudo make install
cd ..



# we need a root folder to contain everything
mkdir skia

# as described here https://skia.org/docs/user/download/
git clone 'https://chromium.googlesource.com/chromium/tools/depot_tools.git'
git clone https://skia.googlesource.com/skia.git

cd skia

git checkout chrome/m98

# patch files: manully
# gn/toolchain/BUILD.gn <-- change 
# -        command = "$shell python \"$rm_py\" \"{{output}}\" && $ar rcs {{output}} @$rspfile"
# +        command = "$shell python2 \"$rm_py\" \"{{output}}\" && $ar rcs {{output}} @$rspfile"

#diff --git a/third_party/harfbuzz/BUILD.gn b/third_party/harfbuzz/BUILD.gn
#index 68e4689c1a..f77b85b751 100644
#--- a/third_party/harfbuzz/BUILD.gn
#+++ b/third_party/harfbuzz/BUILD.gn
#@@ -12,7 +12,7 @@ declare_args() {
#
# if (skia_use_system_harfbuzz) {
#   system("harfbuzz") {
#-    include_dirs = [ "/usr/include/harfbuzz" ]
#+    include_dirs = [ "/usr/local/include/harfbuzz" ]
#     libs = [ "harfbuzz" ]
#     if (skia_pdf_subset_harfbuzz) {
#       libs += [ "harfbuzz-subset" ]
#

#diff --git a/.gn b/.gn
#index 29e83234de..2b9e9b398a 100644
#--- a/.gn
#+++ b/.gn
#@@ -3,3 +3,6 @@ buildconfig = "//gn/BUILDCONFIG.gn"
# default_args = {
#   angle_standalone = false
# }
#+
#+script_executable = "python2"

gn gen out/Static --args='is_official_build=true cc="clang-14" cxx="clang++-14"'
ninja -C out/Static/


