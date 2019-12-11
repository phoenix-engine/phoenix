cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

if(POLICY CMP0076)
  cmake_policy(SET CMP0076 NEW)
endif() # POLICY CMP0076

# Add LZ4 and LZ4F definitions.
add_subdirectory(lz4/lib)

set_source_files_properties(
  res/pushconstants_frag_spv_real.cxx
  res/pushconstants_vert_spv_real.cxx
  res/triangle_frag_spv_real.cxx
  res/triangle_vert_spv_real.cxx

  PROPERTIES
    GENERATED True
    HEADER_FILE_ONLY ON
)

# Add Resource library.
add_library(Resource STATIC)

target_sources(Resource
  PUBLIC
    mapper.cxx
    mappings.cxx
    resource.cxx
  INTERFACE
    resource.hpp
    mapper.hpp
  PRIVATE
    res/pushconstants_frag_spv_decl.cxx
    res/pushconstants_frag_spv_real.cxx
    res/pushconstants_vert_spv_decl.cxx
    res/pushconstants_vert_spv_real.cxx
    res/triangle_frag_spv_decl.cxx
    res/triangle_frag_spv_real.cxx
    res/triangle_vert_spv_decl.cxx
    res/triangle_vert_spv_real.cxx
)

target_include_directories(Resource PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(Resource LZ4F)

set_property(TARGET Resource PROPERTY CXX_STANDARD 11)
set_property(TARGET Resource PROPERTY CXX_STANDARD_REQUIRED ON)
