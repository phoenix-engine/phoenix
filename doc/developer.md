# Developing Phoenix

- [C++](#c)
- [Git](#git)
- [CMake](#cmake)
- [The `phx` CLI](#the-phx-cli)
  - [Assets](#assets)
- [Graphics Backends](#graphics-backends)
  - [Vulkan](#vulkan)
  - [Metal](#metal)
- [Platforms](#platforms)

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

# ...

$ git remote rename origin upstream
$ git remote add origin git@github.com:<me>/glm.git
$ git checkout -b dev-<feature>

# Do some work...

$ git push origin dev-<feature>
```

Then open a pull request from your fork.

# CMake

Phoenix is a [CMake](https://cmake.org) project.  You may simply add it
using `add_subdirectory` in your own project, and it will then be
available by the name `Phoenix`.  Phoenix requires CMake version 3.14 or
greater.

```sh
$ mkdir build
$ cd build
# Use cmake --help to list all generator options if you don't want to
# use Ninja.
$ cmake -G Ninja .. -DCMAKE_BUILD_TYPE=Debug
$ ninja
# ...
```

# The `phx` CLI

In order to generate libraries containing assets for Phoenix, you should
first install [the `phx` tool](https://github.com/phoenix-engine/phx).
For now, it requires [Go](https://golang.org) to be installed.

> Once Go is installed and set up...

```sh
$ go get -u -v github.com/phoenix-engine/phx/...
```

## Assets

The `phx` CLI provides tools for working with assets.

```sh
$ phx help gen

# ...

$ phx gen -l 9 --to ../dep/res --match ".*\.(jpg|spv|wav)"
```

Now a customized compressed streaming asset library is included in the
target directory.  You can add it to your code as a CMake library using
`add_subdirectory`.  It will then be available in CMake by the name
`Resource`.  To use Resource assets in your code, see the
[usage in `phx_sdl::VKRenderer`](../src/sdl/vk_renderer).

> helper function `read_all`:

```cpp
std::vector<char> read_all(res::ID id) {
    const auto& r = res::Mapper::Fetch(id);

    const auto& len = r->Len();

    std::vector<char> into(len);

    size_t consumed = 0;
    while (consumed < len) {
	consumed += r->Read(into.data() + consumed, len - consumed);
    };

    return into;
}
```

> decompressing and loading assets:
> in this case, the input files were named `frag.spv` and `vert.spv`.

```cpp
const auto& frag_data = read_all(res::ID::frag_spv);
const auto& vert_data = read_all(res::ID::vert_spv);

```

# Graphics Backends

## Vulkan

### Tutorial, Spec, and C++ Headers

The [Vulkan Tutorial](https://vulkan-tutorial.com/) is a valuable
resource to familiarize yourself with the Vulkan API and how it works.
For more detail, please refer to the
[Vulkan 1.1 spec](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/).

Note that the Vulkan spec describes the C interface to Vulkan, but
Phoenix uses the
[typesafe C++ wrapper](https://github.com/KhronosGroup/Vulkan-Hpp).
Conventions are documented in the `Vulkan-Hpp` repo.  It is essentially
identical but provides some idiomatic C++ interfaces.

### Debugging, and the Vulkan SDK

Vulkan is provided by the graphics drivers of supported platforms, but
when [`phx_sdl::VKRenderer`](../include/phx_sdl/vk_renderer.hpp) is
built in debug mode (i.e., `VKRenderer<true>`), extra Vulkan debug
functionality such as
[validation layers](https://github.com/KhronosGroup/Vulkan-ValidationLayers)
and
[debug messengers](https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/chap39.html#debugging-debug-messengers)
are enabled which require
[the Vulkan SDK](https://vulkan.lunarg.com/sdk/home) to be installed.

### Shaders

Required tools:
- [glslangValidator](https://www.lunarg.com/vulkan-sdk/)
- [Phoenix CLI](https://github.com/phoenix-engine/phx)

To run shader code on the GPU, Vulkan requires precompiled SPIR-V
bitcode to ensure uniformity across different implementations.

To compile GLSL into SPIR-V, you need the `glslangValidator` tool.  It
comes with the Vulkan SDK, or you can build it yourself.  See the
[docs](https://github.com/KhronosGroup/glslang#building) for more
information.

Some editors include plugins for working with GLSL shaders.  In Emacs,
you can install
[`company-glsl`](https://github.com/guidoschmidt/company-glsl).

To work with shaders in Phoenix, they must be associated with a
[Scene](../include/phx_sdl/scene.hpp).  VKRenderer is constructed with a
Scene which tells it how to set up its draw commands, and what shaders
to use.

The CMake build has a target which can be used to manually rebuild and
redeploy shader assets, called `GenerateShaderResources`.  Due to a bug,
this currently must be built twice to get the latest generated files in
the Resource library.

To build this target, you can run e.g. `ninja GenerateShaderResources`
from your developer shell, or switch to "CMake Targets View" in Visual
Studio's "Solution Explorer" toolbox.  See
[CMake Projects in Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019)
for more details.


### SDL2

Phoenix on Vulkan uses [SDL2](https://www.libsdl.org/) to provide
windowing and limited other native platform functionality, such as
loading Vulkan and identifying graphics hardware.

## Metal

Phoenix supports Metal platforms using a Cocoa ViewController class.
Please see [../CocoaPhoenix/README.md](../CocoaPhoenix/README.md) for
further information.

Xcode is suggested.

# Platforms

## Windows

Phoenix supports Visual Studio 2019 on Windows, optionally using the
[Ninja build tool](https://github.com/ninja-build/ninja).

## Linux

## Android

## macOS

## iOS
