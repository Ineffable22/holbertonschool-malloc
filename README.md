<div align="center">
<h1>My own Malloc</h1>
</div>

## Description
Welcome to Create Your Own Malloc at Holberton School! I am here to help you learn how to use the C malloc function. This function is a useful tool for dynamically allocating memory at runtime. This repository contains a variety of files to help you better understand this feature.

You'll find code samples that show how to use malloc, along with some tests to check if the code works correctly. There is also a Makefile that makes it easy to compile and run the program. Finally, this is a README file that contains information about the project and the included files.

If you're ready to start learning about malloc, this is the perfect place to start! Browse the archives and enjoy your journey to dynamic memory mastery!

Also, these functions are adapted to be used in multi-threading, which makes it even better in terms of learning and implementing multi-threading.


## Resources

### Read or watch:
- [Hack the Virtual Memory: malloc, the heap & the program break](https://blog.holbertonschool.com/hack-the-virtual-memory-malloc-the-heap-the-program-break/)
- [Everything you need to know to write your own malloc](https://intranet.hbtn.io/concepts/80)

### man or help:
- `sbrk`
- `brk`
- `malloc`

# Learning Objectives
At the end of this project, you are expected to be able to [explain to anyone](https://fs.blog/feynman-learning-technique/), without the help of Google:

## General
- What is a program break
- How to play with a program break in order to allocate memory dynamically
- How the glibc `malloc` and `free` functions work
- What is ASLR
- What is memory alignment
- What is a memory page
- How to encapsulate the memory management in order to hide it from the user

# Requirements
## General
- Allowed editors: `vi`, `vim`, `emacs`
- All your files will be compiled on `Ubuntu 14.04 LTS`
- Your C programs and functions will be compiled with `gcc 4.8.4` using the flags `-Wall -Werror -Wextra and -pedantic`
- All your files should end with a new line
- A `README.md` file, at the root of the folder of the project, is mandatory
- Your code should use the `Betty` style. It will be checked using [betty-style.pl](https://github.com/hs-hq/Betty/blob/main/betty-style.pl) and [betty-doc.pl](https://github.com/hs-hq/Betty/blob/main/betty-doc.pl)
- You are not allowed to have more than 5 functions per file
- The prototypes of all your functions should be included in your header file called malloc.h
- Don’t forget to push your header files
- All your header files should be include guarded
- You are allowed to use `global` variables
- You are allowed to use `static` variables

## Betty Compliance
- All the C source files in your directory and subdirectories must be [Betty-compliant](https://intranet.hbtn.io/rltoken/zV6oB-YNOpGlVe_6_ywzCA)

## Allowed Functions and System Calls
- Unless specified otherwise, you are allowed to use the C standard library
- Of course, you’re not allowed to use the `malloc` family from the C library…

## Tests
- It is strongly advised to test your functions against real programs, like a shell, or your old projects for example.
- To do so, you can name your functions `malloc`, `free`, `realloc` and `calloc` (just like they’re name in the glibc), and compile them into a shared library that you would load when executing a program using `LD_LIBRARY_PATH` and `LD_PRELOAD`
- [Here’s a tutorial on how to do it](https://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html)

# More Info
## Important
It is not required that your `_malloc`, `free`, `calloc` and `realloc` behave exactly like the glibc `malloc`, `free`, `calloc` and `realloc`:

- You are free to use any data structure that suits you as long as their purpose is well defined
- You are free to handle the heap as it suits you, as long as the returned pointers (for the functions that return a pointer) are aligned as required and that enough space is available
- You are free to extend the program break as it suits you, as long as it is extended by a multiple of the virtual memory page size, and as long as it is reduced when needed
- You decide of your implementation. During the correction, we will mainly focus on the strength and reliability of your functions, so make sure to handle big allocations :)


## Author:
<div align="center">
<a href="https://www.linkedin.com/in/miguel-enrique-grillo-orellana/">
<img src="https://img.shields.io/badge/Miguel-Linkedind-blue"></a>


<a href="https://medium.com/@Miguel_Grillo"><img src="https://miro.medium.com/max/1200/0*jTIO9a1_5T3mv-pR.png" alt="Link Medium" width="100px" height= "50px"></a>
</div>
