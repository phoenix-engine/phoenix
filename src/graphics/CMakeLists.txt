project(Phoenix CXX C)

set(Graphics_SRCS
  graphics.cxx
)

add_library(Graphics STATIC ${Graphics_SRCS})

target_include_directories(Graphics PUBLIC
  ${SDL2_INCLUDE_DIR}
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/sdl
  ${Phoenix_INCLUDE_DIR}/graphics
)

target_link_libraries(Graphics
  SDL2
  Error
  SDLWindow
  SDLRenderer
  SDLGLRenderer
  SDLTexture
)

set_property(TARGET Graphics PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET Graphics PROPERTY CXX_STANDARD 17)
set_property(TARGET Graphics PROPERTY CXX_STANDARD_REQUIRED ON)
