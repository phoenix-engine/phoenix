set(SDLWindow_SRCS
  window.cxx
)

add_library(SDLWindow STATIC ${SDLWindow_SRCS})

find_package(SDL2 REQUIRED)

target_include_directories(SDLWindow PUBLIC
  ${SDL2_INCLUDE_DIR}
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/sdl
)

target_link_libraries(SDLWindow
  ${SDL2_LIBRARY}
  Error
)

set_property(TARGET SDLWindow PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLWindow PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLWindow PROPERTY CXX_STANDARD_REQUIRED ON)
