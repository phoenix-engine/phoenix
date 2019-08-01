# Developing Phoenix

- [C++](#c++)
- [Git](#git)
- [CMake](#cmake)
- [The `phx` CLI](#the-phx-cli)
- [Platforms](#platforms)
  - [Vulkan](#vulkan)
  - [Metal](#metal)

# C++

Phoenix uses C++ 17.  Please ensure that your developer environment
supports it.

# Git

## Git Submodules

Phoenix uses Git submodules to manage its dependencies.  To fetch and/or
update its dependencies, use the following command:

```sh
$ git submodule update --init --recursive
```

If you want to work on one of its submodules, you can fork it on Github
and add your fork as a remote.

> Example, working on `glm`:

```sh
$ cd dep/glm
$ git remote -v

...

$ git remote rename origin upstream
$ git remote add origin git@github.com:<me>/glm.git
$ git checkout -b dev-<feature>

# Do some work...

$ git push origin dev-<feature>

```

Then open a pull request from your fork.

# CMake

Phoenix is built using CMake.  

In order to generate shaders and other internal resources for Phoenix,
the user should first install the [`phx` tool](https://github.com/phoenix-engine/phx).

> Once Go is installed and set up...

```sh
$ go get -u -v github.com/phoenix-engine/phx/...
```

# The `phx` CLI

The `phx` CLI provides tools for working with assets.

```sh
$ phx help gen

...

$ phx gen -l 9 --to dep/res
```

# Platforms

## Vulkan

### Windows

### Linux

### Android

## Metal

### macOS

### iOS
