set(SDLGLRenderer_SRCS
  gl_renderer.cxx
)

add_library(SDLGLRenderer STATIC ${SDLGLRenderer_SRCS})

find_package(SDL2 REQUIRED)

target_include_directories(SDLGLRenderer PUBLIC
  ${GLAD_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIR}
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/sdl
)

target_link_libraries(SDLGLRenderer
  GLAD
  ${SDL2_LIBRARY}
  Error
)

set_property(TARGET SDLGLRenderer PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLGLRenderer PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLGLRenderer PROPERTY CXX_STANDARD_REQUIRED ON)
