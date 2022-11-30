# Lua++ programming language
This is the Lua++ C lang build, currently in development but is soon to be completed. This codebase is not specifically tweaked to a certain compiler, so any C/C++ compiler should be able to build this project easily. Personally, I recommend building it with ```gcc``` although ```clang``` or ```MSVSC``` would also work fine.

### How to compile and run
1. Make sure that you have ``make``, ``flex``, and ``bison`` installed. To install them on a Linux machine run the following code:
```
sudo apt update
sudo apt install flex
sudo apt install bison
```
2. Enter the main source folder and run ``make compiler`` or ``make vm`` based on the project you would like to build. 
3. Then run the binary file located in `src/bin`.
```
make
./bin/luappc ...
```


