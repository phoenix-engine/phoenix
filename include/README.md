# Phoenix Headers

This contains simple CMake target which allows the Phoenix headers to be
configured as a dependency, and exposes them in Xcode.

Of course, you should also understand the headers themselves.

Important namespaces, classes, and template parameters follow:

- [phx::Phoenix](phoenix.hpp)
  - Consumer
  - Renderer
  - RenderPayload
- [gfx::Graphics](graphics.hpp)
  - [gfx::Renderer](renderer.hpp) (specifies the rendering interface)
  - RenderPayload (passed to the Renderer, for example, `MTKView*`)
- [input::Input](input.hpp)
  - [Consumer](input.hpp)
  - States (see Simple)
  - [Simple (a Consumer implementation)](../src/consumer/consumer.cxx)
- [queue::Queue](queue.hpp)
  - EventQueue
- [event::Event](event.hpp)
  - EventWantsQuit
  - EventIntent
  - EventLostIntent
  - EventDraggingBox
  - EventFinishedBox
- [phx_err::InitError](init_error.hpp)
  - [phx_err::SDLInitError](sdl_init_error.hpp)
