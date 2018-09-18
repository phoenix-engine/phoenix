# SDL utilities

This package is for configuring and initializing SDL.  The main class is
SDLUtil.  It configures and contains other SDL classes.  However, it
leaves the choice of rendering context to the caller.  It is mainly for
getting a Window loaded and properly configured.

Renderer and GLRenderer are graphics context handles.  GLRenderer is for
working directly with OpenGL; Renderer is an SDL type which works with
SDL's Texture, etc. classes.  These have their own configuration and
require only a Window handle, so first create an SDLUtil, then use its
Window handle to initialize a rendering context.

- [Display](display.hpp)
- [Renderer](renderer.hpp)
- [GLRenderer](gl_renderer.hpp)
- [InitUtil](init_util.hpp)
- [InitVideo](init_video.hpp)
- [SDLUtil](sdl_util.hpp)
- [Texture](texture.hpp)
- [Window](window.hpp)
