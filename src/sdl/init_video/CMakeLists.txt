set(SDLInitVideo_SRCS
  init_video.cxx
)

add_library(SDLInitVideo STATIC ${SDLInitVideo_SRCS})

target_include_directories(SDLInitVideo PUBLIC
  ${SDL2_INCLUDE_DIR}
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/sdl
)

target_link_libraries(SDLInitVideo
  SDL2
  Error
)

set_property(TARGET SDLInitVideo PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLInitVideo PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLInitVideo PROPERTY CXX_STANDARD_REQUIRED ON)
