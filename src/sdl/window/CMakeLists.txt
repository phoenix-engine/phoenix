set(SDLWindow_SRCS
  window.cxx
)

add_library(SDLWindow STATIC ${SDLWindow_SRCS})

target_link_libraries(SDLWindow
  SDL2
  Error
)

target_include_directories(SDLWindow PUBLIC
  ${Phoenix_INCLUDE_DIR}/sdl
)

set_property(TARGET SDLWindow PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLWindow PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLWindow PROPERTY CXX_STANDARD_REQUIRED ON)
