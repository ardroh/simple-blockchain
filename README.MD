# Simple Blockchain

A simple blockchain-based cryptocurrency written in C++ to learn a little about how blockchain works. For cryptography operations OpenSSL has been used.

Build tested on Ubuntu and MacOS.

## Libraries used
* OpenSSL (v3)
* CMake

## Building

```sh
mkdir -p ./build;
pushd ./build;
cmake ..; # See also "Debug build"
make
```

### Debug build
For debug build change the cmake command to `cmake -DCMAKE_BUILD_TYPE=Debug ..`.

## To Do
(draft)

* Currently accounts have no way to get the initial founds, so there is a need to implement a mining mechanism even if no transactions are made.