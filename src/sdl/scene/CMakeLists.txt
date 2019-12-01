set(SDLScene_SRCS
  scene.cxx
)

find_package(Vulkan REQUIRED)

add_library(SDLScene STATIC ${SDLScene_SRCS})

target_link_libraries(SDLScene
  Resource
  glm
  Vulkan::Vulkan
)

target_include_directories(SDLScene PUBLIC
  ${Phoenix_INCLUDE_DIR}
)

set_property(TARGET SDLScene PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLScene PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLScene PROPERTY CXX_STANDARD_REQUIRED ON)
