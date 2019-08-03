set(SDLHelper_SRCS
  helper.cxx
)

add_library(SDLHelper STATIC ${SDLHelper_SRCS})

target_link_libraries(SDLHelper
  SDL2
  Error
)

target_include_directories(SDLHelper PUBLIC
  ${Phoenix_INCLUDE_DIR}/sdl
)

set_property(TARGET SDLHelper PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLHelper PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLHelper PROPERTY CXX_STANDARD_REQUIRED ON)
