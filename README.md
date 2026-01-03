# SamsSearch

## From a clean install of Pop OS 22.04:

```
sudo apt-get install build-essential git make \
pkg-config cmake ninja-build gnome-desktop-testing libasound2-dev libpulse-dev \
libaudio-dev libfribidi-dev libjack-dev libsndio-dev libx11-dev libxext-dev \
libxrandr-dev libxcursor-dev libxfixes-dev libxi-dev libxss-dev libxtst-dev \
libxkbcommon-dev libdrm-dev libgbm-dev libgl1-mesa-dev libgles2-mesa-dev \
libegl1-mesa-dev libdbus-1-dev libibus-1.0-dev libudev-dev libthai-dev
```

### For each library (SDL/image/ttf/mixer:

### SDL
```
git clone https://github.com/libsdl-org/SDL.git
cd SDL
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --parallel
sudo cmake --install . --config Release
```

### Enable PNG for SDL_image
```
sudo apt install libpng-dev
```

### SDL_image
```
git clone https://github.com/libsdl-org/SDL_image
cd SDL_image
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --parallel
sudo cmake --install . --config Release
```

### Freetype (required for SDL_ttf):

Go on the official download page and click on the sourceforge link.
https://freetype.org/download.html

Download the tar.xz file.

Extract with tar -xf freetype-<version>.tar.xz, replacing <version> by the version you have, then move inside the extracted folder.

You can find documentation for the installation depending your system, in the doc/ folder.

Then build the package :
```
sh autogen.sh
./configure # this will install in /usr/local. See --help for moving target
make
sudo make install
```

### SDL_ttf:
```
git clone https://github.com/libsdl-org/SDL_ttf.git
cd SDL_ttf
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --parallel
sudo cmake --install . --config Release
```

### SDL_mixer:
```
git clone https://github.com/libsdl-org/SDL_mixer.git
cd SDL_mixer
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build . --config Release --parallel
sudo cmake --install . --config Release
```

### Enable these to all be found:
```
sudo ldconfig
```

### Pull assets if the folder is empty:
```
rmdir assets
git submodule update --init --recursive
git submodule update --recursive --remote
```

## Assets used (so far)
* [80+ RPG Characters Sprites](https://finalbossblues.itch.io/tf-rpg-charactersprites-1) - [finalbossblues](https://finalbossblues.itch.io/)
* [Future Fantasy Tiles and Characters Pack](https://finalbossblues.itch.io/future-fantasy) - [finalbossblues](https://finalbossblues.itch.io/)
* [Fantasy RPG Tileset Pack](https://finalbossblues.itch.io/fantasy-rpg-tileset-pack) - [finalbossblues](https://finalbossblues.itch.io/)
* [Time Fantasy Faces](https://finalbossblues.itch.io/tf-faces) - [finalbossblues](https://finalbossblues.itch.io/)
* [TinyXML-2](https://github.com/leethomason/tinyxml2) - Nifty XML library! 
* [Tiled](https://www.mapeditor.org/) - Best map editor ever
* [cpp-base64](https://github.com/ReneNyffenegger/cpp-base64) - Base 64 decoding
* [Press Start 2P](https://www.fontspace.com/press-start-2p-font-f11591) - Pixel font
* [ChipTunes Green Edition](https://filippogameaudio.itch.io/8-bit-nes-style-chiptunes) - Music by [Filippo Vicarelli](https://filippogameaudio.itch.io/)
* [Leohpaz Complete SFX Bundle](https://itch.io/s/79857/leohpaz-complete-sfx-bundle)
  * Minifantasy - True Heroes SFX pack
  * Domestic Animals SFX Pack
  * Minifantasy - Farm SFX

## How to double tile set size without blurring:
```
find . -name "*.png" | xargs mogrify -sample 200%
```

## CLion and the fun that is CMake
In root directory:
```
cmake -S . -B .
make
```

- Open in CLion as "Makefile project"
- Under 'Edit Configuration' add executable as required
