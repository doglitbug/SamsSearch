# SamsSearch

```
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev
sudo apt-get install libsdl2-ttf-dev
sudo apt-get install libsdl2-mixer-dev
```

## Assets used (so far)
* [80+ RPG Characters Sprites](https://finalbossblues.itch.io/tf-rpg-charactersprites-1) - [finalbossblues](https://finalbossblues.itch.io/)
* [Future Fantasy](https://finalbossblues.itch.io/future-fantasy) - [finalbossblues](https://finalbossblues.itch.io/)
* [Fantasy RPG Tileset Pack](https://finalbossblues.itch.io/fantasy-rpg-tileset-pack) - [finalbossblues](https://finalbossblues.itch.io/)
* [TinyXML-2](https://github.com/leethomason/tinyxml2) - Nifty XML library! 
* [Tiled](https://www.mapeditor.org/) - Best map editor ever
* [cpp-base64](https://github.com/ReneNyffenegger/cpp-base64) - Base 64 decoding
* [Press Start 2P](https://www.fontspace.com/press-start-2p-font-f11591) - Pixel font
* [ChipTunes Green Edition](https://filippogameaudio.itch.io/8-bit-nes-style-chiptunes) - Music by [Filippo Vicarelli](https://filippogameaudio.itch.io/)
* [ChipTunes Retro Game Effects Volume 1](https://filippogameaudio.itch.io/game-sound-effects-01) - ChipTunes Retro Game Effects Volume 1 by [Filippo Vicarelli](https://filippogameaudio.itch.io/)
* [ChipTunes Retro Game Effects Volume 2](https://filippogameaudio.itch.io/game-sound-effects-02) - ChipTunes Retro Game Effects Volume 2 by [Filippo Vicarelli](https://filippogameaudio.itch.io/)

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
