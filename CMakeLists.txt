project(Phoenix CXX C)

add_subdirectory(dep)
add_subdirectory(src)

# find_package(SDL2 REQUIRED)

# target_include_directories(App PUBLIC
#   ${SDL2_INCLUDE_DIR}
#   ${GLAD_INCLUDE_DIR}
#   ${Phoenix_INCLUDE_DIR}/error
#   ${Phoenix_INCLUDE_DIR}/world
#   ${Phoenix_INCLUDE_DIR}/app
#   ${Phoenix_INCLUDE_DIR}/sdl
#   ${Phoenix_INCLUDE_DIR}/graphics
# )

# target_link_libraries(App
#   ${SDL2_LIBRARY}
#   GLAD
#   Error
#   SDLUtil
#   SDLGLRenderer
#   World
#   Graphics
# )
