# Lua++ programming language
This is the Lua++ C lang build, currently in development but is soon to be completed. If you are interested in learning more about this project, please visit our website: [luaplusplus.org](https://www.luaplusplus.org). This codebase is not specifically tweaked to a certain compiler, so any C/C++ compiler should be able to build this project easily. Personally, I recommend building it with ```gcc``` although ```clang``` or ```MSVSC``` would also work fine.

### How to use
1. Make sure that you have ``make``, ``flex``, and ``bison`` installed. To install them on a Linux machine run the following commands:
```
sudo apt update
sudo apt install flex
sudo apt install bison
sudo apt install make
```
2. Enter the main source folder and build the desired project (e.g. ```make interpreter```)
3. Then run the binary that was produced by this command
```
./bin/luapp
...
```

### Compiler
The current complier is very user friendly. It consists of four stages: ``lexer``, ``parser``, ``ir``, and ``codegen``. These are all toggable via the ``-s`` command line argument. This gives you the ability to inspect each stage of the compiler in detail. The usage for the compiler binary is provided below:
```
luappc -s [lexer|parser|type|symbol|ir|codgen] -o [outputfile] [inputfile]

 -s : indicates the name of the stage to stop after.
      Defaults to the last stage.
 -o : name of the output file. Defaults to "output.s"

You should pass the name of the file to compile.
```
