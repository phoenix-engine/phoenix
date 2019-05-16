set(SDLVKRenderer_SRCS
  vk_renderer.cxx
)

add_library(SDLVKRenderer STATIC ${SDLVKRenderer_SRCS})

find_package(Vulkan REQUIRED)

target_include_directories(SDLVKRenderer PUBLIC
  ${GLAD_INCLUDE_DIR}
  ${Vulkan_INCLUDE_DIR}
  ${SDL2_INCLUDE_DIR}
)

target_link_libraries(SDLVKRenderer
  GLAD
  SDL2
  Vulkan::Vulkan
  Error
  SDLHelper
)

set_property(TARGET SDLVKRenderer PROPERTY POSITION_INDEPENDENT_CODE ON)

set_property(TARGET SDLVKRenderer PROPERTY CXX_STANDARD 17)
set_property(TARGET SDLVKRenderer PROPERTY CXX_STANDARD_REQUIRED ON)
