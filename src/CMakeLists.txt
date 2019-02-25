add_subdirectory(error)

if(WIN32 OR LINUX)
  add_subdirectory(sdl)
endif()

add_subdirectory(graphics)
