find_program(
    PHX_CLI "phx"
    DOC "The Phoenix CLI: https://github.com/phoenix-engine/phx"
)
find_program(
    SPV_COMPILER "glslangValidator"
    DOC "The SPIR-V compiler for shaders: https://github.com/phoenix-engine/phoenix/blob/dev/doc/developer.md#shaders"
)

# Compile triangle vert and frag shaders.
add_custom_command(
    OUTPUT triangle.vert.spv
    MAIN_DEPENDENCY vk_renderer_triangle.vert.glsl
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${SPV_COMPILER} -V vk_renderer_triangle.vert.glsl -o triangle.vert.spv
    VERBATIM
    COMMENT "Compiling triangle vert shader..."
)
add_custom_command(
    OUTPUT triangle.frag.spv
    MAIN_DEPENDENCY vk_renderer_triangle.frag.glsl
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${SPV_COMPILER} -V vk_renderer_triangle.frag.glsl -o triangle.frag.spv
    VERBATIM
    COMMENT "Compiling triangle frag shader..."
)

# Compile World2d vert and frag shaders.
add_custom_command(
    OUTPUT world2d.vert.spv
    MAIN_DEPENDENCY vk_renderer_world2d.vert.glsl
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${SPV_COMPILER} -V vk_renderer_world2d.vert.glsl -o world2d.vert.spv
    VERBATIM
    COMMENT "Compiling world2d vert shader..."
)
add_custom_command(
    OUTPUT world2d.frag.spv
    MAIN_DEPENDENCY vk_renderer_world2d.frag.glsl
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${SPV_COMPILER} -V vk_renderer_world2d.frag.glsl -o world2d.frag.spv
    VERBATIM
    COMMENT "Compiling world2d frag shader..."
)

# If any of the shader targets are built, regenerate the assets.
add_custom_target(
    GenerateShaderResources
    DEPENDS
	# vk_renderer_triangle.vert.glsl vk_renderer_triangle.frag.glsl
	# vk_renderer_world2d.vert.glsl vk_renderer_world2d.frag.glsl
	triangle.vert.spv triangle.frag.spv
	world2d.vert.spv world2d.frag.spv
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${PHX_CLI} gen --skip-finalize -l 9 --from . --to ../dep/res --match ".*\.spv"
    COMMENT "Generating assets..."
)
