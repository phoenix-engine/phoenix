set(SDLDisplay_SRCS
  display.cxx
)

add_library(SDLDisplay STATIC ${SDLDisplay_SRCS})

target_link_libraries(SDLDisplay
  SDL2
  Error
)

target_include_directories(SDLDisplay PUBLIC
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/sdl
)

set_property(TARGET SDLDisplay PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLDisplay PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLDisplay PROPERTY CXX_STANDARD_REQUIRED ON)
