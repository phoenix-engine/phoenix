add_library(SDLVKRenderer STATIC)

find_package(Vulkan REQUIRED)

target_link_libraries(SDLVKRenderer
  GLAD
  SDL2
  # Eigen3::Eigen
  glm
  Vulkan::Vulkan
  Error
  SDLInput
  SDLHelper
  SDLScene
  Resource
)

target_include_directories(SDLVKRenderer PUBLIC
  ${Phoenix_INCLUDE_DIR}
)

target_sources(SDLVKRenderer
  PUBLIC ${Phoenix_INCLUDE_DIR}/phx_sdl/vk_renderer.hpp
  PRIVATE vk_renderer.cxx
)

set_property(TARGET SDLVKRenderer PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLVKRenderer PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLVKRenderer PROPERTY CXX_STANDARD_REQUIRED ON)
