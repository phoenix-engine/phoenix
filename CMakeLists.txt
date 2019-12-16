set(PHX_PROJECT_NAME Phoenix)

## if(DEFINED IOS)
##   set(PHX_PROJECT_NAME Phoenix-iOS)
## endif()

cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
if(POLICY CMP0048)
    # Sane CMake project() command version defaults.
    cmake_policy(SET CMP0048 NEW)
endif() # POLICY CMP0048

project("${PHX_PROJECT_NAME}"
  VERSION 0.0.0.1
  DESCRIPTION "A portable, modern C++ game engine for Metal and Vulkan"
  HOMEPAGE_URL "https://github.com/phoenix-engine/phoenix"
  LANGUAGES C CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# if(DEFINED IOS)
#   message("Building for iOS")
# endif() # IOS

# project-global variables

set(Phoenix_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

# Specify the include dir for CMake projects which import Phoenix.
# find_path(Phoenix_INCLUDE_DIR
#  "include"
#  PATHS ${CMAKE_CURRENT_LIST_DIR}/include
#  PATH_SUFFIXES "include"
#)

set(Phoenix_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/lib)

# Look in this path for CMake modules, before ${CMAKE_ROOT}/Modules/ is
# checked.
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/Modules)

# disallow in-source build
include(MacroEnsureOutOfSourceBuild)
macro_ensure_out_of_source_build("\
${PROJECT_NAME} requires an out of source build. Please create a \
separate build directory and run \
'cmake /path/to/${PROJECT_NAME} [options]' there."
)

add_subdirectory(res)
add_subdirectory(dep)
add_subdirectory(src)
add_subdirectory(include)

# Set variables for use in the CMake meta-build.
set(Phoenix_DIR ${CMAKE_CURRENT_LIST_DIR})
set(INCLUDE_INSTALL_DIR include/)
set(LIB_INSTALL_DIR lib/)

# Configure the CMake project variables for usage by downstreams.
# See https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html
include(CMakePackageConfigHelpers)
configure_package_config_file(
  # The cmake.in file is the template file which will be elaborated.
  PhoenixConfig.cmake.in

  # The .cmake file is the product of the template elaboration.  It will
  # be consumed by a downstream build which imports this project.
  PhoenixConfig.cmake

  # INSTALL_DESTINATION is the path where the generated Config.cmake
  # file will be installed.
  INSTALL_DESTINATION ${CMAKE_CURRENT_LIST_DIR}/cmake

  # PATH_VARS specifies the install paths of the products of this Config
  # package.
  # PATH_VARS artifacts/Release
  PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR

  # [NO_SET_AND_CHECK_MACRO]
  # NO_CHECK_REQUIRED_COMPONENTS_MACRO

  # INSTALL_PREFIX specifies the location the package will be installed.
  # In this case, the package is intended to be used from within the
  # build tree, rather than from a system lib directory.
  #
  # A future binary-only build could set this to a system lib install
  # directory.
  INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}
)

write_basic_package_version_file(
  Phoenix-version.cmake
  VERSION 0.0.1
  COMPATIBILITY SameMinorVersion
)
