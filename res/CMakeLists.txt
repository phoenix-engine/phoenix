cmake_policy(SET CMP0058 NEW)

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

# Compile pushconstants vert and frag shaders.
add_custom_command(
    OUTPUT pushconstants.vert.spv
    MAIN_DEPENDENCY vk_renderer_pushconstants.vert.glsl
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${SPV_COMPILER} -V vk_renderer_pushconstants.vert.glsl -o pushconstants.vert.spv
    VERBATIM
    COMMENT "Compiling pushconstants vert shader..."
)
add_custom_command(
    OUTPUT pushconstants.frag.spv
    MAIN_DEPENDENCY vk_renderer_pushconstants.frag.glsl
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${SPV_COMPILER} -V vk_renderer_pushconstants.frag.glsl -o pushconstants.frag.spv
    VERBATIM
    COMMENT "Compiling pushconstants frag shader..."
)

# If any of the shader targets are built, regenerate the assets.
add_custom_target(
    GenerateShaderResources
    DEPENDS
	triangle.vert.spv triangle.frag.spv
	pushconstants.vert.spv pushconstants.frag.spv
    BYPRODUCTS
	../dep/res/res/triangle_frag_spv_decl.cxx ../dep/res/res/triangle_frag_spv_real.cxx
	../dep/res/res/triangle_vert_spv_decl.cxx ../dep/res/res/triangle_vert_spv_real.cxx
	../dep/res/res/pushconstants_frag_spv_decl.cxx  ../dep/res/res/pushconstants_frag_spv_real.cxx
	../dep/res/res/pushconstants_vert_spv_decl.cxx  ../dep/res/res/pushconstants_vert_spv_real.cxx
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${PHX_CLI} gen --skip-finalize -l 9 --from . --to ../dep/res --match ".*\.spv"
    VERBATIM
    COMMENT "Generating assets..."
)

#[[
add_custom_command(
    OUTPUT
	../dep/res/res/triangle_frag_spv_decl.cxx ../dep/res/res/triangle_frag_spv_real.cxx
	../dep/res/res/triangle_vert_spv_decl.cxx ../dep/res/res/triangle_vert_spv_real.cxx
	../dep/res/res/pushconstants_frag_spv_decl.cxx  ../dep/res/res/pushconstants_frag_spv_real.cxx
	../dep/res/res/pushconstants_vert_spv_decl.cxx  ../dep/res/res/pushconstants_vert_spv_real.cxx
    DEPENDS
	triangle.vert.spv triangle.frag.spv
	pushconstants.vert.spv pushconstants.frag.spv
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${PHX_CLI} gen --skip-finalize -l 9 --from . --to ../dep/res --match ".*\.spv"
    COMMENT "Generating assets..."
)
]]
