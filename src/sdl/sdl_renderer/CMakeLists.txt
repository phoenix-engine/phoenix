set(SDLRenderer_SRCS
  sdl_renderer.cxx
)

add_library(SDLRenderer STATIC ${SDLRenderer_SRCS})

target_link_libraries(SDLRenderer
  SDL2
  Error
  SDLHelper
  SDLTexture
)

target_include_directories(SDLRenderer PUBLIC
  ${Phoenix_INCLUDE_DIR}/sdl
)

set_property(TARGET SDLRenderer PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLRenderer PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLRenderer PROPERTY CXX_STANDARD_REQUIRED ON)
