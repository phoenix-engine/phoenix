add_library(Phoenix INTERFACE)

target_include_directories(
  Phoenix
  INTERFACE
  ${CMAKE_CURRENT_LIST_DIR}/
)

set(Phoenix_HEADERS

  ${CMAKE_CURRENT_LIST_DIR}/impl

  ${CMAKE_CURRENT_LIST_DIR}/phoenix.hpp

  ${CMAKE_CURRENT_LIST_DIR}/graphics.hpp

  ${CMAKE_CURRENT_LIST_DIR}/renderer.hpp

  ${CMAKE_CURRENT_LIST_DIR}/input.hpp

  ${CMAKE_CURRENT_LIST_DIR}/event.hpp

  ${CMAKE_CURRENT_LIST_DIR}/queue.hpp
)

target_sources(
  Phoenix
  INTERFACE
  ${Phoenix_HEADERS}
)

target_link_libraries(Phoenix INTERFACE Error)

# Since SOME IDE's can't seem to notice INTERFACE header-only libs....
if("${CMAKE_GENERATOR}" STREQUAL "Xcode")
  add_custom_target(PhoenixHeaders SOURCES ${Phoenix_HEADERS})
endif()
