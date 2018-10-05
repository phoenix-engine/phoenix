set(SDLRenderer_SRCS
  sdl_renderer.cxx
)

add_library(SDLRenderer STATIC ${SDLRenderer_SRCS})

target_include_directories(SDLRenderer PUBLIC
  ${SDL2_INCLUDE_DIR}/include
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/sdl
)

target_link_libraries(SDLRenderer
  SDL2
  Error
  SDLHelper
  SDLTexture
)

set_property(TARGET SDLRenderer PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLRenderer PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLRenderer PROPERTY CXX_STANDARD_REQUIRED ON)
