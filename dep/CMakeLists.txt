add_subdirectory(glad)

if(APPLE or IOS)
  add_subdirectory(phoenix-apple-components)
else
  add_subdirectory(SDL)
endif()
