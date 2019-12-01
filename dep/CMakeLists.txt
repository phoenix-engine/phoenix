if(NOT(APPLE OR IOS))
  # Configure things for Vulkan / SDL.  On Apple, use Metal directly.
  add_subdirectory(glad)

  # Configure SDL (we only want the shared library)
  set(SDL_STATIC OFF)
  set(SDL_SHARED ON)
  add_subdirectory(SDL)
endif()

add_subdirectory(spdlog/include)

add_subdirectory(res)
## TODO: Make this codegen process smoother (dep chain incorrect!)
## Regenerate shaders before building Resource if necessary.
# add_dependencies(Resource GenerateShaderResources)

add_subdirectory(eigen)

# Configure GLM
set(GLM_TEST_ENABLE_CXX_17	true)
set(GLM_QUIET			true)
set(BUILD_SHARED_LIBS		off)
set(GLM_TEST_ENABLE		off)
set(GLM_FORCE_RADIANS		on)
set(GLM_FORCE_DEPTH_ZERO_TO_ONE	on)

add_subdirectory(glm)
