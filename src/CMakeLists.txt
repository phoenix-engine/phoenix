add_subdirectory(error)
add_subdirectory(consumer)

if(APPLE OR IOS)
  # Do nothing, depend on the MetalPhoenix renderer
else()
  add_subdirectory(sdl)
endif()
