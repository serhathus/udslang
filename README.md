# UDS Language

This repository contains a simple interpreter for a toy DSL that supports integer variables, basic control flow and a few custom commands.

## Building

Compile the interpreter with `make`. This requires `bison`, `flex`, and a C++17 compiler.

```bash
make
```

## Running

After building, run the interpreter on a DSL file:

```bash
./tds sample.tds
```

A small example program is provided in `sample.tds`.
