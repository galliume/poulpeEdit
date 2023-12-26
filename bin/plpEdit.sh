clang `pkg-config --cflags gtk4` \
    -o ./build/poulpeEdit \
    ./src/main.c \
    `pkg-config --libs gtk4`