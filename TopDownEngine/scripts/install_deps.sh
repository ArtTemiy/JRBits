mkdir "deps"
# shellcheck disable=SC2164
git clone https://github.com/SFML/SFML.git deps/SFML
git clone https://github.com/google/glog.git deps/glog
git clone https://github.com/google/googletest.git deps/gtest
git clone git@github.com:jbeder/yaml-cpp.git deps/
# shellcheck disable=SC2103