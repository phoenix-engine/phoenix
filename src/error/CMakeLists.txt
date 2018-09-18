set(Error_SRCS init_error.cxx)

add_library(Error STATIC ${Error_SRCS})

target_include_directories(Error PUBLIC
  ${Phoenix_INCLUDE_DIR}/error
  ${SDL2_INCLUDE_DIR}/include
)

target_link_libraries(Error SDL2)

# set_target_properties(Error PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_property(TARGET Error PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET Error PROPERTY CXX_STANDARD 17)
set_property(TARGET Error PROPERTY CXX_STANDARD_REQUIRED ON)
