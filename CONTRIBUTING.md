# Contributing

Thanks for considering to contribute to this project. This document lays out a few guidelines for making an acceptable pull request.

## Style
Variables are in camel case, while types and functions are in pascal case. Enums and definitions are in uppercase snake case. Here are a few examples:
```c
struct {
    bool running;
} emu;

typedef struct {
    int x, y;
} CoolType;

typedef struct {
    char property[12];
    CoolType position;
    int counter;
} CoolLongType;

void CoolFunction( int args, int must, int be, int spaced ) {
    // ...
}

// ...

int coolVariableX = 1;
int coolVariableY = 5;
CoolType variable = { 0, 1 };
CoolLongType longVariable = {
    .property = "Cheese",     // Comments
    .position = variable,     // should be
    .counter = 45,            // spaced like so
};
```

Lastly, here are some other notes:
- Try to keep lines shorter than 80 characters
- Document your functions/structs
- Try to make functions only do one simple task
- The main program (emu.c) is not in pascal case and is abbreviated
- Avoid globals
- Arrange functions, enums, etc in ascending numerical order
- Ensure that the main branch has working code

## Security
Since C is not a memory-safe language, do not use unsafe functions like: `gets`, `scanf`, `sprintf`, `system`, etc. In other words, when working with buffers, ensure that an overflow is impossible. Try to avoid using heap-allocated memory, but when necessary free it when it is no longer needed.

## Building
The current codebase was written on Windows 11 and so far it should be compatible with other platforms. For Linux, gcc, nasm, and make are required. For Windows, I use [w64devkit](https://github.com/skeeto/w64devkit/releases).

To build, create the `build/` directory and run `make`.