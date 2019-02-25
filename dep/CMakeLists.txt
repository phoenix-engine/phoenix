add_subdirectory(glad)

if(APPLE OR IOS)
  add_subdirectory(phoenix-apple-components)
else()
  add_subdirectory(SDL)
endif()
