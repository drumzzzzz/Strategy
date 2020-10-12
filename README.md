CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Usage
 * Maintainers


INTRODUCTION
------------

Strategy design pattern project for UWGB Computer Science Fall semester, 2020.
Reads a list of command operation strings from file "operations.txt".
Iterates each operation and executes the associated strategy on a randomly generated integer array.

USAGE
------------
Operation list of possible commands in operations.txt:
generate
clear
ascending
descending
shuffle
minimum
maximum

The operation strings are lowercase sensitive.
The operation 'generate' must be called before performing any operation other than clear.
Each generate operation adds 20 random numbers (0 to 99), with a maximum array size of 100 values.

MAINTAINERS
-----------

 * Nathaniel Kennis - https://github.com/drumzzzzz

