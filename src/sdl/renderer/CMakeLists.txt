set(SDLRenderer_SRCS
  renderer.cxx
)

add_library(SDLRenderer STATIC ${SDLRenderer_SRCS})

target_include_directories(SDLRenderer PUBLIC
  ${GLAD_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIR}
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/sdl
)

target_link_libraries(SDLRenderer
  GLAD
  SDL2
  Error
  SDLTexture
)

set_property(TARGET SDLRenderer PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLRenderer PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLRenderer PROPERTY CXX_STANDARD_REQUIRED ON)
