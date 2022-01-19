# ares
> *The* Ares *Programming Language*

***

## What is this?

> This started as a school project, but after that I used some of my free time to expand it with more features

+ It is a compiled language for writing basic scripts.
+ Support for Numeric & Boolean data types.
+ 1 level of scope for functions, but hey there's 3 kinds of loops.
+ I know, that's pretty lame for calling it a 'Programming Language'
+ Because of that I tried to make it cooler by naming it like a Greek God
+ You probably don't want to use it for any serious thing. I really wouldn't.


## How to install?

> In order to *compile the compiler*, just run `make all` on your terminal. 

Or you can run `make help` for more information:

```
Makefile Options:
    all              - compiles everything & generates the ares executable
    clean               - deletes all files generated during compiling
    runf                - compiles an ARES file and executes it
                             -> Usage: make runf src=<SOURCECODE_ARES>
                             -> Generates an executable file called 'exe'
    valgrind            - runs valgrind over the compiler through a source file
                             -> Usage: make valgrind src=<SOURCECODE_ARES>
    astyle              - styles code according to .astylerc file
    reset               - runs the rule 'make clean' first, and then 'make all'
```

I'm genuinely surprised you made it this far and went to download my quirky compiler. Thanks! :D

## How to compile files?

> Just compile the compiler's executable file, and then run:

```
./ares -f <SOURCECODE_ARES> -o <OUTPUT_FILE>
```

1. `<SOURCECODE_ARES>`: Contains the program written in Ares code
2. `<OUTPUT_FILE>`: Name of the executable file to be generated

To get a full list of the Ares executable flags, run `./ares -h`:

```
Options
    -h: shows this help
    -f: source code file with `.ares` extension
    -o: output executable file name
    -d: enables DEBUG mode. Generates executable from source code AND the x86 NASM intermediate code
    -u: uninstalls the ARES compiler
```

## How do I run the tests?

> Just compile & run them like you would run any other Ares program

In the `tests/` directory there is a vast battery of test programs to check how to code in Ares.

In order to compile them, you can use the `./ares` executable or the makefile rule:

```
make runf src=<SOURCECODE_ARES>
```

For example, in order to run the **fibonacci.ares** test file, which is in the `tests/` folder:

```
make runf src=tests/fibonacci.ares
```

This will generate an executable called 'exe' and run it automatically for you.
