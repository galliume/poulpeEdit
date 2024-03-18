#!/usr/bin/env bash

set -o errexit -o pipefail -o noclobber -o nounset

configPoulpeEdit=0
buildPoulpeEdit=0

showusage() {
    echo "~~~~~~~~~~~~~~ PoulpeEdit ~~~~~~~~~~~~~~~~~~~"
    echo "-c|--config           CMake config		   "
    echo "-b|--build            Build PoulpeEdit	   "
    echo "-h|--help             Show this help		   "
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
}

while [[ $# -gt 0 ]]; do
    argument="$1"
    case "$argument" in
      -c|--config)
        configPoulpeEdit=1
        shift
        ;;
      -b|--build)
        buildPoulpeEdit=1
        shift
        ;;
      -h|--help)
        showusage
        exit 0
        ;;
      *|-*|--*)
        echo "Unknown option $argument"

        showusage
        exit 1
        ;;
    esac
done

if [[ configPoulpeEdit -eq 1 ]]
then
    cmake -B ./build \
          -DCMAKE_C_COMPILER=clang \
          -DCMAKE_BUILD_TYPE=Debug \
          -DCMAKE_GENERATOR_TOOLSET="ClangCL" \
          -DENABLE_CJSON_TEST=OFF \
		  -DENABLE_CUSTOM_COMPILER_FLAGS=OFF \
	      -DENABLE_CJSON_VERSION_SO=OFF
		  
fi

if [[ buildPoulpeEdit -eq 1 ]]
then
    cmake --build ./build/ -j8
fi
