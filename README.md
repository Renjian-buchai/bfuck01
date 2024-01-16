# Brainfuck Interpreter 01 

## Usage 

```ps
brainfck <source file>
```

## Explanation 

Brainfuck is a esoteric programming language that was designed to create the smallest compiler possible. Unfortunately, my complier takes up 160 kilobytes, but good enough. 

## Further plans

1. Enable it to generate an executable 
1. Optimise it better 
1. ??? 

## Bug reports 

Report if you want to. Doesn't matter. It's a hobby project. No one will use this anyways. \(: 

## Build instructions 

In project root directory, run 

```ps
make debug  # Debug build 
make        # Dev build 
make prod   # Production build
```

### Dependencies 

- None 

If your compiler is not g++, just replace `CC=g++` in the makefile with the compiler of your choice. 
