if(NOT(APPLE OR IOS))
#  add_subdirectory(glad)
  add_subdirectory(SDL)
endif()

add_subdirectory(spdlog/include)
