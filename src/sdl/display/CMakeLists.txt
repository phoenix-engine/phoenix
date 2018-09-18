set(SDLDisplay_SRCS
  display.cxx
)

add_library(SDLDisplay STATIC ${SDLDisplay_SRCS})

find_package(SDL2 REQUIRED)

target_include_directories(SDLDisplay PUBLIC
  ${SDL2_INCLUDE_DIR}
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/sdl
)

target_link_libraries(SDLDisplay
  ${SDL2_LIBRARY}
  Error
)

set_property(TARGET SDLDisplay PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLDisplay PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLDisplay PROPERTY CXX_STANDARD_REQUIRED ON)
