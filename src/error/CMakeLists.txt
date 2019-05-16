set(Error_SRCS init_error.cxx)

if(NOT(APPLE OR IOS))
  set(Error_SRCS init_error.cxx sdl_init_error.cxx)
endif()

add_library(Error STATIC ${Error_SRCS})

target_include_directories(Error PUBLIC
  ${Phoenix_INCLUDE_DIR}
)

if(NOT(APPLE OR IOS))
  target_include_directories(Error PUBLIC
    ${SDL2_INCLUDE_DIR}
  )
endif()

set_property(TARGET Error PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET Error PROPERTY CXX_STANDARD 17)
set_property(TARGET Error PROPERTY CXX_STANDARD_REQUIRED ON)
