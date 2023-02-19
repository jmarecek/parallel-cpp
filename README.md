# Parallel Programming in C++

This repository contains the LaTeX source and C++ code samples for lecture notes on Parallel Programming in C++.

## Changelog

- `0.1.0` First pre-release

## Building from sources

The repository is configured with VSCode devcontainer support.

Make sure that you have VSCode and Docker installed, then simply open the repository in VSCode. You will be prompted to reopen the project in a docker image.

VSCode is configured to use the LaTeX Workshop extension. To build the PDF simply press `CTRL+ALT+B` or select `LaTeX Workshop: Build LaTeX Project` from the command palette.
Note that due to the high number of code examples, the build does take a while.
The resulting PDF will be in the build folder.

### Code samples

Most code files have wrapping main files that exercise both the build and also contain `assert` expressions that verify correctness of the code.

The `verify.sh` shell script will build all (except for a few that don't compile with GCC 11) examples, and then run each of them to validate all asserts.

### Lecture notes

To build the PDF of the lecture notes, issue `pdflatex --shell-escape book`. 
