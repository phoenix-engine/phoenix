if(NOT(APPLE OR IOS))
  add_subdirectory(glad)
  add_subdirectory(SDL)
endif()

add_subdirectory(spdlog/include)

# GLM CMake configuration
set(GLM_TEST_ENABLE_FAST_MATH   true)
set(GLM_FORCE_RADIANS           true)
set(GLM_FORCE_DEPTH_ZERO_TO_ONE true)
add_subdirectory(glm)
