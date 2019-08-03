set(SDLInput_SRCS
  sdl_input.cxx
)

add_library(SDLInput STATIC ${SDLInput_SRCS})

target_link_libraries(SDLInput 
  SDL2
  Consumer
)

target_include_directories(SDLInput PUBLIC
  ${Phoenix_INCLUDE_DIR}
)

set_property(TARGET SDLInput PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLInput PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLInput PROPERTY CXX_STANDARD_REQUIRED ON)
