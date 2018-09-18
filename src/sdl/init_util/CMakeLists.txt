set(SDLInitUtil_SRCS
  init_util.cxx
)

add_library(SDLInitUtil STATIC ${SDLInitUtil_SRCS})

target_include_directories(SDLInitUtil PUBLIC
  ${SDL2_INCLUDE_DIR}
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/sdl
)

target_link_libraries(SDLInitUtil
  SDL2
  Error
)

set_property(TARGET SDLInitUtil PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLInitUtil PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLInitUtil PROPERTY CXX_STANDARD_REQUIRED ON)
