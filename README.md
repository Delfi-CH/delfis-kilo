# dk - delfi's kilo

personal clone of kilo [https://github.com/antirez/kilo?tab=readme-ov-file](https://github.com/antirez/kilo?tab=readme-ov-file)

please dont use this, use (neo)vi(m) / nano / vscode / something else

***Note: This only works on UNIX and UNIX-Like Systems! If you are on Windows, please consider installing a Linux Disto on Bare Metal or use WSL***

## Installation (if you really want to use this)

### ArchLinux

1. Install the `base-devel` and `git` package with `pacman -S base-devel git`
2. Download the `PKGBUILD` to a folder on your Computer (e.g with `curl -o PKGBUILD https://raw.githubusercontent.com/Delfi-CH/delfis-kilo/refs/heads/main/PKGBUILD`).
3. Run `makepkg -si` in the same folder as the PKGBUILD
4. Done!

### Anythig else 

1. Install `make`, `git` and a C Compiler (tested with `gcc` and `clang`)
2. Clone the Repository `git clone https://github.com/Delfi-CH/delfis-kilo.git`
3. Compile the software with `make`
4. Install with `make install`
5. Done!
