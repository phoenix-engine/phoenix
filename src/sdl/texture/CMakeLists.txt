set(SDLTexture_SRCS
  texture.cxx
)

add_library(SDLTexture STATIC ${SDLTexture_SRCS})

target_include_directories(SDLTexture PUBLIC
  ${SDL2_INCLUDE_DIR}/include
  ${Phoenix_INCLUDE_DIR}/error
  ${Phoenix_INCLUDE_DIR}/sdl
)

target_link_libraries(SDLTexture
  SDL2
  Error
)

set_property(TARGET SDLTexture PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLTexture PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLTexture PROPERTY CXX_STANDARD_REQUIRED ON)
