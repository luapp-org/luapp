# Lua++ programming language

This is the Lua++ C lang build, currently in development but is soon to be completed. This codebase is not specifically tweaked to a certain compiler, so any C/C++ compiler should be able to build this project easily. Personally, I recommend building it with `gcc` although `clang` or `MSVSC` would also work fine.

## Compiling and Executing

### Nix

Luapp is packaged as a nix flake. Just cd into the project directory and run
`nix build`. You will then see a binary in `result/bin/luappc`.

For a development shell, run `nix develop`.

If you want to build a statically linked binary, run `nix build .#static`.

### Non-Nix

1. Make sure that you have `make`, `flex`, and `bison` installed. To install them on a Linux machine run the following code:

```
sudo apt update
sudo apt install flex
sudo apt install bison
```

2. Venture into the folder of the project that you would like to compile (e.g. `compiler/`).
3. Build and run it like so:

```
make
./bin/luapp ...
```
