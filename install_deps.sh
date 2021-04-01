mkdir "build"
# shellcheck disable=SC2164
cd build
git clone https://github.com/SFML/SFML SFML
git clone https://github.com/google/glog glog
git clone https://github.com/google/googletest gtest
# shellcheck disable=SC2103
cd ..
