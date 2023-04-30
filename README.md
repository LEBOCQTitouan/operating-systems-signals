# Operating system : system signals

This package provides a simple way to handle system signals in C.

## Installation

### Dependencies

* [Make]("https://www.gnu.org/software/make/") / [CMake](https://cmake.org/) : For building the project
* [gnuplot](http://www.gnuplot.info/) : For displaying data curves

### Building

#### Using Make

```bash
make
```

#### Using CMake

```bash
mkdir build
cmake --build build
```

## Project description

This project is a simple implementation of a system signal handler in C. It provides a way to handle custom system
signals.

Here the parent process creates child processes and sends them signals. The child processes handle the signals and
compute the sin and cos of a given value. The parent process displays the results in gnuplot windows using two other
child processes.