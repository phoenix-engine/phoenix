set(SDLVKRenderer_SRCS
  vk_renderer.cxx
)

add_library(SDLVKRenderer STATIC ${SDLVKRenderer_SRCS})

find_package(Vulkan REQUIRED)

target_link_libraries(SDLVKRenderer
  GLAD
  SDL2
  # Eigen3::Eigen
  glm
  Vulkan::Vulkan
  Error
  SDLHelper
  SDLScene
  Resource
)

target_include_directories(SDLVKRenderer PUBLIC
  ${Phoenix_INCLUDE_DIR}
)

set_property(TARGET SDLVKRenderer PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLVKRenderer PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLVKRenderer PROPERTY CXX_STANDARD_REQUIRED ON)
