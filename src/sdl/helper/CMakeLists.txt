set(SDLHelper_SRCS
  helper.cxx
)

add_library(SDLHelper STATIC ${SDLHelper_SRCS})
# add_library(SDLHelper SHARED ${SDLHelper_SRCS})

target_include_directories(SDLHelper PUBLIC
  ${SDL2_INCLUDE_DIR}/include
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/sdl
)

target_link_libraries(SDLHelper
  SDL2
  Error
)

set_property(TARGET SDLHelper PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLHelper PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLHelper PROPERTY CXX_STANDARD_REQUIRED ON)
