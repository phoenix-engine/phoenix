add_subdirectory(error)
add_subdirectory(sdl)
add_subdirectory(graphics)
# add_subdirectory(world)

set(Phoenix_SRCS phoenix.cxx)

add_library(Phoenix SHARED ${Phoenix_SRCS})

target_include_directories(Phoenix PUBLIC
  # ${SDL2_INCLUDE_DIR}
  # ${GLAD_INCLUDE_DIR}
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/phoenix
#   # ${Phoenix_INCLUDE_DIR}/world
  ${Phoenix_INCLUDE_DIR}/sdl
  ${Phoenix_INCLUDE_DIR}/graphics
)

target_link_libraries(Phoenix
  # SDL2
  # GLAD
  Error
  SDLUtil
  SDLGLRenderer
#   # World
  Graphics
)

set_property(TARGET Phoenix PROPERTY CXX_STANDARD 17)
set_property(TARGET Phoenix PROPERTY CXX_STANDARD_REQUIRED ON)
