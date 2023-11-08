# The-Baker-Crow
A game developed as part of an introductory course on game development at the Universidade de Brasilia (UnB).

# Configuration - (Debian-based Linux) 
## Install g++
    sudo apt install g++

## SDL Library
    sudo apt-get update
    sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev

## Clangd
    sudo apt-get update
    sudo apt-get install clangd-12

## Clangd Configuration

### In the THE-BAKER-CROW directory
    touch compile_commands.json

### Save your path to the include directory, which you can find using:
    pwd

### Edit the compile_commands.json
    nano compile_commands.json

### Insert the following content, changing the directory to yours:
    [
        {
        "directory": "/home/exemple/Documents/GitHub/The-Baker-Crow/include",
        "command": "g++ -std=c++17 -I. -I..",
        "file": "/GitHub/The-Baker-Crow/include/"
        }

    ]

### Save with:
    ctrl + o
    ctrl + x

## Finally, compile and run the program while in THE-BAKER-CROW directory:
    make
    ./TheBakerCrow