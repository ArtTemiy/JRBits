mkdir "deps"
# shellcheck disable=SC2164
git clone https://github.com/SFML/SFML deps/SFML
git clone https://github.com/google/glog deps/glog
git clone https://github.com/google/googletest deps/gtest
# shellcheck disable=SC2103