cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

# Add LZ4 and LZ4F definitions.
add_subdirectory(lz4/lib)

# Add Resource library.
add_library(Resource STATIC
  mapper.cxx
  mappings.cxx
  resource.cxx
  res/frag_spv_decl.cxx
  res/vert_spv_decl.cxx
  res/vk_renderer_frag_decl.cxx
  res/vk_renderer_vert_decl.cxx
)

target_link_libraries(Resource LZ4F)

target_include_directories(Resource PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

set_property(TARGET Resource PROPERTY CXX_STANDARD 17)
set_property(TARGET Resource PROPERTY CXX_STANDARD_REQUIRED ON)
