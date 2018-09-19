add_subdirectory(error)
add_subdirectory(sdl)
add_subdirectory(graphics)

set(Phoenix_SRCS phoenix.cxx)

if(WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS on)
endif()

add_library(Phoenix SHARED ${Phoenix_SRCS})

target_include_directories(Phoenix PUBLIC
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/phoenix
  ${Phoenix_INCLUDE_DIR}/sdl
  ${Phoenix_INCLUDE_DIR}/graphics
)

target_link_libraries(Phoenix
  Error
  SDLUtil
  SDLGLRenderer
  Graphics
)

set_property(TARGET Phoenix PROPERTY CXX_STANDARD 17)
set_property(TARGET Phoenix PROPERTY CXX_STANDARD_REQUIRED ON)
