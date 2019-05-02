set(Error_SRCS init_error.cxx)

if(NOT (APPLE OR IOS))
  set(Error_SRCS init_error.cxx sdl_init.error.cxx)
else()
endif()

add_library(Error STATIC ${Error_SRCS})

target_include_directories(Error PUBLIC
  ${Phoenix_INCLUDE_DIR}
)

set_property(TARGET Error PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET Error PROPERTY CXX_STANDARD 17)
set_property(TARGET Error PROPERTY CXX_STANDARD_REQUIRED ON)
