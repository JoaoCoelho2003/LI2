# LI2- Interpreter for a Stack Oriented Programming Language

## Overview

LI2 is an interpreter for a stack-oriented programming language was developed as a group project during the second semester of the Software Engineering degree at the University of Minho. The project was part of the "Laboratórios de Informática II" subject and involved the full development process.

## Description

The interpreter allows users to write programs using a stack-based approach, similar to a calculator but with additional functionality. The specifics about the syntax is explained to a greater detail [here](docs/project.pdf).

## Dependencies

This project was developed in C, which means a C compiler is needed to compile and run the program. Namely GCC, which can be installed using various package managers depending on your Linux distribution. Here are some examples:

### Debian/Ubuntu-based distributions (using apt):

```
$ sudo apt update
$ sudo apt install gcc
```

### Fedora-based distributions (using dnf):

```
$ sudo dnf install gcc
```

### Arch-based distributions (using pacman):

```
$ sudo pacman -S gcc
```

### Manjaro Linux (using pamac):

```
$ sudo pamac install gcc
```

Feel free to choose the appropriate command based on your Linux distribution and package manager.

## Cloning the Repository

To clone the repository, run the following command in your terminal:

```
$ git clone https://github.com/JoaoCoelho2003/LI2.git
```

Once cloned, navigate to the repository directory using the cd command:

```
$ cd LI2
```

## Compiling and Running

To compile the project, navigate to the source code directory:

```
$ cd src
```

Then, execute the following command to compile the project:

```
$ gcc -O2 *.c -o project -lm
```

This command compiles all `.c` files in the directory into an executable named `project`, with optimization level 2 (`-O2`). The `-lm` flag is used to link the math library.

To run the compiled executable, use the following command:

```
$ ./project
```


This will execute the interpreter and allow you to start using the stack-oriented programming language.

## Conclusion

We hope you find using the LI2 interpreter both educational and enjoyable! If you have any questions or feedback, feel free to reach out. Happy coding!

## Developed by

**A100506** João Coelho

**A100642** Lucas Quintela

**A100606** Inês Marques

**A100743** Marta Rodrigues












