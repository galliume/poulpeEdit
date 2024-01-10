#!/usr/bin/env bash

set -o errexit -o pipefail -o noclobber -o nounset

buildGTK=0
configPoulpeEdit=0
buildPoulpeEdit=0

showusage() {
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "~~~~~~ PoulpeEdit ~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    echo "--config           CMake config"
    echo "--buildPoulpeEdit  Build PoulpeEdit"
    echo "--buildGTK         Build GTK (with meson)"
    echo "--help             Show this help"
    echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
}

while [[ $# -gt 0 ]]; do
    argument="$1"
    echo $argument
    case "$argument" in
      --buildGTK)
        buildGTK=1
        shift
        ;;
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

if [[ buildGTK -eq 1 ]]
then
    pushd ./vendor/gtk/
    meson setup --prefix=E:/vendor/gtk/release _build -Dmedia-gstreamer=disabled -Dwin32-backend=true -Dvulkan=disabled
    meson compile -C _build
    meson install -C _build
    popd
fi

if [[ configPoulpeEdit -eq 1 ]]
then
    rm ./build -rf
    cmake -B ./build/Debug
fi

if [[ buildPoulpeEdit -eq 1 ]]
then
    cmake --build ./build/Debug -j8
fi
