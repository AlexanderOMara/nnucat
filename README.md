# nnucat

nnucat - non-null union cat

# Overview

Takes the first non-null byte from a set of files at each offset and outputs it to stdout.

# Usage

```
Usage: ./bin/nnucat [file ...]
```

# Compiling

## Linux with optimizations

```bash
make CFLAGS='-O3'
```

## macOS with optimizations (Apple Silicon and Intel universal binary)

```bash
make CFLAGS='-O3 -arch arm64 -arch x86_64'
```

# Bugs

If you find a bug or have compatibility issues, please open a ticket under issues section for this repository.

# License

Copyright (c) 2023 Alexander O'Mara

Licensed under the Mozilla Public License, v. 2.0.

If this license does not work for you, feel free to contact me.
