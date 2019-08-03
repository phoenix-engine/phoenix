set(SDLTexture_SRCS
  texture.cxx
)

add_library(SDLTexture STATIC ${SDLTexture_SRCS})

target_link_libraries(SDLTexture
  SDL2
  Error
)

target_include_directories(SDLTexture PUBLIC
  ${Phoenix_INCLUDE_DIR}
)

set_property(TARGET SDLTexture PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLTexture PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLTexture PROPERTY CXX_STANDARD_REQUIRED ON)
