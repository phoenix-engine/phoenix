add_subdirectory(init_util)
add_subdirectory(init_video)
add_subdirectory(display)
add_subdirectory(window)
add_subdirectory(renderer)
add_subdirectory(gl_renderer)
add_subdirectory(texture)

set(SDLUtil_SRCS
  sdl_util.cxx
)

add_library(SDLUtil STATIC ${SDLUtil_SRCS})

find_package(SDL2 REQUIRED)

target_include_directories(SDLUtil PUBLIC
  ${SDL2_INCLUDE_DIR}
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/sdl
)

target_link_libraries(SDLUtil
  ${SDL2_LIBRARY}
  Error
  SDLInitUtil
  SDLInitVideo
  SDLDisplay
  SDLWindow
  Graphics
)

set_property(TARGET SDLUtil PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLUtil PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLUtil PROPERTY CXX_STANDARD_REQUIRED ON)
