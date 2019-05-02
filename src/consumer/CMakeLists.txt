set(Consumer_SRCS consumer.cxx)

add_library(Consumer STATIC ${Consumer_SRCS})

target_include_directories(Consumer PUBLIC
  ${Phoenix_INCLUDE_DIR}
)

set_property(TARGET Consumer PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET Consumer PROPERTY CXX_STANDARD 17)
set_property(TARGET Consumer PROPERTY CXX_STANDARD_REQUIRED ON)
