# Libsus

The Small Utility Structs (SUS) is a collection of pieces of code from several projects of mine that I decided to package neatly for reusability.

## Documentation

There is no documentation at this point, this is still being worked on.

## Building

**Requirements:**

- `gcc`
- `make`

To build the library, ensure you have the above listed requirements, after which, you may simply:

1. Clone the repository.
1. Use `make build` to compile, output will be put in `build/bin/libsus.a`
1. (Optionally) Use `sudo make install` to copy the headers and `.a` to `/usr/local/`

Note that when updating your install of libsus you may have to `make uninstall` before installing again to clear any files that are no longer needed.
