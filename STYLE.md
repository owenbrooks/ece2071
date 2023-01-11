# ECE2071 C Style Guide
Based on the rules in the Google C++ Style Guide.

## File Names
Filenames should be all lowercase and can include underscores (_)
C files should end in .c and header files should end in .h: `my_useful_class.c`

## Type Names
Type names start with a capital letter and have a capital letter for each new word, with no underscores: `MyExcitingClass`, `MyExcitingEnum`

## Variable Names
The names of variables (including function parameters) and data members are all lowercase, with underscores between words. For instance: `a_local_variable`, `a_struct_data_member`.

In general the actual name of the variable should be descriptive enough to give a good idea of what the variable is used for. In certain cases, more comments are required.

## Constant Names
Variables declared const, and whose value is fixed for the duration of the program, are named in all capitals. Underscores can be used as separators. For example:

```c
const int DAYS_IN_A_WEEK = 7;
const int ANDROID8_0_0 = 24;  // Android 8.0.0
```

## Comment Style
Use `//` for comments.

## Indentation
4 spaces should be used for indentation. 
In VSCode: CMD-Shift-P (or Ctrl-Shift-P), Indent Using Spaces, 4

