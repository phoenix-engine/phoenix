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

if(NOT(APPLE OR IOS))
  target_include_directories(
    Phoenix
	INTERFACE
	${SDL2_INCLUDE_DIR}
	${GLAD_INCLUDE_DIR}
  )

  set(Phoenix_HEADERS
    ${Phoenix_HEADERS}
	${CMAKE_CURRENT_LIST_DIR}/phx_sdl
  )
endif()

target_sources(
  Phoenix
  INTERFACE
  ${Phoenix_HEADERS}
)

target_link_libraries(Phoenix INTERFACE Error)
if(WIN32)
  target_link_libraries(Phoenix INTERFACE SDL2 GLAD)
endif()

# Since SOME IDE's can't seem to notice INTERFACE header-only libs....
if("${CMAKE_GENERATOR}" STREQUAL "Xcode")
  add_custom_target(PhoenixHeaders SOURCES ${Phoenix_HEADERS})
endif()
