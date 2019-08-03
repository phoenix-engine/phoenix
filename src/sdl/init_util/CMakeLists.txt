set(SDLInitUtil_SRCS
  init_util.cxx
)

add_library(SDLInitUtil STATIC ${SDLInitUtil_SRCS})

target_link_libraries(SDLInitUtil
  SDL2
  Error
)

target_include_directories(SDLInitUtil PUBLIC
  ${Phoenix_INCLUDE_DIR}/sdl
)

set_property(TARGET SDLInitUtil PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLInitUtil PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLInitUtil PROPERTY CXX_STANDARD_REQUIRED ON)
