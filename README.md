# conan-llvm

This repository provides a conan recipe for the LLVM/Clang Compiler Infrastructure
project.

Starting from LLVM release version 8.0.0 the recipe packages the complete set of
libraries and files which comes with the original install target.


## Options

| Option | Default | Description |
| enable_zlib | False | Enables the usage of zlib library   | 


## LLVM Patch 

The recipe includes a patch of the clang cmake files to satisfy the usage
requirements when a clang library is used. 

What does this mean?

The original clang cmake files specifies the dependencies of libraries but the 
include path is not set or specified. 


## Supported Compiler



## Developer Notes

### Packaging

Important to export the libraries to the package. If it is not set no library
can be used by the user by the cmake variable ${CONAN_LIBS}

self.cpp_info.libs = list(files)

### Development

The recipe can be developed according to the guidelines in https://docs.conan.io/en/latest/developing_packages/package_dev_flow.html. Rake tasks exists to handle the development flow steps:

rake conan:source
rake conan:install
rake conan:build
rake conan:package
rake conan:export
rake conan:test

