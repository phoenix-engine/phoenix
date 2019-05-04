#  Phoenix Apple Components

---

This is an Xcode-native project stack which implements interfaces for
Phoenix components for iOS and macOS.  It supplies static libraries,
pure-C++ wrappers where necessary, and Apple-specific CMake modules to
support conditional inclusion in the Phoenix CMake build scripts.

### Status

- [x] Headers
- [x] PHXViewController
  - [x] PHXFactory
  - [x] PHXDefaultFactory
- [x] PHXResponder
- [x] PHXViewDelegate
- [x] PHXRenderer
  - [...] PHXShaders
  - [...] PHXMetal
  - [...] PHXDrawer
  - [...] PHXResourceManager

In particular, it supplies a Metal implementation of `gfx::Renderer`.

Please see [the docs](doc/README.md) for more information.

---

## Quickstart

Create and configure a `PHXRenderer`, then make a `pmtl::Renderer` from
it.  `pmtl::Renderer` implements the Phoenix `gfx::Renderer` interface,
so it can be used directly in Phoenix.

Then create a Phoenix object using the `pmtl::Renderer`:

```objc
#include "Renderer.hpp"
#include "PHXRenderer.hpp"

// ...

auto pr = [PHXRenderer makeWithView:v withFullscreen:YES];
auto r = mtlp::Renderer<PHXRenderer>(pr);
auto phx = phx::Phoenix(game, r);
```

## Design and Implementation

### Renderer

The `mtlp::Renderer Objective-C++ class exposes a pure-C++ interface to
PHXRenderer for Phoenix to use.

### PHXRenderer

The PHXRenderer Objective-C++ class is the core implementation of the
Metal backend for Phoenix.  It implements MTKViewDelegate for testing
purposes, but should be used as a Phoenix component through the
`mtlp::Renderer` class.

The PHXEventHandler class is a macOS / iOS compatibility layer for
Phoenix.  It allows a Phoenix object to be harnessed to the event-driven
architecture of an Apple application, under the control of the library
user.
